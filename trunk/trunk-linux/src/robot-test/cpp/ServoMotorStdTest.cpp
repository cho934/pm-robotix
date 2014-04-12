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

	try
	{
		pmx::Robot robot;

		//TODO Problem with extEncoder and SPI !!!

		robot.servoTest().turnMin();

		robot.servoTest().turnMax();


		robot.stop();

	} catch (utils::Exception * e)
	{
		logger().error() << "Exception : " << e->what() << utils::end;
	}
	logger().info() << "End of RobotTest." << utils::end;
}

