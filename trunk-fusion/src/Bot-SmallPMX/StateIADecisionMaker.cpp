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
	//IAutomateState* result;

	Data* sharedData = (Data*) data;
	SRobotExtended& robot = dynamic_cast<SRobotExtended&>(r);

	robot.asserv().start(); //config + thread

	cc_setPosition(0.0, 0.0, 0.0, 0);
	robot.asserv().base().printPosition();


	int mm = 300;
	cc_setIgnoreFrontCollision(false);
	TRAJ_STATE ret;
	do
	{
		ret = robot.asserv().base().movexyteta(0, mm, 0, 90);
		logger().info() << "r=" << ret << logs::end;
		if (ret != TRAJ_OK)
			sleep(2);
	}while (ret != TRAJ_OK);

	robot.asserv().base().printPosition();

	//wait the execution Wait90
	while (!sharedData->end90s()) //&& robot.chronometerRobot().getElapsedTimeInSec() < 35)
	{
		//printf("sharedData->end90s=%d time=%f\n", sharedData->end90s(),
		//		robot->chrono().getElapsedTimeInSec());
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
