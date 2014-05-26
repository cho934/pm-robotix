/*!
 * \file
 * \brief Implémentation de la classe FindPIDATest..
 */

#include "FindPIDATest.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "../../common/c/encoder.h"
#include "../../common/c/robot.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::FindPIDATest::run(int argc, char *argv[])
{
	float Dp = 0.0;
	float Di = 0.0;
	float Dd = 0.0;
	int sec = 5;
	int degrees = 0;
	float vmax = 0;
	float acc = 0;
	float dec = 0;
    int useExtEnc = 0;

	if (argc < 12)
	{
		std::cout << "USAGE: PMX_TEST " << argv[1]
				<< " [angle(deg)] [Vmax] [Acc] [Dec] [P] [I] [D] [option:useExtEncoders=0] [option:sec=5s]" << std::endl;
	}

	if (argc > 2)
	{
		degrees = atoi(argv[2]);
		std::cout << "angle: " << atoi(argv[2]) << std::endl;
	}
	else
	{
		std::cout << "angle: " << std::flush;
		std::cin >> degrees;
	}

	if (argc > 3)
	{
		vmax = atof(argv[3]);
		std::cout << "vmax: " << atof(argv[3]) << std::endl;
	}
	else
	{
		std::cout << "vmax: " << std::flush;
		std::cin >> vmax;
	}

	if (argc > 4)
	{
		acc = atof(argv[4]);
		std::cout << "acc: " << atof(argv[4]) << std::endl;
	}
	else
	{
		std::cout << "acc: " << std::flush;
		std::cin >> acc;
	}

	if (argc > 5)
	{
		dec = atof(argv[5]);
		std::cout << "dec: " << atof(argv[5]) << std::endl;
	}
	else
	{
		std::cout << "dec: " << std::flush;
		std::cin >> dec;
	}

	if (argc > 6)
	{
		Dp = atof(argv[6]);
		std::cout << "Dp: " << atof(argv[6]) << std::endl;
	}
	else
	{
		std::cout << "Dp: " << std::flush;
		std::cin >> Dp;
	}

	if (argc > 7)
	{
		Di = atof(argv[7]);
		std::cout << "Di: " << atof(argv[7]) << std::endl;
	}
	else
	{
		std::cout << "Di: " << std::flush;
		std::cin >> Di;
	}

	if (argc > 8)
	{
		Dd = atof(argv[8]);
		std::cout << "Dd: " << atof(argv[8]) << std::endl;
	}
	else
	{
		std::cout << "Dd: " << std::flush;
		std::cin >> Dd;
	}

	if (argc > 9)
	{
		useExtEnc = atoi(argv[9]);
		std::cout << "useExtEnc: " << atoi(argv[9]) << std::endl;
	}
	if (argc > 10)
	{
		sec = atoi(argv[10]);
		std::cout << "sec: " << atoi(argv[10]) << std::endl;
	}

	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "FindPIDATest - " << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	//sleep(1);
	robot.start(useExtEnc);

	robot.base().setupPID_AD( Dp, Di, Dd, 0.0, 0.0, 0.0);

	robot.base().printPosition();

	robot.base().RotateSpeedAcc(degrees, vmax, acc, dec);

	robot.stop();
	sleep(1);
	robot.base().printPosition();

	logger().info() << "End of RobotTest." << utils::end;
}

