/*!
 * \file
 * \brief Implémentation de la classe GroveColorTest.
 */

#include "GroveColorTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::GroveColorTest::run(int, char *[])
{
	logger().info() << "----------------------------------------------" << utils::end;
	logger().info() << "GroveColorTest - Retrieve colors" << utils::end;

	uint8_t TCS3414values[4]; // [Clear,Red,Green,Blue]
	try
	{
		pmx::Robot robot;

		if (robot.groveColorSensor().isConnected())
		{

			for (int i = 0; i < 4; i++)
			{
				robot.groveColorSensor().TCS3414GetValues();

				logger().info() << "Clear: " << (int) TCS3414values[0] << " \tRed: " << (int) TCS3414values[1]
						<< " \tGreen: " << (int) TCS3414values[2] << " \tBlue:  " << (int) TCS3414values[3]
						<< utils::end;
				usleep(500000);
			}
		}
		else
		{
			logger().info() << "groveColorSensor not connected !" << utils::end;
		}
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception : " << e->what() << utils::end;
	}

	logger().info() << "End of RobotTest." << utils::end;
}

