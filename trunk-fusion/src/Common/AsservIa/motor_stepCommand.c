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
//! \file motor_stepCommand.c
//! \author Julien Rouviere <gmail address : julien.rouviere@...>
//! \author ClubElek <http://clubelek.insa-lyon.fr>
// svn :
// $LastChangedBy$
// $LastChangedDate$
/******************************************************************************/

#include "motor_stepCommand.h"

#include "robot.hpp"

//well, genericity isn't always optimisation-friendly...
static long stopAt;

void ComputeStepOrder(StepCommand *out_order, int32 steporder, int seconds) {
	stopAt = currentTimeInMillis() + 1000 * seconds;
	*out_order = steporder;
}

BOOL GetStepOrder(StepCommand *order, int32 *out_order) {
	if (currentTimeInMillis() > stopAt) {
		return TRUE;
	}
	*out_order = *order;
	return FALSE;
}
