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

#define MAX_D_PERIOD 			64	        //maximum number of period for derivation computation,typedef   struct {pidConfig conf;					//pid system configurationint32 dValues[MAX_D_PERIOD]; //all the previous values of error (used for derivation)int32 errSum;					//sum of all the errorsint16 curDiff;					//current index in the dValues table} pidSystemValues;pidSystemValues systemValues[MAX_PID_SYSTEM_NUMBER];
//number of system created so far
PID_SYSTEM pid_Nb;

EXPORTED_FUNCTION void pid_Init() {
	pid_Nb = 0;

}

EXPORTED_FUNCTION PID_SYSTEM pid_Create() {
//no more available system
	if (pid_Nb >= MAX_PID_SYSTEM_NUMBER)
		return -1;

//init configuration variables
	systemValues[pid_Nb].conf.kP = 50;
	systemValues[pid_Nb].conf.kI = 5;
	systemValues[pid_Nb].conf.kD = 40;
	systemValues[pid_Nb].conf.dPeriod = 1;
	systemValues[pid_Nb].conf.iMax = 128000;
	systemValues[pid_Nb].curDiff = 0;

//init current state variables
	pid_ResetError(pid_Nb);

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

EXPORTED_FUNCTION void pid_Configure(PID_SYSTEM system, pidConfig config) {
	systemValues[system].conf = config;
}

EXPORTED_FUNCTION void pid_ConfigKP(PID_SYSTEM system, uint32 kp) {
	systemValues[system].conf.kP = kp;
}
EXPORTED_FUNCTION void pid_ConfigKI(PID_SYSTEM system, uint32 ki) {
	systemValues[system].conf.kI = ki;
}
EXPORTED_FUNCTION void pid_ConfigKD(PID_SYSTEM system, uint32 kd) {
	systemValues[system].conf.kD = kd;
}
EXPORTED_FUNCTION void pid_ConfigDPeriod(PID_SYSTEM system, uint8 dperiod) {
	systemValues[system].conf.dPeriod = dperiod;
}
EXPORTED_FUNCTION void pid_ConfigIMax(PID_SYSTEM system, int32 imax) {
	systemValues[system].conf.iMax = imax;
}

EXPORTED_FUNCTION pidConfig pid_GetConfig(PID_SYSTEM system) {
	return systemValues[system].conf;
}

// RCVA
EXPORTED_FUNCTION int32 pid_Compute(PID_SYSTEM system, int32 error,
int32 vitesse) {
	pidSystemValues * val;
	int32 P, I, D;
	int32 pwm;

	error /= VTOPS_PER_TICKS;

	//printf("motor_PID.c pid_Compute %d, err:%d ", system, error);
	val = &(systemValues[system]);

	printf("motor_PID.c pid_Compute pid error:%d kP:%d (vitesse:%d)\n", error,
			val->conf.kP, vitesse);

	P = error * val->conf.kP;
	I = 0;
	float kd = (float) val->conf.kD;
	if (kd < 1.0f) {
		kd = 1.0f;
	}
	//D = (int) ((-1.0f) * (((float) vitesse) / kd));
	D = 0;
	pwm = P + I + D;

	pwm /= 256;
	printf("motor_PID.c pid_Compute pid P:%d I:%d D:%d -> pwm:%d\n", P, I, D,
			pwm);
//bound the resulting pwm
	if (pwm > MAX_PWM_VALUE) {
		pwm = MAX_PWM_VALUE;
	} else if (pwm < -MAX_PWM_VALUE) {
		pwm = -MAX_PWM_VALUE;
	}

	return pwm;
}

EXPORTED_FUNCTION void pid_ResetError(PID_SYSTEM system) {
	int i;

	for (i = 0; i < MAX_D_PERIOD; i++) {
		systemValues[pid_Nb].dValues[i] = 0;
	}
	systemValues[pid_Nb].errSum = 0;
	systemValues[pid_Nb].curDiff = 0;
}

