#include "SupportSystem.hpp"

#include <unistd.h>

#include "../../Log/Logger.hpp"
#include "../Action.Driver/AServoDeviceDriver.hpp"
#include "Actions.hpp"

using namespace std;

SupportSystem::SupportSystem(Actions & actions) :
		AActionsElement(actions)
{
	servodevicedriver = AServoDeviceDriver::create();
}

SupportSystem::~SupportSystem()
{
}

void SupportSystem::incline(int power, int ramptimems)
{
	logger().debug() << "incline" << logs::end;
	servodevicedriver->setMotorPosition(50, ramptimems, power);
}

void SupportSystem::straighten(int power, int ramptimems)
{
	logger().debug() << "straighten" << logs::end;
	servodevicedriver->setMotorPosition(0, ramptimems, power);
}

void SupportSystem::resetPosition(int pos)
{
	logger().debug() << "resetPosition" << logs::end;
	servodevicedriver->resetEncoder(pos);
}

long SupportSystem::getPosition()
{
	logger().debug() << "getPosition" << logs::end;
	return servodevicedriver->getInternalEncoder();
}

void SupportSystem::stopMotor()
{
	servodevicedriver->stopMotor();
}
