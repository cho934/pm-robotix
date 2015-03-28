#include "MotorControl.hpp"

using namespace std;

MotorControl::MotorControl(Asserv & asserv) :
		AAsservElement(asserv)
{
	asservdriver = AAsservDriver::create();
}

MotorControl::~MotorControl()
{
}

void MotorControl::runMotorLeft(int power, int timeus)
{
	asservdriver->setMotorLeftPower(power, timeus);
}

void MotorControl::runMotorRight(int power, int timeus)
{
	asservdriver->setMotorRightPower(power, timeus);
}

void MotorControl::stopMotors()
{
	asservdriver->stopMotorLeft();
	asservdriver->stopMotorRight();

}
