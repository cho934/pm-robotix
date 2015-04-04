#include "TrackSystem.hpp"

#include <unistd.h>

#include "../../Log/Logger.hpp"
#include "../Action.Driver/AMotorDeviceDriver.hpp"
#include "Actions.hpp"

using namespace std;

TrackSystem::TrackSystem(Actions & actions) :
		AActionsElement(actions)
{
	motordriver = AMotorDeviceDriver::create();
}

TrackSystem::~TrackSystem()
{
}

void TrackSystem::moveForward(int power, int timems)
{
	logger().debug() << "moveForward" << logs::end;
	motordriver->setMotorPower(power, timems);
	usleep(1000 * timems);
}

void TrackSystem::stopMotor()
{
	motordriver->stopMotor();
}
