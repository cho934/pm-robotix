/*!
 * \file
 * \brief Implémentation de la classe StateIADecisionMaker.
 */

#include "../Common/State/StateIADecisionMaker.hpp"

#include <unistd.h>

#include "../Common/Asserv/Asserv.hpp"
#include "../Common/Asserv/Base.hpp"
#include "../Common/AsservIa/ccbase.h"
#include "../Common/AsservIa/path_manager.h"
#include "../Common/Robot.hpp"
#include "../Common/State/Data.hpp"
#include "../Common/Utils/Chronometer.hpp"
#include "../Log/Logger.hpp"
#include "SRobotExtended.hpp"

IAutomateState*
StateIADecisionMaker::execute(Robot&r, void *data)
{
	logger().info() << "start 5" << logs::end;

	Data* sharedData = (Data*) data;
	SRobotExtended& robot = dynamic_cast<SRobotExtended&>(r);

	logger().info() << "strategy = " << sharedData->strategy() << logs::end;
	if (sharedData->strategy() == "FirstSteps")
	{

		IAFirstSteps(r, data);
	}
	else if (sharedData->strategy() == "FirstCarpet")
	{
		IAFirstCarpet(r, data);

	}
	else
	{
		logger().error() << "Bad strategy..." << logs::end;
		exit(0);
	}

	//wait the execution Wait90
	while (!sharedData->end90s()) //&& robot.chronometerRobot().getElapsedTimeInSec() < 35)
	{
		logger().info() << "sharedData->end90s=" << sharedData->end90s() << " time="
				<< robot.chrono().getElapsedTimeInSec() << logs::end;
		usleep(1000000);
	}

	//logger().info() << "PMX - End temporary Pause..." << logs::end;
	//sleep(2);

	//Stop
	logger().info() << "PMX - Stop All..." << logs::end;
	robot.stop();

	return NULL;
}

void StateIADecisionMaker::IAFirstSteps(Robot& r, void * data)
{
	Data* sharedData = (Data*) data;
	SRobotExtended& robot = dynamic_cast<SRobotExtended&>(r);
	logger().debug() << "IAFirstSteps" << logs::end;

	robot.actions().supportSystem().straighten(900, 1500);

	robot.asserv().base().printPosition();
	TRAJ_STATE ret;
	do
	{
		ret = robot.asserv().base().movexyteta(0, 1120, 1000, 90);
		logger().debug() << "r=" << ret << logs::end;
		if (ret != TRAJ_OK)
			sleep(2);
	} while (ret != TRAJ_OK);
	robot.asserv().base().printPosition();

	do
	{
		ret = robot.asserv().base().movexyteta(0, 1120, 1360, 90);
		logger().debug() << "r=" << ret << logs::end;
		if (ret != TRAJ_OK)
			sleep(2);
	} while (ret != TRAJ_OK);
	robot.asserv().base().printPosition();

	//montée des marches

	robot.actions().supportSystem().incline(900, 1500);
	robot.actions().trackSystem().moveForward(500, 0);
	do
	{
		ret = robot.asserv().base().movexytetaSpeedAcc(0, 1120, 1968, 90, 0.8, 0.2, 0.05);
		logger().debug() << "r=" << ret << logs::end;
		if (ret != TRAJ_OK)
			sleep(2);
	} while (ret != TRAJ_OK);
	robot.asserv().base().printPosition();
	robot.actions().trackSystem().stopMotor();
	robot.actions().supportSystem().stopMotor();

	//depose tapis
	if (robot.getMyColor() == PMXGREEN)
	{
		//right
		robot.actions().redcarpetSystem().rightDeploy();
	}
	else if (robot.getMyColor() == PMXYELLOW)
	{
		//left
		robot.actions().redcarpetSystem().leftDeploy();
	}

	//go to other side
	do
	{
		ret = robot.asserv().base().movexyteta(0, 1367, cc_getY(), 90);
		logger().debug() << "r=" << ret << logs::end;
		if (ret != TRAJ_OK)
			sleep(2);
	} while (ret != TRAJ_OK);
	robot.asserv().base().printPosition();

	//depose tapis
	if (robot.getMyColor() == PMXGREEN)
	{
		//right
		robot.actions().redcarpetSystem().leftDeploy();
	}
	else if (robot.getMyColor() == PMXYELLOW)
	{
		//left
		robot.actions().redcarpetSystem().rightDeploy();
	}
}

void StateIADecisionMaker::IAFirstCarpet(Robot& r, void * data)
{
	Data* sharedData = (Data*) data;
	SRobotExtended& robot = dynamic_cast<SRobotExtended&>(r);
	logger().debug() << "IAFirstCarpet" << logs::end;
}

void StateIADecisionMaker::IASetupTableTest()
{
	logger().debug() << "IASetupTableTest" << logs::end;
}
void StateIADecisionMaker::IASetupHomologation()
{
	logger().debug() << "IASetupHomologation" << logs::end;
}
void StateIADecisionMaker::IASetupMatches()
{
	logger().debug() << "IASetupMatches" << logs::end;
}
