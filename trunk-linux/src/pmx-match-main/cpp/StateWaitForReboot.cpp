/*!
 * \file
 * \brief Implémentation de la classe StateWaitForReboot.
 */

#include "StateWaitForReboot.hpp"

//#include <linux/limits.h>
#include <unistd.h>
#include <climits>
//#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "../../common/cpp/Adafruit_RGBLCDShield.hpp"
#include "../../common/cpp/Configuration.hpp"
#include "../../common/cpp/LedBar.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

pmx::IAutomateState*
pmx::StateWaitForReboot::execute(Robot& robot, void *)
{
	logger().info() << "Start" << utils::end;

	//TODO arret des moteurs

	robot.lcdBoard().setBacklight(LCD_ON);
	robot.lcdBoard().clear();
	robot.lcdBoard().print("PMX...GO !");

	try
	{
		char currentPath[PATH_MAX];
		getcwd(currentPath, PATH_MAX);

		robot.configure("pmx.conf.txt");
		logger().info() << "Current directory:" << currentPath << " : Configuration 'pmx.conf.txt' loaded."
				<< utils::end;
	} catch (utils::ConfigurationException* exception)
	{
		logger().error() << "Error in the configuration file" << utils::end;
		logger().error() << "Message: " << exception->what() << utils::end;
		std::cerr << "Error !! " << exception->what() << std::endl;

		robot.stop();
		printf("StateWaitForReboot EXIT\n");
		exit(60);
	}

	logger().info() << "=> Clic SELECT..." << utils::end;
	robot.lcdBoard().setCursor(0, 1);
	robot.lcdBoard().print("Clic SELECT...");
	robot.ledBar().startK2Mil(50000, 50000, false);
	//wait
	uint8_t buttons = 0;
	while (!(buttons & BUTTON_SELECT))
	{
		buttons = robot.lcdBoard().readButtons();
		if (buttons)
		{
			if (buttons & BUTTON_SELECT)
			{
				robot.lcdBoard().clear();
				robot.lcdBoard().setCursor(0, 0);
				robot.lcdBoard().print("NEXT ");
				//robot.lcdBoard().setBacklight(LCD_OFF);
			}
		}
	}

	robot.ledBar().startReset();
	robot.ledBar().stopAndWait(true);

	return this->getState("next");
}
