/*!
 * \file
 * \brief Implémentation de la classe MoveTest..
 */

#include "MoveTest.hpp"

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "../../common/c/ccbase.h"
#include "../../common/c/robot_trajectory.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/SvgWriter.hpp"

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
	sleep(1);
	robot.start(0);

	robot.base().printPosition();
	utils::SvgWriter::writePosition(cc_getX(), cc_getY(), cc_getTheta(), utils::SVG_POS_ROBOT);

	/*
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
	 robot_setMotorRightSpeed(0);*/
	/*
	 RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	 //robot.base().SpeedControlLR(1.0, 1.0, 0.8, 0.0, 0, 0.0);

	 motion_SpeedControlLR(cmd, 2.0, 0.1, 0.2,  2.0, 0.1, 0.2);
	 //motion_SpeedControlLRDecel(cmd, 2.0, 0.9, 2.0, 0.1,  2.0, 0.9, 2.0, 0.1);
	 robot.base().launchAndEndAfterCmd(cmd);
	 */
/*
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	motion_ArcRotate(cmd, -M_PI / 2.0, -0.200);
	robot.base().launchAndEndAfterCmd(cmd);
*/
	robot.base().ArcRotate(-90, -550);

	//Ecriture dans le SVG
	utils::SvgWriter::writePosition(cc_getX(), cc_getY(), cc_getTheta(), utils::SVG_POS_ROBOT);

	robot.stop();
	robot.base().printPosition();
	logger().info() << "End of RobotTest." << utils::end;
}

