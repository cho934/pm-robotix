/*!
 * \file
 * \brief Implémentation de la classe FindPIDTest..
 */

#include "FindPIDTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::FindPIDTest::run(int, char *[])
{
	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "FindPIDTest - " << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	robot.start();
/*
	init(lRes, rRes, dist, 1);
				RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
				float meters = mm / 1000.0f;
				motion_StepOrderAD(cmd, 0.0f, meters / valueVTops, 5);

				launchAndEndAfterCmd(cmd);
	*/

	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

