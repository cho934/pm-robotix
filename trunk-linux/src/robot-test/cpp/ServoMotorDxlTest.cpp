/*!
 * \file
 * \brief Implémentation de la classe ServoMotorDxlTest.
 */

#include "ServoMotorDxlTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::ServoMotorDxlTest::run(int, char *[])
{
	logger().info() << "------------------------------------" << utils::end;
	logger().info() << "ServoMotorDxlTest - AX12" << utils::end;

	try
	{
		pmx::Robot robot;

		robot.servoDxlTest().turnMin();
		//sleep(2);
		robot.servoDxlTest().turnMax();
		//sleep(2);

		robot.stop();

	} catch (utils::Exception * e)
	{
		logger().error() << "Exception : " << e->what() << utils::end;
	}
	logger().info() << "End of RobotTest." << utils::end;
}

