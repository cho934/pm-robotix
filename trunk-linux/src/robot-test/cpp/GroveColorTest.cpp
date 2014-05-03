/*!
 * \file
 * \brief Implémentation de la classe GroveColorTest.
 */

#include "GroveColorTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::GroveColorTest::run(int argc, char *argv[])
{
	int nb = 0;
	int timeSpan = 100;

	if (argc < 3)
	{
		std::cout << "USAGE: ROBOT_TEST " << argv[1] << " [nbOfTests] [option TimeSpan=100ms by default]" << std::endl;
	}

	if (argc > 2)
	{
		nb = atoi(argv[2]);
	}
	else
	{
		std::cout << "[nbOfTests] : " << std::flush;
		std::cin >> nb;
	}

	if (argc > 3)
	{
		timeSpan = atoi(argv[3]);
	}

	logger().info() << "----------------------------------------------" << utils::end;
	logger().info() << "GroveColorTest - Retrieve colors" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();

	for (int i = 0; i < nb; i++)
	{
		robot.groveColorSensor().TCS3414GetColor();

		logger().info() << "Illumin: " << (int)robot.groveColorSensor().TCS3414tristimulus()[1]
		         << " \tx: " 	<< (float)robot.groveColorSensor().TCS3414chromaticityCoordinates()[0]
		         << " \ty: " << (float)robot.groveColorSensor().TCS3414chromaticityCoordinates()[1]
		         << " \tRed: " << (int)robot.groveColorSensor().TCS3414values()[1]
		         << " \tGreen: " << (int)robot.groveColorSensor().TCS3414values()[2]
		         << " \tBlue:  " << (int)robot.groveColorSensor().TCS3414values()[3]
				 << " \tCCT:  " << (int)robot.groveColorSensor().CCT() << " K"
				 << " \tClear: " << (int)robot.groveColorSensor().TCS3414values()[0]

				 << utils::end;

		usleep(timeSpan * 1000);
	}

	logger().info() << "End of RobotTest." << utils::end;
}

