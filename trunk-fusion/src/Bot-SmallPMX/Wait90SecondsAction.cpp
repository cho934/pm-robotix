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

Wait90SecondsAction::Wait90SecondsAction(Robot& robot, void *data) :
		robot_(robot), data_(data)
{
}

void Wait90SecondsAction::execute()
{
	this->logger().debug() << "start" << logs::end;

	Data* sharedData = (Data*) data_;
	//SRobotExtended* robot = (SRobotExtended*) robot_;
	SRobotExtended& robot = dynamic_cast<SRobotExtended&>(robot_);
	//this->logger().info() << "Real execution start time: " << robot->chrono().getElapsedTimeInSec() << logs::end;

	//démarrage du chrono
	logger().info() << "Start Chronometer" << logs::end;
	robot.chrono().start();

	//ARU and adversary
	while (robot.chrono().getElapsedTimeInSec() <= 89)
	{

		//test ARU
		if (robot.actions().tirette().pressed())
		{
			//stop all robot
			robot.stop();

			sharedData->end90s(true);
			exit(0);
		}
		//test adversaire
		/*
		if (robot.actions().detectionSensor().isAdversaryDetected())
		{
			robot.asserv().emergencyStop();
			robot.asserv().setAdversaryDetected(1);
		}*/
		robot.asserv().setAdversaryDetected(robot.actions().detectionSensor().isAdversaryDetected());

		//set asserv().setadversaryDeteced(true);

		usleep(300000);
		//this->logger().info() << "chrono " << robot->chrono().getElapsedTimeInSec() << logs::end;
	}

	//End of PMX
	this->logger().info() << "Stop of the Robot : END of MATCH 90 !" << logs::end;
	this->logger().info() << "Real execution time: " << robot.chrono().getElapsedTimeInSec()
			<< logs::end;

	sharedData->end90s(true); //indique que l'action est effectuée au prog princ
	//sleep(1);
	this->logger().info() << "end90s...stop... " << robot.chrono().getElapsedTimeInSec()
			<< logs::end;
	//stop all robot to be sure...
	robot.stop();

}
