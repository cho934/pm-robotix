/*!
 * \file
 * \brief Implémentation de la classe MoveTest..
 */

#include "MoveTest.hpp"

#include "../../common/c/encoder.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::MoveTest::run(int argc, char *argv[])
{
	int dist = 0;

	if (argc < 3)
		{
			std::cout << "USAGE: PMX_TEST " << argv[1]
					<< " [dist]" << std::endl;
		}

		if (argc > 2)
		{
			dist = atoi(argv[2]);
			std::cout << "degrees: " << atoi(argv[2]) << std::endl;
		}
		else
		{
			std::cout << "degrees: " << std::flush;
			std::cin >> dist;
		}


	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "MoveTest - " << utils::end;



	pmx::Robot &robot = pmx::Robot::instance();
	//sleep(1);
	robot.start();

	int lRes = 1191;//1121
	int rRes = 1192;//1192
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

	robot.base().printPosition();
	robot.base().begin(lRes, rRes, distRes, 1);


	robot.base().move(dist); //mm

	robot.stop();
	robot.base().printPosition();
	logger().info() << "End of RobotTest." << utils::end;
}

