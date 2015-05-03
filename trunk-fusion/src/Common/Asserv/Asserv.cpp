#include "Asserv.hpp"

#include <unistd.h>
#include <math.h>
#include <cstdlib>

#include "../../Log/Logger.hpp"

using namespace std;

/*!
 * \brief Constructor.
 */
Asserv::Asserv() :
		encoders_(*this), motors_(*this), distTicks_(0)
, diam_(31.7) //mm
,entraxe_(145.0) //mm
{
	//diam_ = 31.7; //en mm
	//entraxe_ = 145.0; //en mm

}

void Asserv::moveForward(int power, int timems)
{
	motors_.runMotorLeft(power, timems);
	motors_.runMotorRight(power, timems);
	usleep(1000 * timems);
}

void Asserv::moveD(int distmm, int power)
{
	//diametre chenille = 37mm
	//360 ticks => PI*D = PI*37mm
	// ?  <= distmm
	//mm * 360* ticks = 37PI

	float ticksf = (360.0 * distmm) / (M_PI * diam_);
	distTicks_ = (int) ticksf;
	logger().debug() << "GO : ticks=" << distTicks_ << logs::end;
	motors_.setMotorLeftPosition(distTicks_, power);
	motors_.setMotorRightPosition(distTicks_, power);

}

void Asserv::waitMoveDTrajectory()
{
	int arrived = 0;
	long l = 0;
	long r = 0;

	//attente de la position
	while (!arrived)
	{
		//test if adversary then pause

		//calculate arrived or not
		l = encoders_.getLeftEncoder();
		r = encoders_.getRightEncoder();
		if (((abs(l) + abs(r)) / 2) >= abs(distTicks_))
		{
			arrived = 1;
		}
		usleep(500);
	}

	l = encoders_.getLeftEncoder();
	r = encoders_.getRightEncoder();

	logger().debug() << "Arrived : l=" << l << " r=" << r << "   l=" << (l / 360.0 * (diam_ * M_PI))
			<< "mm r=" << (r / 360.0 * (diam_ * M_PI)) << "mm" << logs::end;
}

void Asserv::turn(float degree, int power)
{
	//float entraxe = (360.0 * entraxemm) / (M_PI * diam);

	float ticksf = (entraxe_ * degree) / diam_;
	int ticks = (int) ticksf;
	logger().debug() << "ticksf=" << ticksf << "  ticks=" << ticks << logs::end;
	motors_.setMotorLeftPosition(-ticks, power);
	motors_.setMotorRightPosition(ticks, power);

	int arrived = 0;
	long l = 0;
	long r = 0;
	//attente de la position
	while (!arrived)
	{
		l = encoders_.getLeftEncoder();
		r = encoders_.getRightEncoder();
		if (((abs(l) + abs(r)) / 2) + 1 >= abs(ticks))
		{
			arrived = 1;
		}
		usleep(500);
	}

	l = encoders_.getLeftEncoder();
	r = encoders_.getRightEncoder();

	logger().debug() << "l=" << l << "  r=" << r << logs::end;
	logger().debug() << "l=" << (l / 360.0 * (diam_ * M_PI)) << "mm  r="
			<< (r / 360.0 * (diam_ * M_PI)) << "mm" << logs::end;

}

void Asserv::turnLeft(float degree, int power)
{
	turn(degree, power);
}

void Asserv::turnRight(float degree, int power)
{
	turn(-degree, power);
}

void Asserv::turnRightTime(int power, int timems)
{
	motors_.runMotorLeft(power, timems);
	motors_.runMotorRight(-power, timems);
	usleep(1000 * timems);
}

void Asserv::turnLeftTime(int power, int timems)
{
	motors_.runMotorLeft(-power, timems);
	motors_.runMotorRight(power, timems);
	usleep(1000 * timems);
}

void Asserv::emergencyStop()
{
	motors_.stopMotors();
}

/*
 void Asserv::start()
 {

 logger().debug("Asserv is started");
 }

 void Asserv::stop()
 {
 //TODO ramener motor et encoder sur asserv
 logger().debug("Asserv is stopped");
 }
 */
