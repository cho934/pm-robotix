/*!
 * \file
 * \brief Implémentation de la classe StateIADecisionMaker.
 */

#include "StateIADecisionMaker.hpp"

#include <unistd.h>
#include <cstdio>

#include "../../Log/Logger.hpp"
#include "../Robot.hpp"
#include "../Utils/Chronometer.hpp"
#include "Data.hpp"


IAutomateState*
StateIADecisionMaker::execute(Robot&robot, void *data)
{
	//IAutomateState* result;

	Data* sharedData = (Data*) data;

	//detection adversaire
	//robot.irSensorsGroup().startTimer();

	//launch IA


	//robot.irSensorsGroup().stopTimer();

	//Arret des moteurs


	//wait the execution Wait90
	while (!sharedData->end90s()) //&& robot.chronometerRobot().getElapsedTimeInSec() < 35)
	{
		printf("sharedData->end90s=%d time=%f\n", sharedData->end90s(),
				robot.chrono().getElapsedTimeInSec());
		usleep(1000000);
	}

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
