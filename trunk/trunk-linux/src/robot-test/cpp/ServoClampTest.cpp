/*!
 * \file
 * \brief Implémentation de la classe ServoClampTest.
 */

#include "ServoClampTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::ServoClampTest::run(int, char *[])
{
	logger().info() << "--------------------------------------------" << utils::end;
	logger().info() << "ServoClampTest - Test clamp" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();

	char currentPath[1024];
	getcwd(currentPath, 1024);
	robot.configure("robot-test.conf.txt");
	logger().info() << "configure " << currentPath << "/robot-test.conf.txt loaded" << utils::end;

	robot.clamp().closeAll();


	robot.clamp().readyToTakeLeftElement();
	robot.clamp().readyToTakeRightElement();

	sleep(3);
	robot.clamp().takeLeftElement();
	robot.clamp().takeRightElement();
	sleep(3);
	robot.clamp().readyToTakeLeftElement();
	robot.clamp().readyToTakeRightElement();
	sleep(3);
	robot.clamp().takeLeftElement();
	robot.clamp().takeRightElement();
	sleep(3);

	robot.clamp().pushLeft();
	robot.clamp().pushRight();

	robot.clamp().closeAll();

	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

