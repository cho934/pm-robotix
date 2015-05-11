/*!
 * \file
 * \brief Implémentation de la classe StateInitialize.
 */

#include "StateInitialize.hpp"

#include <stdint.h>

#include "../../common/cpp/Adafruit_RGBLCDShield.hpp"
#include "../../common/cpp/LedBar.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/RobotColor.hpp"
#include "Data.hpp"

pmx::IAutomateState*
pmx::StateInitialize::execute(Robot& robot, void *data)
{
	this->logger().info() << "start 02" << utils::end;
	pmx::Data* sharedData = (pmx::Data*) data;
	//bool error = false;

	if (!sharedData->skipSetup())
	{
		robot.lcdBoard().setBacklight(LCD_ON);
		robot.lcdBoard().clear();
		robot.lcdBoard().print("PMX...Initialize !");
	}

	robot.clamp().readyToTakeLeftElement();
	robot.clamp().readyToTakeRightElement();
	robot.servoDxlRight().turnMax();
	robot.servoDxlLeft().turnMax();
	robot.servoDxlRight().turnMin();
	robot.servoDxlLeft().turnMin();

	//skip setup
	if (!sharedData->skipSetup())
	{
		logger().debug() << "Initialize color..." << utils::end;

		//prise en compte de la couleur de match
		logger().debug() << "=> Choose PMX COLOR..." << utils::end;
		robot.lcdBoard().setCursor(0, 1);
		robot.lcdBoard().print("COLOR ?");
		robot.ledBar().startK2Mil(50000, 50000, false);

		robot.myColorIs(pmx::PMXNOCOLOR);

		//wait
		uint8_t buttons = robot.lcdBoard().readButtons();
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
					robot.lcdBoard().print("COLOR GREEN  ");
					robot.myColorIs(pmx::PMXGREEN);
					logger().info() << "=> GREEN..." << utils::end;
				}
				if (buttons & BUTTON_SELECT)
				{
					logger().info() << "=> SELECT..." << utils::end;
					//robot.lcdBoard().clear();
					//robot.lcdBoard().setCursor(0, 0);
					//robot.lcdBoard().print("NEXT ");
					//robot.lcdBoard().setBacklight(LCD_OFF);
				}
				if (buttons & BUTTON_DOWN)
				{

					logger().info() << "DOWN Initialize mechanical..." << utils::end;
					robot.clamp().readyToTakeLeftElement();
					robot.clamp().readyToTakeRightElement();
					//TODO rentrer pince latérale
					//TODO rentrer prise ball avant et arrière
					logger().info() << "End Initialize mechanical." << utils::end;
				}
				if (buttons & BUTTON_UP)
				{
					logger().info() << "UP Initialize mechanical..." << utils::end;

					logger().info() << "End Initialize mechanical." << utils::end;
				}
			}
			usleep(300000);
		}

		robot.ledBar().startReset();
		robot.ledBar().stop(true);
		logger().debug() << "End Initialize color." << utils::end;
	}

	if (robot.myColor() == pmx::PMXGREEN)
		logger().info() << "color: GREEN" << utils::end;
	if (robot.myColor() == pmx::PMXYELLOW)
		logger().info() << "color: YELLOW" << utils::end;
	if (robot.myColor() == pmx::PMXNOCOLOR)
	{
		logger().error() << "color: NOCOLOR" << utils::end;
		exit(0);
	}

	//Ajout des stratégies
	if (robot.myRunningMode() == pmx::ROBOTMATCHES)
	{
		logger().debug() << "ROBOTMATCHES" << utils::end;
		//configure IA
		sharedData->decisionMaker->IASetupMatches();
		robot.lcdBoard().print("PMX MATCH GO !");
	}
	else if (robot.myRunningMode() == pmx::ROBOTHOMOLOGATION)
	{
		logger().debug() << "ROBOTHOMOLOGATION" << utils::end;
		//configure IA
		sharedData->decisionMaker->IASetupHomologation();

		robot.lcdBoard().print("HOMOLOGATION GO !");
	}
	else if (robot.myRunningMode() == pmx::ROBOTTABLETEST)
	{
		logger().debug() << "ROBOTTABLETEST" << utils::end;
		//configure IA
		sharedData->decisionMaker->IASetupTableTest();
		robot.lcdBoard().print("TABLE TEST GO !");
	}

	return this->getState("next");
}
