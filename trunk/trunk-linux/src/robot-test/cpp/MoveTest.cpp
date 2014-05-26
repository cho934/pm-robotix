/*!
 * \file
 * \brief Implémentation de la classe MoveTest..
 */

#include "MoveTest.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "../../common/c/encoder.h"
#include "../../common/c/robot.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::MoveTest::run(int argc, char *argv[])
{
	int dist = 0;

	if (argc < 3)
	{
		std::cout << "USAGE: PMX_TEST " << argv[1] << " [PUISSANCE_MOTOR]" << std::endl;
	}

	if (argc > 2)
	{
		dist = atoi(argv[2]);
		std::cout << "dist: " << atoi(argv[2]) << std::endl;
	}
	else
	{
		std::cout << "dist: " << std::flush;
		std::cin >> dist;
	}

	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "MoveTest - " << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	//sleep(1);
	robot.start(0);

	robot.base().printPosition();

	long ileft = robot_getLeftInternalCounter();
	long iright = robot_getRightInternalCounter();
	long eleft = robot_getLeftExternalCounter();
	long eright = robot_getRightExternalCounter();
	logger().info() << "iL=" << ileft << "\tiR=" << iright << "\tieL=" << eleft << "\teR=" << eright << utils::end;

	robot_setMotorLeftSpeed(dist);
	robot_setMotorRightSpeed(dist);

	for (int i = 0; i < 50; i++)
	{
		ileft = robot_getLeftInternalCounter();
		iright = robot_getRightInternalCounter();
		eleft = robot_getLeftExternalCounter();
		eright = robot_getRightExternalCounter();
		logger().info() << "iL=" << ileft << "\tiR=" << iright << "\tieL=" << eleft << "\teR=" << eright << utils::end;
		usleep(100000);
	}

	robot_setMotorLeftSpeed(0);
	robot_setMotorRightSpeed(0);

	robot.stop();
	robot.base().printPosition();
	logger().info() << "End of RobotTest." << utils::end;
}

