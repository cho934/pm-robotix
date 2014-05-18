/*!
 * \file
 * \brief Implémentation de la classe Md25Test.
 */

#include "Md25EncoderTest.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "../../common/cpp/Chronometer.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Md25.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::Md25EncoderTest::run(int argc, char *argv[])
{
	float bat = 0;
	long encoder1 = 0;
	long encoder2 = 0;

	int nbtests;

	if (argc < 7)
	{
		std::cout << "USAGE: PMX_TEST " << argv[1] << " [nb tests] " << std::endl;
	}

	if (argc > 2)
	{
		nbtests = atoi(argv[2]);
		std::cout << "nb tests: " << atoi(argv[2]) << std::endl;
	}
	else
	{
		std::cout << "nb tests: " << std::flush;
		std::cin >> nbtests;
	}

	logger().info() << "--------------------" << utils::end;
	logger().info() << "Md25Test - Go" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();

	bat = robot.md25().getBatteryVolts();
	logger().info() << "bat  = " << bat << utils::end;


	for (int i = 0; i < nbtests; i++)
	{
		encoder1 = -robot.md25().ensureGetEncoder(0, MD25_ENCODER1_REG);
		encoder2 = -robot.md25().ensureGetEncoder(0, MD25_ENCODER2_REG);
		logger().info() << "getEnc1 L:" << encoder1 << "\tgetEnc2 R: " << encoder2 << utils::end;
		usleep(200000);
	}


	logger().info() << "End of RobotTest." << utils::end;
}

