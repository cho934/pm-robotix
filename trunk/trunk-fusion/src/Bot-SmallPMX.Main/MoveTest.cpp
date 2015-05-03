/*!
 * \file
 * \brief Implémentation de la classe MotorTest.
 */

#include "MoveTest.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

#include "../Bot-SmallPMX/SActionsExtended.hpp"
#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/Action/TrackSystem.hpp"
#include "../Common/Asserv/Asserv.hpp"
#include "../Common/Asserv/MotorControl.hpp"
#include "../Log/Logger.hpp"

using namespace std;

void MoveTest::run(int argc, char *argv[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	int power = 0;
	int mm = 0;

	ostringstream out;

	if (argc == 1)
	{
		power = 300;
		mm = 100;

	}
	else
	{
		out << " power(-900/+900):";
		if (argc > 3)
		{
			power = atoi(argv[3]);
			out << atoi(argv[3]);
		}
		else
		{
			logger().error() << out.str() << logs::end;
			std::cin >> power;
			out << power;
		}

		out << " - dist(mm):";
		if (argc > 4)
		{
			mm = atoi(argv[4]);
			out << atoi(argv[4]);
		}
		else
		{
			logger().error() << out.str() << logs::end;
			std::cin >> mm;
			out << mm;
		}
	}
	logger().info() << out.str() << logs::end;

	SRobotExtended* robot = (SRobotExtended*) &SRobotExtended::instance();

	logger().info() << "moveD " << mm << " mm, power max=" << power << logs::end;

	//robot->actions.trackSystem().moveForward(power, timems);

	robot->asserv.moveD(mm, power);
	robot->asserv.waitMoveDTrajectory();


	logger().info() << "Stop" << logs::end;
	robot->asserv.motors().stopMotors();
	robot->actions.trackSystem().stopMotor();

	logger().info() << this->name() << " - Happy End." << logs::end;
}
