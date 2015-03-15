/*!
 * \file
 * \brief Implémentation de la classe LedBarTest.
 */

#include "../Common/Action/LedBar.hpp"
#include "LedBarTest.hpp"

#include <iostream>
#include <string>

#include "../Bot-BigPMX/BActionsExtended.hpp"
#include "../Bot-BigPMX/BRobotExtended.hpp"
#include "../Common/Action.Driver/ALedDriver.hpp"

using namespace std;

void LedBarTest::run(int, char *[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	BRobotExtended robot;
	robot.actions.ledbar().resetAll();

	robot.actions.ledbar().flash(0xFF, LED_OFF);
	robot.actions.ledbar().flash(0x00);

	robot.actions.ledbar().blink(2, 1000000);

	robot.actions.ledbar().k2mil(2, 10000, 1);
	robot.actions.ledbar().flash(0xAA, LED_GREEN);
	robot.actions.ledbar().flash(0xF0, LED_GREEN);
	robot.actions.ledbar().resetAll();

	robot.actions.start();

	robot.actions.ledbar().startAlternate(10, 100000, 0xF0, 0x0F, LED_GREEN, true);
	robot.actions.ledbar().startBlinkPin(10, 500000, 4, LED_ORANGE, true);
	robot.actions.stop();

	robot.actions.ledbar().resetAll();

	logger().info() << "Happy End." << logs::end;
}

