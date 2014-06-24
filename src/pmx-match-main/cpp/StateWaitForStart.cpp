/*!
 * \file
 * \brief Implémentation de la classe StateWaitForStart.
 */

#include "StateWaitForStart.hpp"

#include <stdint.h>
#include <unistd.h>
#include <cstdio>

#include "../../common/c/ia.h"
#include "../../common/cpp/Adafruit_RGBLCDShield.hpp"
#include "../../common/cpp/Chronometer.hpp"
#include "../../common/cpp/GpioBoard.hpp"
#include "../../common/cpp/LedBar.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "Data.hpp"
#include "Wait90SecondsAction.hpp"

pmx::IAutomateState*
pmx::StateWaitForStart::execute(Robot& robot, void *data) {
	logger().info() << "start" << utils::end;

	pmx::Data* sharedData = (pmx::Data*) data;
	IAutomateState* result = NULL;

	//skip setup
	if (!sharedData->skipSetup()) {

		robot.lcdBoard().setBacklight(LCD_ON);
		robot.lcdBoard().clear();
		robot.lcdBoard().print("PMX...");
		if (robot.myColor() == pmx::PMXYELLOW) {
			robot.lcdBoard().print("YELLOW");
		} else if (robot.myColor() == pmx::PMXRED) {
			robot.lcdBoard().print("RED");
		}
		robot.lcdBoard().setCursor(0, 1);
		robot.lcdBoard().print("Wait for Start !");

		//GPIOBOARD
		robot.gpioBoard().setOnP0(0);

		robot.ledBar().startAlternate(100000, 100000, 0x81, 0x3C, false);
		//wait
		uint8_t buttons = 0;
		int in7 = 0;
		in7 = robot.gpioBoard().getValueP1(7);
		while (in7) //TODO ou pas de tir de ficelle
		{
			in7 = robot.gpioBoard().getValueP1(7);
			buttons = robot.lcdBoard().readButtons();
			//logger().info() << "in7=" << in7 << utils::end;
			if (buttons) {
				robot.ledBar().startReset();
				robot.ledBar().stop(true);
				ia_clear();
				return this->getState("rebootInitialize");
			}
			usleep(200000);
		}

		robot.lcdBoard().clear();
		robot.lcdBoard().print("PMX...GO GO GO !");

		robot.ledBar().startReset();
		robot.ledBar().stop(true);
		robot.gpioBoard().setOffP0(0);
		usleep(500000);

		robot.lcdBoard().setBacklight(LCD_OFF);
	}

	logger().info() << "Start Chronometer" << utils::end;
	//démarrage du chrono
	robot.chronometerRobot().start();

	//lancement de l'etape Wait90Seconds
	pmx::Wait90SecondsAction* action = new pmx::Wait90SecondsAction(&robot, (void *) sharedData);
	action->start("Wait90SecondsAction");

	result = this->getState("decisionMaker"); //IA

	return result;
}
