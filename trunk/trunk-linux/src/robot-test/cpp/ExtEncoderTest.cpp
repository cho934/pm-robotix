/*!
 * \file
 * \brief Implémentation de la classe ExtEncoderTest.
 */

#include "ExtEncoderTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::ExtEncoderTest::run(int, char *[])
{
	logger().info() << "-----------------------------" << utils::end;
	logger().info() << "ExtEncoderTest - Go" << utils::end;

	try
	{
		unsigned char statusL = 0;
		unsigned long counterL = 0;
		unsigned char statusR = 0;
		unsigned long counterR = 0;

		pmx::Robot robot;

		robot.encoderLeft().clearCounter();
		robot.encoderRight().clearCounter();

		for (int i = 0; i < 20000; i++)
		{
			usleep(5000);

			counterL = robot.encoderLeft().readCounter();
			statusL = robot.encoderLeft().readStatus();

			counterR = robot.encoderRight().readCounter();
			statusR = robot.encoderRight().readStatus();

			std::cout << "counterL = " << counterL << " ------ counterR = " << counterR << "----- statusL  = "
					<< reinterpret_cast<void*>(statusL) << "------statusR  = " << reinterpret_cast<void*>(statusR)
					<< std::endl;
		}
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception : " << e->what() << utils::end;
	}

	logger().info() << "End of RobotTest." << utils::end;
}

