#ifndef PMX_BOTBIGPMX_ROBOTEXTENDED_HPP_
#define PMX_BOTBIGPMX_ROBOTEXTENDED_HPP_

#include "../Common/Robot.hpp"
#include "BActionsExtended.hpp"
#include "BAsservExtended.hpp"

class BRobotExtended: public Robot
{
public:

	//on etend les actions possibles
	BActionsExtended actions;

	BAsservExtended asserv;
};

#endif

