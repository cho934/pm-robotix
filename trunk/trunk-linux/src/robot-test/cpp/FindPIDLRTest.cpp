/*!
 * \file
 * \brief Implémentation de la classe FindPIDLRTest..
 */

#include "FindPIDLRTest.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "../../common/c/encoder.h"
#include "../../common/c/robot.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::FindPIDLRTest::run(int argc, char *argv[])
{
	float Ap = 0.0;
	float Ai = 0.0;
	float Ad = 0.0;
	float Dp = 0.0;
	float Di = 0.0;
	float Dd = 0.0;
	int sec = 5;
	int posLmm = 0;
	int posRmm = 0;
	int useExtEnc = 0;

	if (argc < 12)
	{
		std::cout << "USAGE: PMX_TEST " << argv[1]
				<< " [L vit] [P] [I] [D]  [R vit] [P] [I] [D] [option:useExtEncoders=0] [option:sec:5s]"
				<< std::endl;
	}

	if (argc > 2)
	{
		posLmm = atoi(argv[2]);
		std::cout << "posLmm: " << atoi(argv[2]) << std::endl;
	}
	else
	{
		std::cout << "posLmm: " << std::flush;
		std::cin >> posLmm;
	}

	if (argc > 3)
	{
		Ap = atof(argv[3]);
		std::cout << "Ap: " << atof(argv[3]) << std::endl;
	}
	else
	{
		std::cout << "Ap: " << std::flush;
		std::cin >> Ap;
	}

	if (argc > 4)
	{
		Ai = atof(argv[4]);
		std::cout << "Ai: " << atof(argv[4]) << std::endl;
	}
	else
	{
		std::cout << "Ai: " << std::flush;
		std::cin >> Ai;
	}

	if (argc > 5)
	{
		Ad = atof(argv[5]);
		std::cout << "Ad: " << atof(argv[5]) << std::endl;
	}
	else
	{
		std::cout << "Ad: " << std::flush;
		std::cin >> Ad;
	}

	if (argc > 6)
	{
		posRmm = atoi(argv[6]);
		std::cout << "posRmm: " << atoi(argv[6]) << std::endl;
	}
	else
	{
		std::cout << "posRmm: " << std::flush;
		std::cin >> posRmm;
	}

	if (argc > 7)
	{
		Dp = atof(argv[7]);
		std::cout << "Dp: " << atof(argv[7]) << std::endl;
	}
	else
	{
		std::cout << "Dp: " << std::flush;
		std::cin >> Dp;
	}

	if (argc > 8)
	{
		Di = atof(argv[8]);
		std::cout << "Di: " << atof(argv[8]) << std::endl;
	}
	else
	{
		std::cout << "Di: " << std::flush;
		std::cin >> Di;
	}

	if (argc > 9)
	{
		Dd = atof(argv[9]);
		std::cout << "Dd: " << atof(argv[9]) << std::endl;
	}
	else
	{
		std::cout << "Dd: " << std::flush;
		std::cin >> Dd;
	}

	if (argc > 10)
	{
		useExtEnc = atoi(argv[10]);
		std::cout << "useExtEnc: " << atoi(argv[9]) << std::endl;
	}
	if (argc > 11)
	{
		sec = atoi(argv[10]);
		std::cout << "sec: " << atoi(argv[11]) << std::endl;
	}

	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "FindPIDADTest - " << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	//sleep(1);
	robot.start(useExtEnc);


	robot.base().setupPID_LR(Ap, Ai, Ad, Dp, Di, Dd);

	robot.base().printPosition();
	robot.base().findPidLR(posLmm, posRmm, sec);

	robot.base().assistedHandling();
	robot.stop();
	robot.base().printPosition();

	logger().info() << "End of RobotTest." << utils::end;
}

