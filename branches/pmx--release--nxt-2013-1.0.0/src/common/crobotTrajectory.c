#pragma config(Sensor, S4,     HTANG_LEFT,     sensorI2CCustom)
#pragma config(Sensor, S1,     HTANG_RIGHT,    sensorI2CCustom)
#pragma config(Motor,  motorC,          MOTOR_LEFT,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorA,          MOTOR_RIGHT,   tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma platform(NXT)

#ifndef _ROBOT_TRAJECTORY
#define _ROBOT_TRAJECTORY // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "crobotTrajectory.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _ROBOT_TRAJECTORY_H_
#include "crobotTrajectory.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES
// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: EXTERNAL SOURCES
#include "cunitConversion.c"
#ifndef _ENCODER
#include "cencoder.c"
#endif
#include "cmotorSpeedCmd.c"
#include "cmotorPositionCmd.c"
#include "cmotorStepCmd.c"
// END OF:  EXTERNAL SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES
//static ClothoidParam clotho;
//static RobotCommand nextCommand;
// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES

void traj_Init()
{
	//TODO
}

void motion_Line(RobotCommand *out_cmd, float dist)
{
	motion_LineSpeedAcc(out_cmd, dist, motion_GetDefaultSpeed(), motion_GetDefaultAccel(), motion_GetDefaultDecel());
}

void motion_LineSpeed(RobotCommand *out_cmd, float dist, float VMax)
{
	motion_LineSpeedAcc(out_cmd, dist, VMax, motion_GetDefaultAccel(), motion_GetDefaultDecel());
}

void motion_LineSpeedAcc(RobotCommand *out_cmd, float dist, float VMax, float Accel, float Decel)
{
	out_cmd->cmdType = POSITION_COMMAND;
	out_cmd->mcType = ALPHA_DELTA;

	//ALPHA
	ComputePositionCommand(	&(out_cmd->cmd.posCmd[ALPHA_MOTOR]),
							0,0,0,0);	//no move on alpha

	//DELTA
	ComputePositionCommand(	&(out_cmd->cmd.posCmd[DELTA_MOTOR]),
							convertDistTovTops(dist),
							convertSpeedTovTopsPerPeriod(VMax),
							convertAccelTovTopsPerPeriodSqd(Accel),
							convertAccelTovTopsPerPeriodSqd(Decel) );
}

void motion_Rotate(RobotCommand *out_cmd, float angle)
{
	motion_RotateSpeedAcc(out_cmd, angle, motion_GetDefaultSpeed(), motion_GetDefaultAccel(), motion_GetDefaultDecel());
}

void motion_RotateSpeed(RobotCommand *out_cmd, float angle, float VMax)
{
	motion_RotateSpeedAcc(out_cmd, angle, VMax, motion_GetDefaultAccel(), motion_GetDefaultDecel());
}

void motion_RotateSpeedAcc(RobotCommand *out_cmd, float angle, float VMax, float Accel, float Decel)
{
	out_cmd->cmdType = POSITION_COMMAND;
	out_cmd->mcType = ALPHA_DELTA;

	//ALPHA
	ComputePositionCommand(&(out_cmd->cmd.posCmd[ALPHA_MOTOR]),
								convertDistTovTops(angle*distEncoderMeter/2.0),
								convertSpeedTovTopsPerPeriod(VMax),
								convertAccelTovTopsPerPeriodSqd(Accel),
								convertAccelTovTopsPerPeriodSqd(Decel));

	//DELTA
	ComputePositionCommand(&(out_cmd->cmd.posCmd[DELTA_MOTOR]),
								0, 0, 0, 0);	//no move on delta
}


void motion_ArcRotate(RobotCommand *out_cmd, float angle, float radius)
{
	motion_ArcRotateSpeedAcc(out_cmd, angle, radius, motion_GetDefaultSpeed(), motion_GetDefaultAccel(), motion_GetDefaultDecel());
}

