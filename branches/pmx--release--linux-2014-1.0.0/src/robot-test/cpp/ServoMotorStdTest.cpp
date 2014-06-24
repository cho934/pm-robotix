/*!
 * \file
 * \brief Implémentation de la classe ServoMotorStdTest.
 */

#include "ServoMotorStdTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::ServoMotorStdTest::run(int, char *[])
{
	logger().info() << "--------------------------------------------" << utils::end;
	logger().info() << "ServoMotorStdTest - Test servo" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();

	//TODO Problem with extEncoder and SPI !!!

	//robot.servoTest().turnMin();
	sleep(1);
	//robot.servoTest().turnMax();
	sleep(1);

	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

