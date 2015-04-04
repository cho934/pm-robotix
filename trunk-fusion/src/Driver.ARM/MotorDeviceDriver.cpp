//drivers...EV3

#include "MotorDeviceDriver.hpp"

#include <unistd.h>
#include <ctime>
#include <iostream>
#include <string>

#include "../Common/Utils/Exception.hpp"

using namespace std;

AMotorDeviceDriver * AMotorDeviceDriver::create()
{
	static MotorDeviceDriver *instance = new MotorDeviceDriver();
	return instance;
}

MotorDeviceDriver::MotorDeviceDriver() :
		connected_(0)
{

}

// -900 < power < +900
void MotorDeviceDriver::setMotorPower(int power, int timems)
{
	power = -power;

	if ((power < -900))
	{
		cout << "ERROR setMotorLeftPower exceed -900!" << endl;
		power = -900;
	}
	else if (power > 900)
	{
		cout << "ERROR setMotorLeftPower exceed +900!" << endl;
		power = 900;
	}
	else
	{

	}
}

long MotorDeviceDriver::getInternalEncoder()
{
	return 0;
}

void MotorDeviceDriver::stopMotor()
{

}

void MotorDeviceDriver::resetEncoder()
{

}

int MotorDeviceDriver::getMotorCurrent()
{
	return 0;
}

void MotorDeviceDriver::enableHardRegulation(bool enable)
{

}
