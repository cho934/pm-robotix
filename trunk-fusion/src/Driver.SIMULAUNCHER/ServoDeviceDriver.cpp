//drivers...SIMULAUNCHER

#include "ServoDeviceDriver.hpp"

#include <unistd.h>
#include <ctime>
#include <iostream>
#include <string>

#include "../Common/Utils/Exception.hpp"

using namespace std;


AServoDeviceDriver * AServoDeviceDriver::create()
{
	static ServoDeviceDriver *instance = new ServoDeviceDriver();
	return instance;
}

ServoDeviceDriver::ServoDeviceDriver() :
		connected_(0)
{
	logger().debug() << "ServoDeviceDriver()" << logs::end;


}

void ServoDeviceDriver::setMotorPosition(int pos, int ramptimems, int power)
{

}

long ServoDeviceDriver::getInternalEncoder()
{
	return 0;
}

void ServoDeviceDriver::stopMotor()
{

}

void ServoDeviceDriver::resetEncoder(int pos)
{

}

int ServoDeviceDriver::getMotorCurrent()
{
	return 0;
}

void ServoDeviceDriver::enableHardRegulation(bool enable)
{

}
