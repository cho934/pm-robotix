/*!
 * \file
 * \brief Implémentation de la classe FindPIDADTest..
 */

#include "FindPIDADTest.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "../../common/c/encoder.h"
#include "../../common/c/robot.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::FindPIDADTest::run(int argc, char *argv[])
{
	float Dp = 0.0;
	float Di = 0.0;
	float Dd = 0.0;
	int sec = 5;
	int dist = 0;
	float vmax = 0;
	float acc = 0;
	float dec = 0;

	if (argc < 11)
	{
		std::cout << "USAGE: PMX_TEST " << argv[1]
				<< " [dist(mm)] [Vmax] [Acc] [Dec] [P] [I] [D] [option:sec:5s]" << std::endl;
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
		sec = atoi(argv[9]);
		std::cout << "sec: " << atoi(argv[9]) << std::endl;
	}

	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "FindPIDADTest - " << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	//sleep(1);
	//robot.start();

	int lRes = 1121;
	int rRes = 1192;
	float distRes = 0.300f;

	if (useExternalEncoders) //TODO a mettre dans Base.cpp
	{
		lRes = 19885;
		rRes = 20360;
		distRes = 0.250f;
	}
	else
	{
		lRes = 1136;
		rRes = 1136;
		distRes = 0.300f;

	}
	/*
	 long left = robot_getLeftInternalCounter();
	 long right = robot_getRightInternalCounter();
	 logger().info() << "L=" << left << "\tR=" << right << utils::end;

	 robot_setMotorLeftSpeed(100);
	 robot_setMotorRightSpeed(100);
	 sleep(3);
	 left = robot_getLeftInternalCounter();
	 right = robot_getRightInternalCounter();
	 logger().info() << "L=" << left << "\tR=" << right << utils::end;
	 */

	robot.base().begin(lRes, rRes, distRes, 1);
	robot.base().setupPID_AD(0.0, 0.0, 0.0, Dp, Di, Dd);

	robot.base().printPosition();

	robot.base().MoveLineSpeedAcc(dist, vmax, acc, dec);

	robot.stop();
	sleep(1);
	robot.base().printPosition();

	logger().info() << "End of RobotTest." << utils::end;
}

