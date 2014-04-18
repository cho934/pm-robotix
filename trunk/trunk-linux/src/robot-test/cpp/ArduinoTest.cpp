/*!
 * \file
 * \brief Implémentation de la classe ArduinoTest.
 */

#include "ArduinoTest.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

void robottest::ArduinoTest::run(int, char *[])
{
	logger().info() << "-----------------------------------------------" << utils::end;
	logger().info() << "ArduinoTest - Communicate with the arduino board" << utils::end;

	try
	{
		pmx::Robot robot;

		for (int i = 0; i < 20000; i++)
		{
			// drive some arduino tests

			robot.arduinoBoard().launchCmd("L11", "LED1 on");
			usleep(500000);
			robot.arduinoBoard().launchCmd("L10", "LED1 off");
			usleep(500000);
			robot.arduinoBoard().launchCmd("L21", "LED2 on");
			usleep(500000);
			robot.arduinoBoard().launchCmd("L20", "LED2 off");
			usleep(500000);
		}

	} catch (utils::Exception * e)
	{
		logger().error() << "Exception : " << e->what() << utils::end;
	}
	logger().info() << "End of RobotTest." << utils::end;
}

