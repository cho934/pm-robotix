#ifndef PMX_BOTBIGPMX_ROBOTEXTENDED_HPP
#define PMX_BOTBIGPMX_ROBOTEXTENDED_HPP

#include "../Common/Robot.hpp"
#include "BActionsExtended.hpp"

class BRobotExtended: public Robot
{
public:

	//on etend les actions possibles
	BActionsExtended actions;

};

#endif

