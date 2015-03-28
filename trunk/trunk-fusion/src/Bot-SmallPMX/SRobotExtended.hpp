#ifndef PMX_BOTSMALLPMX_ROBOTEXTENDED_HPP_
#define PMX_BOTSMALLPMX_ROBOTEXTENDED_HPP_

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
};

#endif

