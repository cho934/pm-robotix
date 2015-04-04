#include "MotorControl.hpp"

#include <unistd.h>

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

void MotorControl::moveForward(int power, int timems)
{
	runMotorLeft(power, timems);
	runMotorRight(power, timems);
	usleep(1000 * timems);
}

void MotorControl::turnRight(int power, int timems)
{
	runMotorLeft(power, timems);
	runMotorRight(-power, timems);
	usleep(1000 * timems);
}


void MotorControl::moveForward(int distmm)
{
	//start odo

}
