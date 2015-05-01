/*!
 * \file
 * \brief Implémentation de la classe Wait90SecondsAction.
 */

#include "Wait90SecondsAction.hpp"

#include <unistd.h>

#include "../../Log/Logger.hpp"
#include "../Robot.hpp"
#include "../Utils/Chronometer.hpp"
#include "Data.hpp"

Wait90SecondsAction::Wait90SecondsAction(Robot* robot, void *data) :
		robot_(robot), data_(data)
{
}

void Wait90SecondsAction::execute()
{
	this->logger().info() << "start" << logs::end;
	Data* sharedData = (Data*) data_;

	sleep(15);

	sharedData->end90s(true); //indique que l'action est effectuée au prog princ

	//End of PMX
	this->logger().info() << "Stop of the Robot : END of MATCH 90 !" << logs::end;
	this->logger().info() << "Real execution time: " << this->robot_->chrono().getElapsedTimeInSec()
			<< logs::end;


	//Stop robot


}
