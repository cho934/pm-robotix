/*!
 * \file
 * \brief Implémentation de la classe MotorTest.
 */

#include "MoveTest.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/Asserv/Asserv.hpp"
#include "../Common/Asserv/Base.hpp"
#include "../Common/AsservIa/ccbase.h"
#include "../Common/State/Data.hpp"
#include "../Common/State/Wait90SecondsAction.hpp"
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

	SRobotExtended &robot = SRobotExtended::instance();

	//lancement de l'etape Wait90Seconds
	Data *data = new Data();
	Wait90SecondsAction* action = new Wait90SecondsAction(robot, (void *) data);

	action->start("Wait90SecondsAction");

	logger().info() << "moveD " << mm << " mm, power max=" << power << logs::end;

	robot.asserv().start(); //config + thread

	cc_setPosition(0.0, 0.0, 0.0, 0);
	robot.asserv().base().printPosition();

	cc_setIgnoreFrontCollision(false);
	TRAJ_STATE r;
	do
	{
		r = robot.asserv().base().movexyteta(0, mm, 0, 0);
		logger().info() << "r=" << r << logs::end;
		if (r == TRAJ_COLLISION)
			sleep(2);
	} while (r != TRAJ_OK);

	robot.asserv().base().printPosition();
/*
	do
	{
		r = robot.asserv().base().movexyteta(0, mm, 100, 0);
		logger().info() << "r=" << r << logs::end;
		if (r == TRAJ_COLLISION)
			sleep(2);
	} while (r != TRAJ_OK);

	robot.asserv().base().printPosition();

	do
	{
		r = robot.asserv().base().movexyteta(0, mm + 30, 100, 0);
		logger().info() << "r=" << r << logs::end;
		if (r == TRAJ_COLLISION)
			sleep(2);
	} while (r != TRAJ_OK);

	robot.asserv().base().printPosition();
*/
	logger().info() << "Stop ..." << logs::end;
	robot.stop();

	logger().info() << this->name() << " - Happy End." << logs::end;
}
