/*!
 * \file
 * \brief Implémentation de la classe ServoMotorDxlTest.
 */

#include "ServoMotorDxlTest.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/ServoMotorDxlObject.hpp"

void robottest::ServoMotorDxlTest::run(int argc, char *argv[])
{
	int nb = 0;
	int timeSpan = 500;

	if (argc < 3)
	{
		std::cout << "USAGE: ROBOT_TEST " << argv[1]
				<< " [nbOfTests] [option TimeSpan=500ms by default]" << std::endl;
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

	logger().info() << "------------------------------------" << utils::end;
	logger().info() << "ServoMotorDxlTest - AX12" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();

	robot.servoDxlTest().enable();

	for (int i = 0; i < nb; i++)
	{
		//logger().info() << "displayInfos" << utils::end;
		robot.servoDxlTest().displayInfos();

		//usleep(timeSpan * 1000);

		logger().info() << "turnMin" << utils::end;
		robot.servoDxlTest().turnMin();
		usleep(timeSpan * 1000);

		logger().info() << "turnMax" << utils::end;
		robot.servoDxlTest().turnMax();
		usleep(timeSpan * 1000);

	}
	robot.servoDxlTest().freeMotion();

	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

