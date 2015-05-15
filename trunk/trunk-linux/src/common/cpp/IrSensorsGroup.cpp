/*!
 * \file
 * \brief Implémentation de la classe IrSensorsGroup.
 */

#include "IrSensorsGroup.hpp"

#include <unistd.h>
#include <sstream>

#include "../c/ccbase.h"
#include "Base.hpp"
#include "Chronometer.hpp"
#include "Logger.hpp"
#include "Robot.hpp"
#include "SvgWriter.hpp"

pmx::IrSensorsGroup::IrSensorsGroup(pmx::Robot & robot)
		: ARobotElement(robot), timerIrSensorGroup_(PERIOD_IR, 0, this), initDone_(false)
, irLeft_(robot, 4, 30)
, irCenter_(robot, 5, 30)
, irRight_(robot, 0, 30)
//, irRearCenter_(robot, 1, 30)
{
	//temps de mise en route des capteurs GP2 IR
	waitSensors();
}

void pmx::IrSensorsGroup::startTimer() {
	this->timerIrSensorGroup_.start("IrSensorsGroup");
}

void pmx::IrSensorsGroup::stopTimer() {
	this->timerIrSensorGroup_.stopTimer();
}

void pmx::IrSensorsGroup::waitSensors() {
	usleep(60000);
	initDone_ = true;
}

void pmx::IrSensorsGroup::onTimer(utils::Chronometer chrono) {
	//logger().debug() << "onTimer :" << chrono.getElapsedTimeInMilliSec() << "ms" << utils::end;

	this->getValue(&this->irRight_);
	this->getValue(&this->irLeft_);
	this->getValue(&this->irCenter_);
	//this->getValue(&this->irRearCenter_);

	logger().debug() << "onTimer : " << chrono.getElapsedTimeInMilliSec() << " ms R=" << this->irRight_.distanceMm()
			<< " mm C=" << this->irCenter_.distanceMm() << " mm L=" << this->irLeft_.distanceMm()
			//<< " mm RC=" << this->irRearCenter_.distanceMm() << " mm"
			<< utils::end;

	//test detection opponent
	if (irCenter_.distanceMm() <= 270) {
		logger().info() << "===> opponent detected irCenter_" << utils::end;
		logger().info() << "onTimer : " << chrono.getElapsedTimeInMilliSec() << " ms R=" << this->irRight_.distanceMm()
				<< " mm C=" << this->irCenter_.distanceMm() << " mm L=" << this->irLeft_.distanceMm()
				//<< " mm RC=" << this->irRearCenter_.distanceMm() << " mm"
				<< utils::end;
		//log SVG
	//	std::ostringstream msg;
	//	msg << " C " << irCenter_.distanceMm() << "mm";
		//utils::SvgWriter::writeTextCustom(cc_getX(), cc_getY(), msg.str(), "red", "20");

		robot().base().collisionOccured(1);
	}
	if (irRight_.distanceMm() <= 170) {
		logger().info() << "=> opponent detected irRight_" << utils::end;
		logger().info() << "onTimer : " << chrono.getElapsedTimeInMilliSec() << " ms R=" << this->irRight_.distanceMm()
				<< " mm C=" << this->irCenter_.distanceMm() << " mm L=" << this->irLeft_.distanceMm()
				//<< " mm RC=" << this->irRearCenter_.distanceMm() << " mm"
				<< utils::end;
		robot().base().collisionOccured(0);
	}
	if (irLeft_.distanceMm() <= 170) {
		logger().info() << "=> opponent detected irLeft_" << utils::end;
		logger().info() << "onTimer : " << chrono.getElapsedTimeInMilliSec() << " ms R=" << this->irRight_.distanceMm()
				<< " mm C=" << this->irCenter_.distanceMm() << " mm L=" << this->irLeft_.distanceMm()
				//<< " mm RC=" << this->irRearCenter_.distanceMm() << " mm"
				<< utils::end;
		robot().base().collisionOccured(0);
	}
	/*
	if (irRearCenter_.distanceMm() <= 170) {
		logger().debug() << "=> opponent detected REAR " << utils::end;
		logger().debug() << "onTimer : " << chrono.getElapsedTimeInMilliSec() << " ms R=" << this->irRight_.distanceMm()
				<< " mm C=" << this->irCenter_.distanceMm() << " mm L=" << this->irLeft_.distanceMm() << " mm RC="
				<< this->irRearCenter_.distanceMm() << " mm" << utils::end;
		robot().base().collisionOccured(0);
	}*/

}

void pmx::IrSensorsGroup::onTimerEnd(utils::Chronometer chrono) {
	logger().debug() << "onTimerEnd :" << chrono.getElapsedTimeInMilliSec() << "ms" << utils::end;
	irRight_.reset();
	irLeft_.reset();
	irCenter_.reset();
	//irRearCenter_.reset();
}

void pmx::IrSensorsGroup::getValue(pmx::IrSensor * irSensor) {
	double distMm = 0.0;
	distMm = irSensor->getDistance();
//logger().debug() << "getValue: " << distMm << "mm" << utils::end;
}
