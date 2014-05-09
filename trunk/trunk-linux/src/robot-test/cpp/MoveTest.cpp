/*!
 * \file
 * \brief Implémentation de la classe MoveTest..
 */

#include "MoveTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::MoveTest::run(int, char *[])
{
	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "MoveTest - " << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	robot.start();


	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

