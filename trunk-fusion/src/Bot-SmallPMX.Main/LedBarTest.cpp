/*!
 * \file
 * \brief Implémentation de la classe LedBarTest.
 */

#include "../Common/Action/LedBar.hpp"
#include "LedBarTest.hpp"

#include <unistd.h>
#include <iostream>
#include <string>

#include "../Bot-SmallPMX/SActionsExtended.hpp"
#include "../Bot-SmallPMX/SRobotExtended.hpp"

using namespace std;

void LedBarTest::run(int, char *[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	SRobotExtended robot;

	robot.actions.ledbar().setOff(0);
	robot.actions.ledbar().setOff(1);
	usleep(500000);
	robot.actions.ledbar().setOn(0);
	robot.actions.ledbar().setOn(1);
	usleep(500000);
	robot.actions.ledbar().setOff(0);
	robot.actions.ledbar().setOff(1);
	usleep(500000);
	robot.actions.ledbar().set(0, LD_RED);
	usleep(1000000);
	robot.actions.ledbar().set(0, LD_ORANGE);
	usleep(1000000);
	robot.actions.ledbar().set(0, LD_GREEN);
	usleep(1000000);
	robot.actions.ledbar().setOff(0);
	usleep(1000000);

	robot.actions.ledbar().blink(5, 200000, LD_ORANGE);

	robot.actions.ledbar().k2mil(4, 100000, LD_RED);

	logger().info() << this->name() << " - Happy End." << logs::end;
}

