/*!
 * \file
 * \brief Implémentation de la classe IrSensorsGroup.
 */

#include <cmath>
#include "IrSensorsGroup.hpp"
#include "Robot.hpp"

pmx::IrSensorsGroup::IrSensorsGroup(pmx::Robot & robot)
		: ARobotElement(robot), timerIrSensorGroup_(PERIOD_IR, 0, this),
		  initDone_(false),
		  irLeft_(robot, 0, 30),
		  irCenter_(robot, 1, 150),
		  irRight_(robot, 2, 30),
		  irRearCenter_(robot, 3, 30)
{
	//temps de mise en route des capteurs GP2 IR
	waitSensors();
}

void pmx::IrSensorsGroup::startTimer()
{
	//printf(" Thread IrSensorsGroup Start. \n");
	this->timerIrSensorGroup_.start();
}

void pmx::IrSensorsGroup::stopTimer()
{
	this->timerIrSensorGroup_.stopTimer();
}

void pmx::IrSensorsGroup::waitSensors()
{
	usleep(60000);
	initDone_ = true;
}

void pmx::IrSensorsGroup::onTimer(utils::Chronometer chrono)
{
	logger().debug() << "onTimer :" << chrono.getElapsedTimeInMilliSec() << "ms" << utils::end;

	this->getValue(&this->irRight_);
	this->getValue(&this->irLeft_);
	this->getValue(&this->irCenter_);
	this->getValue(&this->irRearCenter_);

	logger().debug() << "onTimer : " << chrono.getElapsedTimeInMilliSec() << " ms R=" << this->irRight_.distanceMm()
			<< " mm C=" << this->irCenter_.distanceMm() << " mm L=" << this->irLeft_.distanceMm() << " mm RC="
			<< this->irRearCenter_.distanceMm() << " mm" << utils::end;

}

void pmx::IrSensorsGroup::onTimerEnd(utils::Chronometer chrono)
{
	logger().debug() << "onTimerEnd :" << chrono.getElapsedTimeInMilliSec() << "ms" << utils::end;
	irRight_.reset();
	irLeft_.reset();
	irCenter_.reset();
	irRearCenter_.reset();
}

void pmx::IrSensorsGroup::getValue(pmx::IrSensor * irSensor)
{
	double distMm = 0.0;
	distMm = irSensor->getDistance();
	logger().debug() << "getValue: " << distMm << "mm" << utils::end;

}
