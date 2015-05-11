/*!
 * \file
 * \brief Implémentation de la classe ArduinoTest.
 */

#include "ArduinoTest.hpp"

#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "../../common/cpp/ArduinoBoard.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::ArduinoTest::run(int argc, char *argv[])
{
	int nb = 0;
	int timeSpan = 100;

	if (argc < 3)
	{
		std::cout << "USAGE: ROBOT_TEST " << argv[1] << " [nbOfTests] [option TimeSpan=100ms by default]" << std::endl;
	}

	if (argc > 2)
	{
		nb = atoi(argv[2]);
	}
	else
	{
		std::cout << "[nbOfTests] : " << std::flush;
		std::cin >> nb;
	}

	if (argc > 3)
	{
		timeSpan = atoi(argv[3]);
	}

	logger().info() << "-----------------------------------------------" << utils::end;
	logger().info() << "ArduinoTest - Communicate with the arduino board" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();

	for (int i = 0; i < nb; i++)
	{
		// drive some arduino tests
/*
		robot.arduinoBoardMega().launchCmd("L11", "LED1 on");
		logger().info() << "L11" << "LED1 on" << utils::end;
		usleep(timeSpan*1000);
		robot.arduinoBoardMega().launchCmd("L10", "LED1 off");
		logger().info() << "L10" << "LED1 off" << utils::end;
		usleep(timeSpan*1000);
		robot.arduinoBoardMega().launchCmd("L21", "LED2 on");
		logger().info() << "L21" << "LED2 on" << utils::end;
		usleep(timeSpan*1000);
		robot.arduinoBoardMega().launchCmd("L20", "LED2 off");
		logger().info() << "L20" << "LED2 off" << utils::end;
		usleep(timeSpan*1000);
		*/
	}

	logger().info() << "End of RobotTest." << utils::end;
}

