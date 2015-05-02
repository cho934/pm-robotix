/*!
 * \file
 * \brief Implémentation de la classe Wait90SecondsAction.
 */

#include "../Common/State/Wait90SecondsAction.hpp"

#include <unistd.h>

#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/Robot.hpp"
#include "../Common/State/Data.hpp"
#include "../Common/Utils/Chronometer.hpp"
#include "../Log/Logger.hpp"

Wait90SecondsAction::Wait90SecondsAction(Robot* robot, void *data) :
		robot_(robot), data_(data)
{
}

void Wait90SecondsAction::execute()
{
	this->logger().info() << "start" << logs::end;
	Data* sharedData = (Data*) data_;
	SRobotExtended* robot = (SRobotExtended*) robot_;
	this->logger().info() << "Real execution start time: " << robot->chrono().getElapsedTimeInSec()
				<< logs::end;

	sleep(1);

	sharedData->end90s(true); //indique que l'action est effectuée au prog princ

	//End of PMX
	this->logger().info() << "Stop of the Robot : END of MATCH 90 !" << logs::end;
	this->logger().info() << "Real execution time: " << robot->chrono().getElapsedTimeInSec()
			<< logs::end;

	//Stop robot
	//logger().info() << "PMX - Stop All..." << logs::end;
	//robot->actions.stop();
	//TODO robot->asserv.stop();


}
