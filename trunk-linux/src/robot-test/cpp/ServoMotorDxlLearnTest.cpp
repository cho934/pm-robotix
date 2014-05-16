/*!
 * \file
 * \brief Implémentation de la classe ServoMotorDxlLearnTest..
 */

#include "ServoMotorDxlLearnTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::ServoMotorDxlLearnTest::run(int, char *[])
{
	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "ServoMotorDxlLearnTest - learn AX-12 position" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	robot.start();


	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

