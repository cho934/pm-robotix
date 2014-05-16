/*!
 * \file
 * \brief Implémentation de la classe ServoMotorDxlObject.
 */

#include "ServoMotorDxlObject.hpp"
#include "Robot.hpp"

pmx::ServoMotorDxlObject::ServoMotorDxlObject(pmx::Robot & robot)
		: ARobotElement(robot), connected_(false), id_(7), stateOpened_(0), actionStopped_(0),
		  valMin_(0), valMed_(0), valMax_(0), valSpeed_(0)
{
	//logger().debug() << "ServoMotorDxlObject::ServoMotorDxlObject()" << utils::end;
}

void pmx::ServoMotorDxlObject::init()
{

	try
	{
		//initialise 1 seul servo pour cet objet.
		long temp = 0;
		temp = pmx::ServoMotorDxl::instance().dxlGetVoltage(id_);
		logger().debug() << "Volt dxl n°" << id_ << " =" << temp << utils::end;
		if (temp != 0 && temp > 9 && temp < 12)
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
	logger().debug() << "turn min" << utils::end;

	if (!connected_)
	{
		logger().error() << "turnMin ; (ID=" << id_ << " is NOT CONNECTED !" << utils::end;
		return;
	}

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

void pmx::ServoMotorDxlObject::turnMax()
{
	logger().debug() << "turn max" << utils::end;

	if (!connected_)
	{
		logger().error() << "turnMin ; (ID=" << id_ << " is NOT CONNECTED !" << utils::end;
		return;
	}

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