void motion_ArcRotateSpeed(RobotCommand *out_cmd, float angle, float radius, float VMax)
{
	motion_ArcRotateSpeedAcc(out_cmd, angle, radius, VMax, motion_GetDefaultAccel(), motion_GetDefaultDecel());
}

void motion_ArcRotateSpeedAcc(RobotCommand *out_cmd, float angle, float radius, float VMax, float Accel, float Decel)
{
	float dL,dR;
	float ratio;

	out_cmd->cmdType = POSITION_COMMAND;
	out_cmd->mcType = LEFT_RIGHT;

	dL = angle*(radius-distEncoderMeter/2.0);
	dR = angle*(radius+distEncoderMeter/2.0);

	if(abs(dL) > abs(dR))
	{
		ratio = dR/dL;

		//LEFT
		ComputePositionCommand(&(out_cmd->cmd.posCmd[LEFT_MOTOR]),
									convertDistTovTops(dL),
									convertSpeedTovTopsPerPeriod(VMax),
									convertAccelTovTopsPerPeriodSqd(Accel),
									convertAccelTovTopsPerPeriodSqd(Decel));

		//RIGHT
		ComputePositionCommand(&(out_cmd->cmd.posCmd[RIGHT_MOTOR]),
									convertDistTovTops(dR),
									convertSpeedTovTopsPerPeriod(VMax*ratio),
									convertAccelTovTopsPerPeriodSqd(Accel*ratio),
									convertAccelTovTopsPerPeriodSqd(Decel*ratio));
	}
	else
	{
		ratio = dL/dR;

		//LEFT
		ComputePositionCommand(&(out_cmd->cmd.posCmd[LEFT_MOTOR]),
									convertDistTovTops(dL),
									convertSpeedTovTopsPerPeriod(VMax*ratio),
									convertAccelTovTopsPerPeriodSqd(Accel*ratio),
									convertAccelTovTopsPerPeriodSqd(Decel*ratio));

		//RIGHT
		ComputePositionCommand(&(out_cmd->cmd.posCmd[RIGHT_MOTOR]),
									convertDistTovTops(dR),
									convertSpeedTovTopsPerPeriod(VMax),
									convertAccelTovTopsPerPeriodSqd(Accel),
									convertAccelTovTopsPerPeriodSqd(Decel));
	}
}

void motion_SpeedControlLR(RobotCommand *out_cmd, float spLeft, float distLeft, float accLeft, float spRight, float distRight, float accRight)
{
	out_cmd->cmdType = SPEED_COMMAND;
	out_cmd->mcType = LEFT_RIGHT;

	//LEFT
	ComputeSpeedCommand(&(out_cmd->cmd.speedCmd[LEFT_MOTOR]),
							getMotorSpeed(&motors[LEFT_RIGHT][LEFT_MOTOR]),
							convertSpeedTovTopsPerPeriod(spLeft),
							convertDistTovTops(distLeft),
							convertAccelTovTopsPerPeriodSqd(accLeft));

	//RIGHT
	ComputeSpeedCommand(&(out_cmd->cmd.speedCmd[RIGHT_MOTOR]),
							getMotorSpeed(&motors[LEFT_RIGHT][RIGHT_MOTOR]),
							convertSpeedTovTopsPerPeriod(spRight),
							convertDistTovTops(distRight),
							convertAccelTovTopsPerPeriodSqd(accRight));
}

