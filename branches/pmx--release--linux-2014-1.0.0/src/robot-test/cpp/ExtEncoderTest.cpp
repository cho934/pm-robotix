/*!
 * \file
 * \brief Implémentation de la classe ExtEncoderTest.
 */

#include "../../common/cpp/ExtEncoder.hpp"
#include "ExtEncoderTest.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "../../common/cpp/Exception.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::ExtEncoderTest::run(int argc, char *argv[])
{
	int nb = 0;
	int timeSpan = 200;

	if (argc < 3)
	{
		std::cout << "USAGE: ROBOT_TEST " << argv[1] << " [nbOfTests] [option TimeSpan=200ms by default]" << std::endl;
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

	logger().info() << "-----------------------------" << utils::end;
	logger().info() << "ExtEncoderTest - Go" << utils::end;

	long long counterR = 0;
	long long counterL = 0;

	pmx::Robot &robot = pmx::Robot::instance();

	robot.encoderLeft().clearCounter();
	robot.encoderRight().clearCounter();

	for (int i = 0; i < nb; i++)
	{
		usleep(timeSpan * 1000);

		counterL = -robot.encoderLeft().readCounter();
		counterR = robot.encoderRight().readCounter();

		std::cout << "counterL = " << counterL << "\t\t counterR = " << counterR << std::endl;
	}

	logger().info() << "End of RobotTest." << utils::end;
}

