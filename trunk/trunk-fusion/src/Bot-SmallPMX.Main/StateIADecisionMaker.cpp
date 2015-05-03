/*!
 * \file
 * \brief Implémentation de la classe StateIADecisionMaker.
 */

#include "../Common/State/StateIADecisionMaker.hpp"

#include <unistd.h>
#include <cstdio>

#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/State/Data.hpp"
#include "../Log/Logger.hpp"

IAutomateState*
StateIADecisionMaker::execute(Robot&r, void *data)
{
	logger().info() << "start 5" << logs::end;
	//IAutomateState* result;

	Data* sharedData = (Data*) data;
	SRobotExtended& robot = dynamic_cast<SRobotExtended&>(r);

	robot.actions.supportSystem().straighten(900, 1500);
	//robot->asserv.motors().moveD(550, 900);
	robot.asserv.moveD(550, 900);
	robot.asserv.waitMoveDTrajectory();
		//robot->actions.trackSystem().moveForward(300, 0);


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