void motion_SpeedControlADMaxTime(RobotCommand *out_cmd,
								float spAlpha, float accAlpha,
								float spDelta, float accDelta,
								int duringMs)
{
	long time;

	out_cmd->cmdType = SPEED_COMMAND;
	out_cmd->mcType = ALPHA_DELTA;

	//time = (DEFAULT_SAMPLING_FREQ*duringMs)/1000;
	time = (duringMs/DEFAULT_SAMPLING_PERIOD_Ms)/1000;


	ComputeSpeedCommandMaxTime( &(out_cmd->cmd.speedCmd[ALPHA_MOTOR]),
								getMotorSpeed(&motors[ALPHA_DELTA][ALPHA_MOTOR]),
								convertSpeedTovTopsPerPeriod(spAlpha),
								convertAccelTovTopsPerPeriodSqd(accAlpha),
								time);

	ComputeSpeedCommandMaxTime( &(out_cmd->cmd.speedCmd[DELTA_MOTOR]),
								getMotorSpeed(&motors[ALPHA_DELTA][DELTA_MOTOR]),
								convertSpeedTovTopsPerPeriod(spDelta),
								convertAccelTovTopsPerPeriodSqd(accDelta),
								time);
}

void motion_SpeedControlLRDecel(RobotCommand *out_cmd,
						float spLeft, float distLeft, float accLeft, float decLeft,
						float spRight, float distRight, float accRight, float decRight)
{
	long motorSpeed;
	long goalSpeed;

	out_cmd->cmdType = SPEED_COMMAND;
	out_cmd->mcType = LEFT_RIGHT;

	motorSpeed = getMotorSpeed(&motors[LEFT_RIGHT][LEFT_MOTOR]);
	goalSpeed = convertSpeedTovTopsPerPeriod(spLeft);

	if( ((motorSpeed < goalSpeed) && motorSpeed > 0)
		|| ((motorSpeed > goalSpeed) && motorSpeed < 0) )
	{
		//LEFT
		ComputeSpeedCommand(&(out_cmd->cmd.speedCmd[LEFT_MOTOR]),
								motorSpeed,
								goalSpeed,
								convertDistTovTops(distLeft),
								convertAccelTovTopsPerPeriodSqd(accLeft));
	}
	else
	{
		//LEFT
		ComputeSpeedCommand(&(out_cmd->cmd.speedCmd[LEFT_MOTOR]),
								motorSpeed,
								goalSpeed,
								convertDistTovTops(distLeft),
								convertAccelTovTopsPerPeriodSqd(decLeft));
	}

	motorSpeed = getMotorSpeed(&motors[LEFT_RIGHT][RIGHT_MOTOR]);
	goalSpeed = convertSpeedTovTopsPerPeriod(spRight);

	if( ((motorSpeed < goalSpeed) && motorSpeed > 0)
	|| ((motorSpeed > goalSpeed) && motorSpeed < 0) )
	{
		//RIGHT
		ComputeSpeedCommand(&(out_cmd->cmd.speedCmd[RIGHT_MOTOR]),
								motorSpeed,
								goalSpeed,
								convertDistTovTops(distRight),
								convertAccelTovTopsPerPeriodSqd(accRight));
	}
	else
	{
		//RIGHT
		ComputeSpeedCommand(&(out_cmd->cmd.speedCmd[RIGHT_MOTOR]),
								motorSpeed,
								goalSpeed,
								convertDistTovTops(distRight),
								convertAccelTovTopsPerPeriodSqd(decRight));
	}
}

void motion_SpeedControlLRV0(RobotCommand *out_cmd,
							float V0Left, float spLeft, float distLeft, float accLeft,
							float V0Right, float spRight, float distRight, float accRight)
{
	out_cmd->cmdType = SPEED_COMMAND;
	out_cmd->mcType = LEFT_RIGHT;

	//LEFT
	ComputeSpeedCommand(&(out_cmd->cmd.speedCmd[LEFT_MOTOR]),
							convertSpeedTovTopsPerPeriod(V0Left),
							convertSpeedTovTopsPerPeriod(spLeft),
							convertDistTovTops(distLeft),
							convertAccelTovTopsPerPeriodSqd(accLeft));

	//RIGHT
	ComputeSpeedCommand(&(out_cmd->cmd.speedCmd[RIGHT_MOTOR]),
							convertSpeedTovTopsPerPeriod(V0Right),
							convertSpeedTovTopsPerPeriod(spRight),
							convertDistTovTops(distRight),
							convertAccelTovTopsPerPeriodSqd(accRight));
}

