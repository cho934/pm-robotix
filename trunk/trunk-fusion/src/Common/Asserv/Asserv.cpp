#include "Asserv.hpp"

#include <math.h>
#include <unistd.h>
#include <cstdlib>

#include "../../Log/Logger.hpp"

using namespace std;

/*!
 * \brief Constructor.
 */
Asserv::Asserv() :
		encoders_(*this), motors_(*this), distTicks_(0), entraxe_(0.145) //m
				, diam_(31.7) //mm
{
	adversaryDetected_ = false;
}

void Asserv::moveDTime(int power, int timems)
{
	motors_.runMotorLeft(power, timems);
	motors_.runMotorRight(power, timems);
	usleep(1000 * timems);
}

void Asserv::moveD(long destTick, long restTick, int power)
{
	distTicks_ = destTick;

	logger().debug() << "moveD GO : restTick=" << restTick << "  destTick=" << destTick
			<< logs::end;
	motors_.setMotorLeftPosition(restTick, power);
	motors_.setMotorRightPosition(restTick, power);
}

long Asserv::moveDWaitTrajectory()
{
	int arrived = 0;
	long l = 0;
	long r = 0;
	long m = 0;

	//attente de la position
	while (!arrived)
	{
		//calculate arrived or not
		l = encoders_.getLeftEncoder();
		r = encoders_.getRightEncoder();
		m = ((abs(l) + abs(r)) / 2.0);
		if (m >= abs(distTicks_))
		{
			arrived = 1;
			distTicks_ = 0;
			encoders_.reset();
		}

		//test if adversary then pause
		if (adversaryDetected_ == 1)
		{
			logger().debug() << "moveDWaitTrajectory emergencyStop m =" << m << " distTicks_="
					<< distTicks_ << "l=" << l << "r=" << r << logs::end;
			this->emergencyStop();
			sleep(1);
			return (distTicks_ - m);
		}

		usleep(100000);
	}

	l = encoders_.getLeftEncoder();
	r = encoders_.getRightEncoder();

	logger().debug() << "Arrived : l=" << l << " r=" << r << "   l=" << (l / 360.0 * (diam_ * M_PI))
			<< "mm r=" << (r / 360.0 * (diam_ * M_PI)) << "mm" << logs::end;
	return 0; //nbre de ticks restant
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

void Asserv::start()
{
	//config and start asserv
	int lRes = 0;
	int rRes = 0;
	float distRes = 0.0f;

	lRes = 3614; //nombre de tick par metre
	rRes = lRes;
	distRes = entraxe_; //entraxe en metre

	this->base().begin(lRes, rRes, distRes, 1, 0);

	logger().debug("Asserv is started");

}

void Asserv::stop()
{
	this->base().stop();
	motors_.runMotorLeft(0, 0);
	motors_.runMotorRight(0, 0);


	logger().debug("Asserv is stopped");
}

