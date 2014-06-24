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
//! \file motor_PID.h
//! \author Julien Rouviere <gmail address : julien.rouviere@...>
//! \author ClubElek <http://clubelek.insa-lyon.fr>
// svn :
// $LastChangedBy$
// $LastChangedDate$
/******************************************************************************/

#ifndef _MOTOR_PID_H_
#define _MOTOR_PID_H_

#include "global.h"

//PID system are identified by a number
typedef uint8 PID_SYSTEM;

//structure used to stock configuration values of the PID system
typedef struct {
	double kP;
	double kI;
	double kD;
} pidConfig;

typedef struct {
	pidConfig conf;					//pid system configuration
	unsigned long lastTime;
	double lastInput;
	double lastOutput;
	double ITerm;
} pidSystemValues;

//! \brief Initialisation of the PID system
void pid_Init(void);

//! \brief Create a new PID system
//! \return The new system ID
PID_SYSTEM pid_Create(void);

//! \brief Configure kP value of the PID system
void pid_Config(PID_SYSTEM system, double kp, double ki, double kd);

//! \brief Compute the PID sum of a system
//!
//! \param system The system on which we compute the PID
//! \param setpoint reference value to reach
//! \param input mesured value
//! \return The new command to apply on the system (% pwm) between -100 and +100
double pid_Compute(PID_SYSTEM system, double setpoint, double input, double speed);

int32 pid_Compute_rcva_chaff(PID_SYSTEM system, int32 error, double vitesse);

int32 pid_ComputeRcva(PID_SYSTEM system, int32 error, int32 vitesse);

#endif//_MOTOR_PID_H_
