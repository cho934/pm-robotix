/*!
 * \file
 * \brief Implémentation de la classe ArduinoTest.
 */

#include "../../common/cpp/GpioBoard.hpp"
#include "GpioBoardTest.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "../../common/cpp/Logger.hpp"
//#include "../../common/cpp/LoggerFactory.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::GpioBoardTest::run(int argc, char *argv[])
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
	logger().info() << "GpioBoardTest - " << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();

	//robot.gpioBoard().setup();
	int in0 = 0;
	int in1 = 0;
	int in2 = 0;
	int in7 = 0;
	for (int i = 0; i < nb; i++)
	{
		// drive some gpioboard tests
		logger().info() << "P0 ON" << utils::end;
		robot.gpioBoard().setOnP0(0);
		usleep(timeSpan * 1000);

		logger().info() << "P0 OFF" << utils::end;
		robot.gpioBoard().setOffP0(0);
		usleep(timeSpan * 1000);

		in0 = robot.gpioBoard().getValueP1(0);
		in1 = robot.gpioBoard().getValueP1(1);
		in2 = robot.gpioBoard().getValueP1(2);
		in7 = robot.gpioBoard().getValueP1(7);
		logger().info() << "                in0=" << in0 << " in1=" << in1 << " in2=" << in2 << " in7=" << in7 << utils::end;
		usleep(timeSpan * 1000);
	}


	logger().info() << "End of RobotTest." << utils::end;
}

