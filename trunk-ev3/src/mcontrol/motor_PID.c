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
//! \file motor_PID.c
//! \author Julien Rouviere <gmail address : julien.rouviere@...>
//! \author ClubElek <http://clubelek.insa-lyon.fr>
// svn :
// $LastChangedBy$
// $LastChangedDate$
/******************************************************************************/

#include "motor.h"

#include "motor_PID.h"
#include "types.h"
#include "global.h"
#include <stdio.h>
#include "../robot.h"

pidSystemValues systemValues[MAX_PID_SYSTEM_NUMBER];

//number of system created so far
PID_SYSTEM pid_Nb;

void pid_Init() {
	pid_Nb = 0;

}

PID_SYSTEM pid_Create() {
	//no more available system
	if (pid_Nb >= MAX_PID_SYSTEM_NUMBER)
		return -1;

	//init configuration variables
	systemValues[pid_Nb].conf.kP = 50;
	systemValues[pid_Nb].conf.kI = 5;
	systemValues[pid_Nb].conf.kD = 40;

	//init current state variables

	pid_Nb++;
	return pid_Nb - 1;
}

//! \brief This function signal a very big error integral value,
//! generally it is caused by a hardware problem
void signalErrorOverflow(PID_SYSTEM system) {
	if (getMotorSpeed(&(motors[ALPHA_DELTA][DELTA_MOTOR])) > 0) {
		//collision_SignalShock(FRONT_SHOCK);
		printf("motor.c signalErrorOverflow PID Overflow'd front : %d\n",
				system);
	} else {
		//collision_SignalShock(BACK_SHOCK);
		printf("motor.c signalErrorOverflow PID Overflow'd back : %d\n",
				system);
	}
}

int SampleTime = 10; //30 millisec
double outMin = -100.0f;
double outMax = 100.0f;

void pid_Config(PID_SYSTEM system, double kp, double ki, double kd) {

	double SampleTimeInSec = ((double) SampleTime) / 1000;
	systemValues[system].lastTime = 0;
	systemValues[system].lastOutput = 0.0;
	systemValues[system].lastInput = 0.0;
	systemValues[system].conf.kP = kp;
	systemValues[system].conf.kI = ki * SampleTimeInSec;
	systemValues[system].conf.kD = kd / SampleTimeInSec;
}

//void SetOutputLimits(PID_SYSTEM system,double Min, double Max) {
//	if (Min > Max)
//		return;
//	outMin = Min;
//	outMax = Max;
//
//	if (Output > outMax)
//		Output = outMax;
//	else if (Output < outMin)
//		Output = outMin;
//
//	if (ITerm > outMax)
//		ITerm = outMax;
//	else if (ITerm < outMin)
//		ITerm = outMin;
//}

/*working variables*/
//unsigned long lastTime;
//double Input, Output, Setpoint;
//double ITerm, lastInput;
/**
 * SetPoint : value to reach
 * Input : current value
 *
 * */
double pid_Compute(PID_SYSTEM system, double setpoint, double input,
		double speed) {
	printf("pidCompute %d\n",system);
	pidSystemValues* val = &(systemValues[system]);
	pidConfig conf = val->conf;

	double outPut = val->lastOutput;
	double lastInput = val->lastInput;
	double ITerm = val->ITerm;

	unsigned long now = currentTimeInMillis();
	unsigned long lastTime = val->lastTime;

	int timeChange = (now - lastTime);
	if (timeChange >= SampleTime) {
		double kp = conf.kP;
		double ki = conf.kI;
		double kd = conf.kD;

		/*Compute all the working error variables*/
		double error = setpoint - input;
		ITerm += (ki * error);
		if (ITerm > outMax)
			ITerm = outMax;
		else if (ITerm < outMin)
			ITerm = outMin;
		double dInput = (input - lastInput);

		/*Compute PID Output*/
		outPut = kp * error + ITerm - kd * dInput;
		if (outPut > outMax)
			outPut = outMax;
		else if (outPut < outMin)
			outPut = outMin;

		/*Remember some variables for next time*/
		val->lastInput = input;
		val->lastTime = now;
		val->ITerm = ITerm;
	} else {
		printf("No pid calculation: %ld - %ld = %d ms\n", now, lastTime,
				timeChange);
	}
	val->lastOutput = outPut;
	return outPut;
}

// RCVA

// int32 pid_Compute(PID_SYSTEM system, int32 error,
//		double vitesse) {
//	pidSystemValues * val;
//	double P, I, D;
//	double pwm;
//
//	error /= VTOPS_PER_TICKS;
//
//	//printf("motor_PID.c pid_Compute %d, err:%d ", system, error);
//	val = &(systemValues[system]);
//
//	printf("motor_PID.c pid_Compute pid error:%d kP:%f (vitesse:%f)\n", error,
//			val->conf.kP, vitesse);
//
//	P = error * val->conf.kP;
//	I = 0;
//	float kd = (float) val->conf.kD;
//
//	D = -vitesse * kd;
//	D = 0;
//	pwm = P + I + D;
//
//	pwm /= 256.0f;
//	printf("motor_PID.c pid_Compute pid P:%f I:%f D:%f -> pwm:%f\n", P, I, D,
//			pwm);
//	//bound the resulting pwm
//	if (pwm > MAX_PWM_VALUE) {
//		pwm = MAX_PWM_VALUE;
//	} else if (pwm < -MAX_PWM_VALUE) {
//		pwm = -MAX_PWM_VALUE;
//	}
//
//	return (int32) pwm;
//}

