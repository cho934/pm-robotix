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

	int mm = 0;
	int detect = 0;
	float vmax = 0.0;
	float acc = 0.0;
	float dec = 0.0;
	int speedT = 0;

	ostringstream out;
	logger().info() << "USAGE: " << argv[0] << " " << argv[1] << " " << argv[2]
			<< " [detect(0-1)] [dist(mm)] [SpeedTrackSys] [opt:Vmax] [opt:acc] [opt:dec]" << logs::end;

	if (argc <= 4)
	{
		mm = 100;
		speedT = 0;
	}
	else
	{
		out << " detect(0-1):";
		if (argc > 3)
		{
			detect = atoi(argv[3]);
			out << atoi(argv[3]);
		}
		else
		{
			logger().error() << out.str() << logs::end;
			std::cin >> detect;
			out << detect;
		}

		out << " - dist(mm):";
		if (argc > 4)
		{
			mm = atoi(argv[4]);
			out << mm;
		}
		else
		{
			logger().error() << out.str() << logs::end;
			std::cin >> mm;
			out << mm;
		}

		out << " SpeedTrackSys:";
		if (argc > 5)
		{
			speedT = atof(argv[5]);
			out << speedT;
		}

		out << " Vmax:";
		if (argc > 6)
		{
			vmax = atof(argv[6]);
			out << vmax;
		}

		out << " acc:";
		if (argc > 7)
		{
			acc = atof(argv[7]);
			out << acc;
		}

		out << " dec:";
		if (argc > 8)
		{
			dec = atof(argv[8]);
			out << dec;
		}

	}
	logger().info() << out.str() << logs::end;

	//fct... Bot-SmallPMX-EV3 T 8 0 650 500 0.6 0.2 0.05 pour monter la pente

	SRobotExtended &robot = SRobotExtended::instance();
	Data *data = new Data();
	Wait90SecondsAction* action = new Wait90SecondsAction(robot, (void *) data);
	robot.asserv().start(); //config + thread

	if (argc <= 5)
	{
		vmax = cc_motion_GetDefaultSpeed();
		acc = cc_motion_GetDefaultAccel();
		dec = cc_motion_GetDefaultDecel();
	}

	//lancement de l'etape Wait90Seconds
	action->start("Wait90SecondsAction");

	//robot.actions().supportSystem().resetPosition(5);
	//robot.actions().supportSystem().straighten(800, 1500);

	robot.actions().trackSystem().moveForward(speedT, 0);
	//sleep(1);
	cc_setPosition(0.0, 0.0, 0.0, 0);
	robot.asserv().base().printPosition();

	cc_setIgnoreFrontCollision(!detect);

	//robot.asserv().base().LineSpeedAcc(mm, 1.0, 1.0, 1.0);
	//robot.asserv().base().ArcRotate(-90, -200);

	TRAJ_STATE r;
	do
	{
		//r = robot.asserv().base().movexyteta(0, mm, 0, 0);

		r = robot.asserv().base().movexytetaSpeedAcc(0, mm, 0, 0, vmax, acc, dec);
		logger().info() << "r=" << r << logs::end;

		if (detect)
			if (r != TRAJ_OK)
			{
				logger().info() << "Wait" << logs::end;
				sleep(2);
			}
	} while (r != TRAJ_OK);


	robot.asserv().base().printPosition();
	robot.actions().trackSystem().stopMotor();
	//robot.actions().supportSystem().incline(900, 1500);
	robot.actions().redcarpetSystem().rightDeploy();
	robot.actions().redcarpetSystem().leftDeploy();
	robot.actions().redcarpetSystem().releaseAll();
	logger().info() << "Stop ..." << logs::end;
	robot.stop();

	logger().info() << this->name() << " - Happy End." << logs::end;
}