void motion_SpeedControlLRTime(RobotCommand *out_cmd,
							float V0Left, float TLeft, float accLeft,
							float V0Right, float TRight, float accRight)
{
	out_cmd->cmdType = SPEED_COMMAND;
	out_cmd->mcType = LEFT_RIGHT;

	//LEFT
	ComputeSpeedCommandTime(&(out_cmd->cmd.speedCmd[LEFT_MOTOR]),
							convertSpeedTovTopsPerPeriod(V0Left),
							(long)(TLeft / valueSample),
							convertAccelTovTopsPerPeriodSqd(accLeft));

	//RIGHT
	ComputeSpeedCommandTime(&(out_cmd->cmd.speedCmd[RIGHT_MOTOR]),
							convertSpeedTovTopsPerPeriod(V0Right),
							(long)(TRight / valueSample),
							convertAccelTovTopsPerPeriodSqd(accRight));
}

void motion_SpeedControlAD(RobotCommand *out_cmd, float spAlpha, float distAlpha, float accAlpha, float spDelta, float distDelta, float accDelta)
{
	out_cmd->cmdType = SPEED_COMMAND;
	out_cmd->mcType = ALPHA_DELTA;

	//ALPHA
	ComputeSpeedCommand(&(out_cmd->cmd.speedCmd[ALPHA_MOTOR]),
							getMotorSpeed(&motors[ALPHA_DELTA][ALPHA_MOTOR]),
							convertSpeedTovTopsPerPeriod(spAlpha),
							convertDistTovTops(distAlpha),
							convertAccelTovTopsPerPeriodSqd(accAlpha));

	//DELTA
	ComputeSpeedCommand(&(out_cmd->cmd.speedCmd[DELTA_MOTOR]),
							getMotorSpeed(&motors[ALPHA_DELTA][DELTA_MOTOR]),
							convertSpeedTovTopsPerPeriod(spDelta),
							convertDistTovTops(distDelta),
							convertAccelTovTopsPerPeriodSqd(accDelta));
}

void motion_StepOrderLR(RobotCommand *out_cmd, long posLeft, long posRight)
{
	out_cmd->cmdType = STEP_COMMAND;
	out_cmd->mcType = LEFT_RIGHT;

	//LEFT
	ComputeStepOrder(&(out_cmd->cmd.stepCmd[LEFT_MOTOR]), posLeft);

	//RIGHT
	ComputeStepOrder(&(out_cmd->cmd.stepCmd[RIGHT_MOTOR]), posRight);
}

void motion_StepOrderAD(RobotCommand *out_cmd, long posAlpha, long posDelta)
{
	out_cmd->cmdType = STEP_COMMAND;
	out_cmd->mcType = ALPHA_DELTA;

	//ALPHA
	ComputeStepOrder(&(out_cmd->cmd.stepCmd[ALPHA_MOTOR]), posAlpha);

	//DELTA
	ComputeStepOrder(&(out_cmd->cmd.stepCmd[DELTA_MOTOR]), posDelta);
}

// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: TESTS

#if(PROJECT_MAIN_FILE == "crobotTrajectory.c")
	//-----------------------------------------------------------------------------------------------------------------------------
	//! @brief     this task tests the functions
	//! @return    none
	//! @author    cho
	//! @note
	//! @todo
	//-----------------------------------------------------------------------------------------------------------------------------
	task main()
	{
		//traj_Init();
		//RobotCommand cmd;
		////motion_Rotate(&cmd, 2*PI);

		//motion_Line(&cmd, 2.0);
		//path_LaunchTrajectory(&cmd);

		//path_WaitEndOfTrajectory();
	}
#endif // (PROJECT_MAIN_FILE)

// END OF:  TESTS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif
