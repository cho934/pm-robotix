/*!
 * \file
 * \brief Implémentation de la classe FindPIDDTest..
 */

#include "FindPIDDTest.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "../../common/c/encoder.h"
#include "../../common/c/robot.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::FindPIDDTest::run(int argc, char *argv[])
{
	float Dp = 0.0;
	float Di = 0.0;
	float Dd = 0.0;
	int sec = 5;
	int dist = 0;
	float vmax = 0;
	float acc = 0;
	float dec = 0;
    int useExtEnc = 0;

	if (argc < 12)
	{
		std::cout << "USAGE: PMX_TEST " << argv[1]
				<< " [dist(mm)] [Vmax] [Acc] [Dec] [P] [I] [D] [option:useExtEncoders=0/1]" << std::endl;
	}

	if (argc > 2)
	{
		dist = atoi(argv[2]);
		std::cout << "dist: " << atoi(argv[2]) << std::endl;
	}
	else
	{
		std::cout << "dist: " << std::flush;
		std::cin >> dist;
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
	/*if (argc > 10)
	{
		sec = atoi(argv[10]);
		std::cout << "sec: " << atoi(argv[10]) << std::endl;
	}*/


	//Fct ./ROBOT_TEST 13 300 0.05 0.005 0.005   150.0 0.0 1.2 / 188.0 0.0 1.9

	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "FindPIDDTest - " << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	//sleep(1);
	int asserv=1;
	robot.start(useExtEnc, asserv);

	robot.base().setupPID_AD(0.0, 0.0, 0.0, Dp, Di, Dd);

	robot.base().printPosition();

	robot.base().LineSpeedAcc(dist, vmax, acc, dec);
	//sleep(1);
	robot.base().assistedHandling();
	robot.stop();
	robot.base().printPosition();
	sleep(1);
	robot.base().printPosition();

	logger().info() << "End of RobotTest." << utils::end;
}

