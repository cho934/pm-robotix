/*******************************************************************************
 * ClubElek Robot motion control software for Eurobot 2007
 * Copyright (C) 2006-2007 ClubElek
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *******************************************************************************/
//! \file motion.c
//! \author Julien Rouviere <gmail address : julien.rouviere@...>
//! \author ClubElek <http://clubelek.insa-lyon.fr>
// svn :
// $LastChangedBy$
// $LastChangedDate$
/******************************************************************************/

#include "motion.h"

#include "motion_priv.h"

#include "motor.h"
#include "motor_PID.h"

#include "robot_odometry.h"
#include "robot_trajectory.h"
#include "robot_slippage.h"

#include "path_manager.h"
#include "encoder.h"
#include "global.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
//tell the program if mouse sensor and/or motor encoder are available 
#include <sys/time.h>
#include <sys/signal.h>
#include <errno.h>
#include <string.h>
#include "../robot.h"
#include "../log.h"
MOTION_STATE RobotMotionState;

//nb of period since the beginning
static uint32 periodNb;

//semaphore for motion IT and Task
static sem_t semMotionIT;

//mutex protecting the currently executed command
static pthread_mutex_t mtxMotionCommand;
static pthread_t thread;
//the currently executed command
static RobotCommand motionCommand;

//motion control task
void *motion_ITTask(void *p_arg);

void motion_InitTimer(int frequency);
void initPWM(void);
void signalEndOfTraj(void);

//declaration of some internal function :
void path_Init(void);
void path_TriggerWaypoint(TRAJ_STATE state);

void configurePID() {
	pid_ConfigKP(motors[ALPHA_DELTA][ALPHA_MOTOR].PIDSys, 40);
	pid_ConfigKI(motors[ALPHA_DELTA][ALPHA_MOTOR].PIDSys, 0);
	pid_ConfigKD(motors[ALPHA_DELTA][ALPHA_MOTOR].PIDSys, 20);
	pid_ConfigDPeriod(motors[ALPHA_DELTA][ALPHA_MOTOR].PIDSys, 3);

	pid_ConfigKP(motors[ALPHA_DELTA][DELTA_MOTOR].PIDSys, 1020);
	pid_ConfigKI(motors[ALPHA_DELTA][DELTA_MOTOR].PIDSys, 0);
	pid_ConfigKD(motors[ALPHA_DELTA][DELTA_MOTOR].PIDSys, 00);
	pid_ConfigDPeriod(motors[ALPHA_DELTA][DELTA_MOTOR].PIDSys, 3);

	pid_ConfigKP(motors[LEFT_RIGHT][LEFT_MOTOR].PIDSys, 75);
	pid_ConfigKI(motors[LEFT_RIGHT][LEFT_MOTOR].PIDSys, 0);
	pid_ConfigKD(motors[LEFT_RIGHT][LEFT_MOTOR].PIDSys, 50);

	pid_ConfigKP(motors[LEFT_RIGHT][RIGHT_MOTOR].PIDSys, 75);
	pid_ConfigKI(motors[LEFT_RIGHT][RIGHT_MOTOR].PIDSys, 5);
	pid_ConfigKD(motors[LEFT_RIGHT][RIGHT_MOTOR].PIDSys, 50);
	motors_ConfigAllIMax(90000);

}
void motion_Init() {
	int i, j;

	periodNb = 0;

	initPWM();

	pid_Init();
	//motor initialisation
	for (i = 0; i < MAX_MOTION_CONTROL_TYPE_NUMBER; i++) {
		for (j = 0; j < MOTOR_PER_TYPE; j++) {
			initMotor(&motors[i][j]);
		}
	}
	configurePID();
	encoder_Init();

	motion_FreeMotion();

	//timing semaphore : unlock the motion control task periodically
	sem_init(&semMotionIT, 0, 0);

	//currently executed motion command protection mutex
	pthread_mutex_init(&mtxMotionCommand, NULL);

	//create motion control task
	if (pthread_create(&thread, NULL, motion_ITTask, NULL) < 0) {
		fprintf(stderr, "pthread_create error for thread 1\n");
		exit(1);
	}

	motion_InitTimer(DEFAULT_SAMPLING_FREQ);
	traj_Init();
	slippage_Init();

	//path manager initialisation
	path_Init();
}
void motion_Destroy() {

}
void signalEndOfTraj() {
	if (motionCommand.cmdType == POSITION_COMMAND) {
		motion_FreeMotion();
	}

	if (nextWaypoint.type == WP_END_OF_TRAJ) {
		path_TriggerWaypoint(TRAJ_OK);
	}
}

void resetAllPIDErrors(void) {
	pid_ResetError(motors[LEFT_RIGHT][LEFT_MOTOR].PIDSys);
	pid_ResetError(motors[LEFT_RIGHT][RIGHT_MOTOR].PIDSys);
	pid_ResetError(motors[ALPHA_DELTA][ALPHA_MOTOR].PIDSys);
	pid_ResetError(motors[ALPHA_DELTA][DELTA_MOTOR].PIDSys);
}

void motion_FreeMotion() {
	resetAllPIDErrors();
	RobotMotionState = FREE_MOTION;
	setPWM(0, 0);

	resetAllPIDErrors();
}

void motion_AssistedHandling() {
	motion_FreeMotion();
}

void motion_DisablePID() {
	motion_FreeMotion();
	RobotMotionState = DISABLE_PID;
	setPWM(0, 0);


	resetAllPIDErrors();
}

void loadCommand(RobotCommand *cmd) {
	switch (cmd->cmdType) {
	case POSITION_COMMAND:
		LoadPositionCommand(&cmd->cmd.posCmd[0], &motors[cmd->mcType][0],
				periodNb);
		LoadPositionCommand(&cmd->cmd.posCmd[1], &motors[cmd->mcType][1],
				periodNb);
		break;

	case SPEED_COMMAND:
		//if we are in same command mode, we get the next order and apply it
		//as the starting point of new trajectory
		if (motionCommand.cmdType == SPEED_COMMAND
				&& motionCommand.mcType == cmd->mcType) {
			int32 pos0, pos1;
			GetSpeedOrder(&motionCommand.cmd.speedCmd[0], periodNb, &pos0);
			GetSpeedOrder(&motionCommand.cmd.speedCmd[1], periodNb, &pos1);

			LoadSpeedCommand(&cmd->cmd.speedCmd[0], pos0, periodNb);
			LoadSpeedCommand(&cmd->cmd.speedCmd[1], pos1, periodNb);
		} else {
			LoadSpeedCommand(&cmd->cmd.speedCmd[0],
					motors[cmd->mcType][0].lastPos, periodNb);
			LoadSpeedCommand(&cmd->cmd.speedCmd[1],
					motors[cmd->mcType][1].lastPos, periodNb);
		}
		break;

	default:
		break;
	};
}

void motion_SetCurrentCommand(RobotCommand *cmd) {
	RobotMotionState = DISABLE_PID;

	pthread_mutex_lock(&mtxMotionCommand);

	loadCommand(cmd);
	motionCommand = *cmd;
	RobotMotionState = TRAJECTORY_RUNNING;

	pthread_mutex_unlock(&mtxMotionCommand);

}

void SendMotorErrors(int32 error0, int32 error1) {

}

static __sighandler_t Motion_IT(void) {
	//	OSIntEnter();
	//printf("Motion_IT\n");
	if (RobotMotionState != DISABLE_PID) {
		//p13_5 = 1;	//period measurement
		sem_post(&semMotionIT);
	}
	return 0;
	//OSIntExit();
}

//Motion control main loop
//implemented as an IT task, armed on a timer to provide
//a constant and precise period between computation
void *motion_ITTask(void *p_arg) {
	static int32 left, right;
	static int32 alpha, delta;

	static int32 dLeft, dRight;
	static int32 dAlpha, dDelta;

	static int32 dLeft2, dRight2;
	static int32 dAlpha2, dDelta2;

	static int32 ord0, ord1;
	static BOOL fin0, fin1;
	static int32 pwm0, pwm1;
	static int32 pwm0b, pwm1b;
	printf("motion_ITTask start\n");
	int stop = 0;
	while (!stop) {

		sem_wait(&semMotionIT);
		printf("motion.c : ------  updating state ---- time : %ld ms [%d]\n",
				currentTimeInMillis(), RobotMotionState);

		periodNb++;

		encoder_ReadSensor(&dLeft, &dRight, &dAlpha, &dDelta);

		odo_Integration(2 * dAlpha / (float) distEncoder, (float) dDelta);

		RobotPosition p = odo_GetPosition();
		log_status(currentTimeInMillis(), robot_getLeftExternalCounter(),
				robot_getRightExternalCounter(), robot_getLeftPower(),
				robot_getRightPower(), p.x, p.y, p.theta);

		//send position
		//	if ((periodNb & 0x3F) == 0) {
//			pos_SendPosition();
//		}

		//update all motors 
		updateMotor(&motors[LEFT_RIGHT][LEFT_MOTOR], dLeft);
		updateMotor(&motors[LEFT_RIGHT][RIGHT_MOTOR], dRight);
		updateMotor(&motors[ALPHA_DELTA][ALPHA_MOTOR], dAlpha);
		updateMotor(&motors[ALPHA_DELTA][DELTA_MOTOR], dDelta);

		//order and pwm computation
		switch (RobotMotionState) {
		case TRAJECTORY_RUNNING:
			//lock motionCommand
			pthread_mutex_lock(&mtxMotionCommand);

			//choose the right function to compute new order value
			switch (motionCommand.cmdType) {
			case POSITION_COMMAND:
				printf("motion.c :  POSITION_COMMAND\n");
				fin0 = GetPositionOrder(&motionCommand.cmd.posCmd[0], periodNb,
						&ord0);
				fin1 = GetPositionOrder(&motionCommand.cmd.posCmd[1], periodNb,
						&ord1);
				printf(
						"motion.c :  POSITION_COMMAND posCmd1:%d %d periodNb:%d fin1:%d\n",
						&motionCommand.cmd.posCmd[1].order0,
						&motionCommand.cmd.posCmd[1].order3, periodNb, fin1);
				break;

			case SPEED_COMMAND:
				printf("motion.c :  SPEED_COMMAND\n");
				fin0 = GetSpeedOrder(&motionCommand.cmd.speedCmd[0], periodNb,
						&ord0);
				fin1 = GetSpeedOrder(&motionCommand.cmd.speedCmd[1], periodNb,
						&ord1);
				break;

			case STEP_COMMAND:
				printf("motion.c :  STEP_COMMAND\n");
				fin0 = GetStepOrder(&motionCommand.cmd.stepCmd[0], &ord0);
				fin1 = GetStepOrder(&motionCommand.cmd.stepCmd[1], &ord1);
				break;
			}

			//compute pwm for first motor
			printf("motion.c motion_ITTask pid_Compute ord0:%d lastPos0:%d\n",
					ord0, motors[motionCommand.mcType][0].lastPos);
			pwm0 = pid_Compute(motors[motionCommand.mcType][0].PIDSys,
					ord0 - motors[motionCommand.mcType][0].lastPos);
			printf(
					"motion.c motion_ITTask pid_Compute : order pos:%d last pos:%d\n",
					ord1, motors[motionCommand.mcType][1].lastPos);
			//compute pwm for second motor
			pwm1 = pid_Compute(motors[motionCommand.mcType][1].PIDSys,
					ord1 - motors[motionCommand.mcType][1].lastPos);

			//output pwm to motors
			if (motionCommand.mcType == LEFT_RIGHT) {
				printf("motion.c :  LEFT_RIGHT\n");
				setPWM(pwm0, pwm1);
			} else if (motionCommand.mcType == ALPHA_DELTA) {
				printf("motion.c :  ALPHA_DELTA\n");
				pwm0b = pwm1 - pwm0;
				BOUND_INT(pwm0b, 0x7EFF);

				pwm1b = pwm1 + pwm0;
				BOUND_INT(pwm1b, 0x7EFF);

				setPWM(pwm0b, pwm1b);
			}

			//if required send both errors
			if (isSendErrorsEnabled) {
				SendMotorErrors(ord0 - motors[motionCommand.mcType][0].lastPos,
						ord1 - motors[motionCommand.mcType][1].lastPos);
			}

			//test end of traj
			if (fin0 && fin1) {
				signalEndOfTraj();
			}

			//unlock motionCommand
			pthread_mutex_unlock(&mtxMotionCommand);

			break;

		case ASSISTED_HANDLING: {
			//compute pwm for first motor
			pwm0 = pid_Compute(motors[motionCommand.mcType][0].PIDSys, dLeft);

			//compute pwm for second motor
			pwm1 = pid_Compute(motors[motionCommand.mcType][1].PIDSys, dRight);

			//write pwm in registers
			setPWM(pwm0, pwm1);
		}
			break;

		case DISABLE_PID: {
			printf("motion_ITTask DISABLE_PID end exit \n");
			stop = 1;
			break;
		}
		case FREE_MOTION: {
			printf("motion_ITTask FREE_MOTION end exit \n");
			stop = 1;
			break;
		}
		default:
			break;
		};
		//p13_5 = 0;	//period measurement
	}
	printf("motion_ITTask end exit()\n");
	sleep(1);
	//exit(2);
	return 0;
}

//Motion control main loop
//implemented as an IT handler armed on a timer to provide
//a constant and precise period between computation
void motion_InitTimer(int frequency) {
//	motion_SetSamplingFrequency(frequency);
	printf("motion_InitTimer\n");
	signal(SIGALRM, Motion_IT);
	long delay = 10 * 1000;
	struct itimerval tval = {
	/* subsequent firings */.it_interval = { .tv_sec = 0, .tv_usec = delay },
	/* first firing */.it_value = { .tv_sec = 0, .tv_usec = delay } };

	int err = setitimer(ITIMER_REAL, &tval, (struct itimerval*) 0);
	printf("motion_InitTimer %ld ms [%d]\n", delay / 1000, err);
	if (err != 0) {
		printf("Oh dear, something went wrong with setitimer()! %s\n",
				strerror(errno));
	}
}

void motion_StopTimer() {
	setPWM(0, 0);
}

void initPWM() {

}

void setPWM(int16 pwmLeft, int16 pwmRight) {
	printf("motion.c setPWM : left %d  right %d\n", pwmLeft, pwmRight);
	robot_setMotorLeftSpeed(pwmLeft);
	robot_setMotorRightSpeed(pwmRight);
}

