/*!
 * \file
 * \brief Implémentation de la classe MoveLineVAccTest..
 */

#include "MoveLineVAccTest.hpp"

#include "../../common/c/encoder.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::MoveLineVAccTest::run(int argc, char *argv[])
{
	int dist = 0;
	float vmax = 0;
	float acc = 0;
	float dec = 0;
	int useExtEnc = 0;

	if (argc < 7)
	{
		std::cout << "USAGE: PMX_TEST " << argv[1] << " [dist] [Vmax] [Acc] [Dec] [option:useExternalEncoders=0]" << std::endl;
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
			useExtEnc = atoi(argv[6]);
			std::cout << "useExtEnc: " << atoi(argv[6]) << std::endl;
		}

	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "MoveTest - " << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	//sleep(1);
	robot.start(useExtEnc);

	robot.base().printPosition();

	robot.base().LineSpeedAcc(dist, vmax, acc, dec); // 1.4

	robot.stop();
	robot.base().printPosition();
	sleep(2);
	robot.base().printPosition();
	logger().info() << "End of RobotTest." << utils::end;
}

