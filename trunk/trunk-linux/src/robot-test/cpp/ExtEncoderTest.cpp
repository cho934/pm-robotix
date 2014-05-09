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

	try
	{

		unsigned long counterR = 0;
		unsigned long counterL = 0;
		unsigned long counterRold = 0;
		unsigned long counterLold = 0;

		long long right = 0;
		long long left = 0;

		pmx::Robot &robot = pmx::Robot::instance();

		robot.encoderLeft().clearCounter();
		robot.encoderRight().clearCounter();

		for (int i = 0; i < nb; i++)
		{
			usleep(timeSpan * 1000);

			counterL = robot.encoderLeft().readCounter();
			counterR = robot.encoderRight().readCounter();
			if (counterL > 4244897280 / 2)
			{
				left = -(((long long) 4244897280) - counterL);
			}
			else
			{
				left = counterL;
			}
			if (counterR > 4244897280 / 2)
			{
				right = -(((long long) 4244897280) - counterR);
			}
			else
			{
				right = counterR;
			}
			right = -right;

			std::cout << "left = " << left << " ------ right = " << right << "    counterL = " << counterL
					<< " ------ counterR = " << counterR

					//<< "----- statusL  = "
					//<< reinterpret_cast<void*>(statusL) << "------statusR  = " << reinterpret_cast<void*>(statusR)
					<< std::endl;

			counterRold = counterR;
			counterLold = counterL;

		}
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception : " << e->what() << utils::end;
	}

	logger().info() << "End of RobotTest." << utils::end;
}

