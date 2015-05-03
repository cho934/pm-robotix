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


void MotorControl::setMotorLeftPosition(int tick, int power)
{
	asservdriver->setMotorLeftPosition(tick, power);
}

void MotorControl::setMotorRightPosition(int tick, int power)
{
	asservdriver->setMotorRightPosition(tick, power);
}


