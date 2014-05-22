/*!
 * \file
 * \brief Implémentation de la classe StateInitialize.
 */

#include "StateInitialize.hpp"
#include "StateIADecisionMaker.hpp"
#include <stdint.h>

#include "../../common/cpp/Adafruit_RGBLCDShield.hpp"
#include "../../common/cpp/LedBar.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/RobotColor.hpp"

pmx::IAutomateState*
pmx::StateInitialize::execute(Robot& robot, void *)
{
	this->logger().info() << "start" << utils::end;
	bool error = false;

	robot.lcdBoard().setBacklight(LCD_ON);
	robot.lcdBoard().clear();
	robot.lcdBoard().print("PMX...Initialize !");

	//actions d'initialisation
	logger().debug() << "Initialize mechanical..." << utils::end;
	//TODO Initialize mechanical
	logger().debug() << "End Initialize mechanical." << utils::end;

	logger().debug() << "Initialize color..." << utils::end;

	//prise en compte de la couleur de match
	logger().debug() << "=> Choose PMX COLOR..." << utils::end;
	robot.lcdBoard().setCursor(0, 1);
	robot.lcdBoard().print("COLOR ?");
	robot.ledBar().startK2Mil(50000, 50000, false);

	robot.myColorIs(pmx::PMXNOCOLOR);

	//wait
	uint8_t buttons = 0;
	while (!(buttons & BUTTON_SELECT) || robot.myColor() == pmx::PMXNOCOLOR)
	{
		buttons = robot.lcdBoard().readButtons();
		if (buttons)
		{
			if (buttons & BUTTON_LEFT)
			{
				robot.lcdBoard().setCursor(0, 1);
				robot.lcdBoard().print("COLOR YELLOW ");
				robot.myColorIs(pmx::PMXYELLOW);
				logger().info() << "=> YELLOW..." << utils::end;
			}
			if (buttons & BUTTON_RIGHT)
			{
				robot.lcdBoard().setCursor(0, 1);
				robot.lcdBoard().print("COLOR RED     ");
				robot.myColorIs(pmx::PMXRED);
				logger().info() << "=> RED..." << utils::end;
			}
			if (buttons & BUTTON_SELECT)
			{
				//robot.lcdBoard().clear();
				//robot.lcdBoard().setCursor(0, 0);
				//robot.lcdBoard().print("NEXT ");
				//robot.lcdBoard().setBacklight(LCD_OFF);
			}
		}
	}

	robot.ledBar().startReset();
	robot.ledBar().stop(true);

	logger().debug() << "color:" << robot.myColor() << utils::end;

	logger().debug() << "End Initialize color." << utils::end;

	/*
	 if (error)
	 {
	 //error and reboot
	 return this->getState("waitForReboot");
	 }
	 else
	 {

	 logger().info() << "=> Clic RESET..." << utils::end;
	 robot.ledBar().startK2Mil(50000, 50000, false);

	 robot.rebootContact().wait();
	 //attente d'un clic (seuil bas + seuil haut)
	 while (!robot.rebootContact().state())
	 {
	 usleep(10000);
	 }
	 while (robot.rebootContact().state())
	 {
	 usleep(10000);
	 }
	 robot.rebootContact().stop(true); //arrete le listener associé.
	 robot.ledBar().stopAndWait(true);
	 robot.ledBar().reset();

	 return this->getState("next");
	 } */
	return this->getState("next");
}
