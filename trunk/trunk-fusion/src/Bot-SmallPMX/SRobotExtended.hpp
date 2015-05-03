#ifndef PMX_S_ROBOTEXTENDED_HPP_
#define PMX_S_ROBOTEXTENDED_HPP_

#include "../Common/Robot.hpp"
#include "SActionsExtended.hpp"
#include "SAsservExtended.hpp"

class SRobotExtended: public Robot
{
public:

	static SRobotExtended & instance()
	{
		static SRobotExtended instance;
		return instance;
	}

	//on etend les actions possibles
	SActionsExtended actions;

	SAsservExtended asserv;

	//on etend le stop avec les actions supplémetaires
	void stop() //TODO heritage / surcharge ?
	{
		this->asserv.emergencyStop();

		this->actions.emergencyStop();
		this->actions.stop(); //manager
	}
};

#endif

