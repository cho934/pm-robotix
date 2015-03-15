#ifndef PMX_BOTSMALLPMX_ROBOTEXTENDED_HPP_
#define PMX_BOTSMALLPMX_ROBOTEXTENDED_HPP_

#include "../Common/Robot.hpp"
#include "SActionsExtended.hpp"
#include "SAsservExtended.hpp"

class SRobotExtended: public Robot
{
public:

	//on etend les actions possibles
	SActionsExtended actions;

	SAsservExtended asserv;
};

#endif

