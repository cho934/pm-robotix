/*!
 * \file
 * \brief Implémentation de la classe Wait90SecondsAction.
 */

#include "Wait90SecondsAction.hpp"

#include <unistd.h>
//#include <cstdlib>

#include "../../common/c/ccbase.h"
#include "../../common/c/path_manager.h"
#include "../../common/cpp/Chronometer.hpp"
#include "../../common/cpp/LedBar.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/ServoMotorDxlObject.hpp"
#include "Data.hpp"

pmx::Wait90SecondsAction::Wait90SecondsAction(pmx::Robot* robot, void *data) :
		robot_(robot), data_(data)
{
}

void pmx::Wait90SecondsAction::execute()
{
	this->logger().info() << "start" << utils::end;
	pmx::Data* sharedData = (pmx::Data*) data_;

	logger().debug() << "Start Chronometer" << utils::end;
	//démarrage du chrono
	robot_->chronometerRobot().start();

	sleep(5);

	/*
	 this->robot_->ledBar().startAlternate(1000, 50000, 0xF0, 0x0F, false);

	 usleep(3000000);

	 this->robot_->ledBar().stopAndWait(true);
	 */

	//End of PMX
	this->logger().info() << "Stop of the Robot : END of MATCH 90 !" << " Real execution time: "
			<< this->robot_->chronometerRobot().getElapsedTimeInSec() << utils::end;

	robot_->base().stop(); //TODO robot.base().stop();
	this->robot_->stop();

	sharedData->end90s(true); //indique que l'action est effectuée au prog princ
	//printf("Wait 90s EXIT\n");
	usleep(500000);
	exit(0);

}
