/*!
 * \file
 * \brief Implémentation de la classe ServoMotorDxlObject.
 */

#include "ServoMotorDxlObject.hpp"

#include <unistd.h>

#include "Exception.hpp"
#include "Logger.hpp"
#include "ServoMotorDxl.hpp"

pmx::ServoMotorDxlObject::ServoMotorDxlObject(pmx::Robot & robot, int id, int min, int max)
		: ARobotElement(robot), connected_(false), id_(id), stateOpened_(0), actionStopped_(0), valMin_(min), valMed_(
				0), valMax_(max), valSpeed_(0)
{
	//logger().debug() << "--------ServoMotorDxlObject::ServoMotorDxlObject()" << utils::end;
}

void pmx::ServoMotorDxlObject::begin()
{
	try
	{
		//initialise 1 seul servo pour cet objet.
		long temp = 0;
		temp = pmx::ServoMotorDxl::instance().dxlGetVoltage(id_);
		logger().debug() << "Volt dxl n°" << id_ << " =" << temp << utils::end;
		if (temp != 0 && temp > 90 && temp < 110)
		{
			connected_ = true;
		}
		else
		{
			logger().error() << "init() - ServoMotorDxlObject NOT CONNECTED !!! (dxlGetVoltage test)" << utils::end;
		}
	} catch (utils::Exception * e)
	{

		logger().error() << "init()::Exception - ServoMotorDxlObject NOT CONNECTED !!! (dxlGetVoltage test)"
				<< e->what() << utils::end;
	}

}

void pmx::ServoMotorDxlObject::displayInfos()
{
	logger().debug() << "displayInfos" << utils::end;
	if (!connected_)
	{
		logger().error() << "displayInfos ; (ID=" << id_ << " is NOT CONNECTED !" << utils::end;
		return;
	}

	long int data = 0;

	pmx::ServoMotorDxl::instance().dxlSetAxLedOn(id_);

	data = pmx::ServoMotorDxl::instance().dxlGetBaud(id_);
	logger().info() << "dxlGetBaud = " << data << utils::end;
	data = pmx::ServoMotorDxl::instance().dxlGetTemperature(id_);
	logger().info() << "dxlGetTemp = " << data << utils::end;
	data = pmx::ServoMotorDxl::instance().dxlGetAxLed(id_);
	logger().info() << "dxlGetAxLed = " << data << utils::end;
	data = pmx::ServoMotorDxl::instance().dxlGetVoltage(id_);
	logger().info() << "dxlGetVolta = " << data << utils::end;
	data = pmx::ServoMotorDxl::instance().dxlGetPos(id_);
	logger().info() << "dxlGetPos = " << data << utils::end;

	pmx::ServoMotorDxl::instance().dxlSetAxLedOff(id_);

	usleep(100000);
}

void pmx::ServoMotorDxlObject::turnMin()
{
	logger().debug() << "turn min " << valMin_ << utils::end;

	if (!connected_)
	{
		logger().error() << "turnMin ; (ID=" << id_ << " is NOT CONNECTED !" << utils::end;
		return;
	}

	int finished = 0;
	long moving = 0;
	pmx::ServoMotorDxl::instance().dxlSetPos(id_, valMin_);
	while (pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_) == 1)
	{
		moving = pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_);
		finished = pmx::ServoMotorDxl::instance().dxlGetPos(id_);
		logger().debug() << "moving=" << moving << " finished=" << finished << utils::end;
		usleep(100000);
	}

//TODO return pos
}

void pmx::ServoMotorDxlObject::turnMax()
{
	logger().debug() << "turn max " << valMax_ << utils::end;

	if (!connected_)
	{
		logger().error() << "turnMin ; (ID=" << id_ << " is NOT CONNECTED !" << utils::end;
		return;
	}

	int finished = 0;
	long moving = 0;
	pmx::ServoMotorDxl::instance().dxlSetPos(id_, valMax_);
	while (pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_) == 1)
	{
		moving = pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_);
		finished = pmx::ServoMotorDxl::instance().dxlGetPos(id_);
		logger().debug() << "moving=" << moving << " finished=" << finished << utils::end;
		usleep(100000);
	}
}
void pmx::ServoMotorDxlObject::freeMotion()
{
	pmx::ServoMotorDxl::instance().dxlSetEnableTorque(id_, 0);
}

void pmx::ServoMotorDxlObject::enable()
{
	pmx::ServoMotorDxl::instance().dxlSetEnableTorque(id_, 1);
}

