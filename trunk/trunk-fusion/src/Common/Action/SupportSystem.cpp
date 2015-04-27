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

void SupportSystem::incline(int power, int timems)
{
	logger().debug() << "incline" << logs::end;
	servodevicedriver->setMotorPosition(50, timems);
}

void SupportSystem::straighten(int power, int timems)
{
	logger().debug() << "straighten" << logs::end;
	servodevicedriver->setMotorPosition(0, timems);
}

void SupportSystem::setPosition(int pos)
{
	logger().debug() << "setPosition" << logs::end;
	servodevicedriver->resetEncoder(pos);
}

void SupportSystem::stopMotor()
{
	servodevicedriver->stopMotor();
}
