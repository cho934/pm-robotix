/*
 * SRobotExtended.cpp
 *
 *  Created on: 3 mai 2015
 *      Author: pmx
 */

#include "SRobotExtended.hpp"

SRobotExtended::SRobotExtended()
{
	actions_ = new SActionsExtended();
	asserv_ = new SAsservExtended();
	//on ecrase les versions par default
	asserv_default = asserv_;
	actions_default = actions_;
}

//on etend le stop avec les actions supplémetaires
void SRobotExtended::stop() //TODO heritage / surcharge ?
{
	this->asserv().emergencyStop();

	this->actions().emergencyStop();
	this->actions().stop(); //manager
}

