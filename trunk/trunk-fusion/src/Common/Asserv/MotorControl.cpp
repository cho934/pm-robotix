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

void MotorControl::moveForward(int power, int timems)
{
	runMotorLeft(power, timems);
	runMotorRight(power, timems);
	usleep(1000 * timems);
}

void MotorControl::turnRightTime(int power, int timems)
{
	runMotorLeft(power, timems);
	runMotorRight(-power, timems);
	usleep(1000 * timems);
}

void MotorControl::turnLeftTime(int power, int timems)
{
	runMotorLeft(-power, timems);
	runMotorRight(power, timems);
	usleep(1000 * timems);
}

void MotorControl::moveD(int distmm, int power)
{
	//diametre chenille = 37mm
	//360 ticks => PI*D = PI*37mm
	// ?  <= distmm
	//mm * 360* ticks = 37PI
	float diam = 31.7;

	float ticksf = (360.0 * distmm) / (M_PI * diam);
	int ticks = (int) ticksf;
	logger().debug() << "ticksf=" << ticksf << "  ticks=" << ticks << logs::end;
	asservdriver->setMotorLeftPosition(ticks, power);
	asservdriver->setMotorRightPosition(ticks, power);

	int arrived = 0;
	long l = 0;
	long r = 0;
	//attente de la position
	while (!arrived)
	{
		l = asservdriver->getLeftInternalEncoder();
		r = asservdriver->getRightInternalEncoder();
		if (((abs(l) + abs(r)) / 2) >= abs(ticks))
		{
			arrived = 1;
		}
		usleep(500);
	}

	l = asservdriver->getLeftInternalEncoder();
	r = asservdriver->getRightInternalEncoder();

	logger().debug() << "l=" << l << "  r=" << r << logs::end;
	logger().debug() << "l=" << (l / 360.0 * (diam * M_PI)) << "mm  r="
			<< (r / 360.0 * (diam * M_PI)) << "mm" << logs::end;

}

void MotorControl::turnLeft(float degree, int power)
{
	turn(degree, power);
}

void MotorControl::turnRight(float degree, int power)
{
	turn(-degree, power);
}

void MotorControl::turn(float degree, int power)
{
	float diam = 31.7;
	float entraxe = 145;//en mm
	//float entraxe = (360.0 * entraxemm) / (M_PI * diam);


	float ticksf = (entraxe * degree) / diam;
	int ticks = (int) ticksf;
	logger().debug() << "ticksf=" << ticksf << "  ticks=" << ticks << logs::end;
	asservdriver->setMotorLeftPosition(-ticks, power);
	asservdriver->setMotorRightPosition(ticks, power);

	int arrived = 0;
	long l = 0;
	long r = 0;
	//attente de la position
	while (!arrived)
	{
		l = asservdriver->getLeftInternalEncoder();
		r = asservdriver->getRightInternalEncoder();
		if (((abs(l) + abs(r)) / 2)+1 >= abs(ticks))
		{
			arrived = 1;
		}
		usleep(500);
	}

	l = asservdriver->getLeftInternalEncoder();
	r = asservdriver->getRightInternalEncoder();

	logger().debug() << "l=" << l << "  r=" << r << logs::end;
	logger().debug() << "l=" << (l / 360.0 * (diam * M_PI)) << "mm  r="
			<< (r / 360.0 * (diam * M_PI)) << "mm" << logs::end;

}
