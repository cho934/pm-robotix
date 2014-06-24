/*!
 * \file
 * \brief Implémentation de la classe DeviceServoLeft.
 */

#include "DeviceServoLeft.hpp"
#include "Robot.hpp"
#include "ServoMotorDxl.hpp"

pmx::DeviceServoLeft::DeviceServoLeft(pmx::Robot & robot)
		: ARobotElement(robot),
		  id_(8),
		  stateOpened_(0),
		  actionStopped_(0)
{
	logger().debug() << "DeviceServoLeft::DeviceServoLeft()" << utils::end;

	//initialise 1 seul servo pour cet objet.
	//long temp = pmx::ServoMotorDxl::instance().dxlGetTemperature(id_);
	//logger().info() << "Temperature dxl n°" << id_ << " =" << temp << utils::end;

}

void pmx::DeviceServoLeft::displayInfos()
{
	logger().debug() << "displayInfos" << utils::end;

	long int data = 0;

	pmx::ServoMotorDxl::instance().dxlSetAxLedOn(id_);


	data = pmx::ServoMotorDxl::instance().dxlGetBaud(id_);
	logger().debug() << "dxlGetBaud = " << data << utils::end;
	data = pmx::ServoMotorDxl::instance().dxlGetTemperature(id_);
	logger().debug() << "dxlGetTemp = " << data << utils::end;
	data = pmx::ServoMotorDxl::instance().dxlGetAxLed(id_);
	logger().debug() << "dxlGetAxLed = " << data << utils::end;
	data = pmx::ServoMotorDxl::instance().dxlGetVoltage(id_);
	logger().debug() << "dxlGetVolta = " << data << utils::end;
	data = pmx::ServoMotorDxl::instance().dxlGetPos(id_);
	logger().debug() << "dxlGetPos = " << data << utils::end;



	pmx::ServoMotorDxl::instance().dxlSetAxLedOff(id_);

	usleep(100000);
}

void pmx::DeviceServoLeft::turnMin()
{
	logger().debug() << "turn min" << utils::end;

	int finished = 0;
	long moving = 0;
	pmx::ServoMotorDxl::instance().dxlSetPos(id_, 100);
	while (pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_) == 1)
	{
		moving = pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_);
		finished = pmx::ServoMotorDxl::instance().dxlGetPos(id_);
		logger().debug() << "moving=" << moving << " finished=" << finished << utils::end;
		usleep(100000);
	}

	//TODO return pos
}

void pmx::DeviceServoLeft::turnMax()
{
	logger().debug() << "turn max" << utils::end;

	int finished = 0;
	long moving = 0;
	pmx::ServoMotorDxl::instance().dxlSetPos(id_, 900);
	while (pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_) == 1)
	{
		moving = pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_);
		finished = pmx::ServoMotorDxl::instance().dxlGetPos(id_);
		logger().debug() << "moving=" << moving << " finished=" << finished << utils::end;
		usleep(100000);
	}
}

