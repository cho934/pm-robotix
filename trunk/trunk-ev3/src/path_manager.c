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
//! \file path_manager.c
//! \author Julien Rouviere <gmail address : julien.rouviere@...>
//! \author ClubElek <http://clubelek.insa-lyon.fr>
// svn :
// $LastChangedBy$
// $LastChangedDate$
/******************************************************************************/

#include "path_manager.h"
#include "motion.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

WAYPOINT nextWaypoint;
static BOOL waitingSemaphore;
static sem_t semWaypoint;
static TRAJ_STATE trajState;

void path_TriggerWaypoint(TRAJ_STATE state);

//collision handler
//static HANDLED ex_defaultCollisionCallback(void) {
//	motion_FreeMotion();
//
//	if (waitingSemaphore) {
//		path_TriggerWaypoint(TRAJ_COLLISION);
//	}
//
//	LOG_DEBUG("Collision Handler...");
//	return IT_HANDLED;
//}

void path_Init(void) {
	trajState = TRAJ_OK;
	waitingSemaphore = FALSE;
	sem_init(&semWaypoint, 0, 0);

}

void path_SetNextWaypoint(WAYPOINT *wp) {
	nextWaypoint = *wp;
}

//! Trigger the current waypoint
//! motion control internal function
void path_TriggerWaypoint(TRAJ_STATE state) {
	if (nextWaypoint.type != WP_NOT_SET) {
		trajState = state;
		sem_post(&semWaypoint);

	}
}

TRAJ_STATE path_WaitWaypoint() {
	if (RobotMotionState == TRAJECTORY_RUNNING) {
		//! Wait for waypoint semaphore
		waitingSemaphore = TRUE;

		sem_wait(&semWaypoint);

		waitingSemaphore = FALSE;

		return trajState;

	} else {
		return TRAJ_ERROR;
	}
}

TRAJ_STATE path_WaitEndOfTrajectory() {
	WAYPOINT *eot = (WAYPOINT *) calloc(1, sizeof(WAYPOINT));
	eot->type = WP_END_OF_TRAJ;
	eot->threshold = 0;
	path_SetNextWaypoint(eot);

	return path_WaitWaypoint();
}

void path_LaunchTrajectory(RobotCommand *traj) {
	sem_init(&semWaypoint, 0, 0);

	motion_SetCurrentCommand(traj);
}

void path_CancelTrajectory() {
	if (waitingSemaphore) {
		motion_FreeMotion();
		path_TriggerWaypoint(TRAJ_CANCELLED);
	}
}

void path_InterruptTrajectory() {
	if (waitingSemaphore) {
		motion_FreeMotion();
		path_TriggerWaypoint(TRAJ_INTERRUPTED);
	}
}

