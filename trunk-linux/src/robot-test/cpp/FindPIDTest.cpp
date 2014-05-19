/*!
 * \file
 * \brief Implémentation de la classe FindPIDTest..
 */

#include "FindPIDTest.hpp"

#include "../../common/c/encoder.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::FindPIDTest::run(int, char *[])
{
	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "FindPIDTest - " << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	sleep(1);
	robot.start();

	int lRes = 3800;
	int rRes = 3800;
	float dist = 0.128f;

	if (useExternalEncoders) //TODO a mettre dans Base.cpp
	{
		lRes = 19885;
		rRes = 20360;
		dist = 0.250f;
	}
	else
	{
		lRes = 1121;
		rRes = 1192;
		dist = 0.300;

	}


	robot.base().begin(lRes, rRes, dist, 1);

	robot.base().printPosition();

	robot.base().pidD(100); //mm



	robot.stop();
	robot.base().printPosition();

	logger().info() << "End of RobotTest." << utils::end;
}

