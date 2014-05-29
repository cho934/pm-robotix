/*!
 * \file
 * \brief Implémentation de la classe Wait90SecondsAction.
 */

#include "Wait90SecondsAction.hpp"

#include <unistd.h>
#include <cstdlib>

#include "../../common/cpp/Chronometer.hpp"
#include "../../common/cpp/LedBar.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/ServoMotorDxlObject.hpp"
#include "Data.hpp"

pmx::Wait90SecondsAction::Wait90SecondsAction(pmx::Robot* robot, void *data)
		: robot_(robot), data_(data)
{
}

void
pmx::Wait90SecondsAction::execute()
{
	this->logger().info() << "start" << utils::end;
	pmx::Data* sharedData = (pmx::Data*) data_;

	sleep(30);
	this->logger().error() << "FUNNY ACTION..." << utils::end;

	//arret de tout les actions
	//this->robot_->stopDevices();

	//Gonfler le ballon pendant 10s
	//this->robot_->ledBar().startK2Mil(50000, 10000, false);

	this->robot_->ledBar().startAlternate(1000, 50000, 0xF0, 0x0F, false);
	robot_->servoDxlFiletLaunch().enable();
	robot_->servoDxlFiletLaunch().turnMax();
	robot_->servoDxlFiletLaunch().turnMax();
	robot_->servoDxlFiletLaunch().freeMotion();
	usleep(3000000);

	this->robot_->ledBar().stopAndWait(true);
	sharedData->end90s(true); //indique que l'action est effectuée au prog princ

	//End of PMX
	this->logger().info() << "Stop of the Robot : END of MATCH 90 !" << utils::end;
	this->logger().info() << "Real execution time: " << this->robot_->chronometerRobot().getElapsedTimeInSec()
			<< utils::end;

	//this->robot_->stop();
	//printf("Wait 90s EXIT\n");
	//exit(70);

}
