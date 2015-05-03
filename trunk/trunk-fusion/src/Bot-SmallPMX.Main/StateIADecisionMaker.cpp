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
	SRobotExtended* robot = (SRobotExtended*) &r;





	//wait the execution Wait90
	while (!sharedData->end90s()) //&& robot.chronometerRobot().getElapsedTimeInSec() < 35)
	{
		//printf("sharedData->end90s=%d time=%f\n", sharedData->end90s(),
		//		robot->chrono().getElapsedTimeInSec());
		logger().info() << "sharedData->end90s=" << sharedData->end90s() << " time="
				<< robot->chrono().getElapsedTimeInSec() << logs::end;
		usleep(1000000);
	}

	//Stop
	logger().info() << "PMX - Stop All..." << logs::end;
	robot->actions.stop();
	robot->asserv.motors().stopMotors();
	//TODO robot->asserv.stop();

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
