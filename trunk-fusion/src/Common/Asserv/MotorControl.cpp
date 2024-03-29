#include "MotorControl.hpp"

#include <unistd.h>
#include <math.h>

using namespace std;

MotorControl::MotorControl(Asserv & asserv) :
		AAsservElement(asserv)
{
	asservdriver = AAsservDriver::create();
}

MotorControl::~MotorControl()
{
}

void MotorControl::runMotorLeft(int power, int timems)
{
	asservdriver->setMotorLeftPower(power, timems);
}

void MotorControl::runMotorRight(int power, int timems)
{
	asservdriver->setMotorRightPower(power, timems);
}

void MotorControl::stopMotors()
{
	asservdriver->stopMotorLeft();
	asservdriver->stopMotorRight();
}


void MotorControl::setMotorLeftPosition(long tick, int power)
{
	asservdriver->setMotorLeftPosition(tick, power);
}

void MotorControl::setMotorRightPosition(long tick, int power)
{
	asservdriver->setMotorRightPosition(tick, power);
}


