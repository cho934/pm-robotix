/*!
 * \file
 * \brief Implémentation de la classe IrSensorsGroup.
 */

#include <cmath>
#include "IrSensorsGroup.hpp"
#include "Robot.hpp"
#include "RobotInOutFactory.hpp"

pmx::IrSensorsGroup::IrSensorsGroup(pmx::Robot & robot)
: ARobotElement(robot), timerIrSensorGroup_(PERIOD_IR, 0, this), initDone_(false),
irLeft_(robot, pmx::IRobotOut::PIN0, 30),
irCenter_(robot, pmx::IRobotOut::PIN1, 150),
irRight_(robot, pmx::IRobotOut::PIN2, 30),
irRearCenter_(robot, pmx::IRobotOut::PIN3, 30) {

    //temps de mise en route des capteurs GP2 IR
    waitSensors();
}

void
pmx::IrSensorsGroup::startTimer() {
    printf(" Thread IrSensorsGroup Start. \n");
    this->timerIrSensorGroup_.start();
}

void
pmx::IrSensorsGroup::stopTimer() {
    this->timerIrSensorGroup_.stopTimer();
}

void pmx::IrSensorsGroup::waitSensors() {
    usleep(60000);
    initDone_ = true;
}

void
pmx::IrSensorsGroup::onTimer(utils::Chronometer chrono) {
    logger().debug() << "onTimer :" << chrono.getElapsedTimeInMilliSec() << "ms" << utils::end;

    pmx::IRobotIn * robotIn = pmx::RobotInOutFactory::instance()->robotIn();

    this->getValues(robotIn, &this->irRight_);
    this->getValues(robotIn, &this->irLeft_);
    this->getValues(robotIn, &this->irCenter_);
    this->getValues(robotIn, &this->irRearCenter_);

    logger().debug() << "onTimer : " << chrono.getElapsedTimeInMilliSec()
            << " ms R=" << this->irRight_.distanceMm()
            << " mm C=" << this->irCenter_.distanceMm()
            << " mm L=" << this->irLeft_.distanceMm()
            << " mm RC=" << this->irRearCenter_.distanceMm()
            << " mm"
            << utils::end;

}

void
pmx::IrSensorsGroup::onTimerEnd(utils::Chronometer chrono) {

    logger().debug() << "onTimerEnd :" << chrono.getElapsedTimeInMilliSec() << "ms" << utils::end;
    irRight_.reset();
    irLeft_.reset();
    irCenter_.reset();
    irRearCenter_.reset();
}

void
pmx::IrSensorsGroup::getValues(pmx::IRobotIn * robotIn, pmx::IrSensor * irSensor) {

    double distMm = 0.0;
    int value = 0;
    value = robotIn->getValue(IRobotIn::ADC_USE, irSensor->adcPin());
    irSensor->voltage(value); //en volts
    distMm = this->gp2Convert(irSensor->type(), value);
    if (distMm >= 9999.0) {
        distMm = 9999.0;
    }
    irSensor->distanceMm((int) distMm);
}

double
pmx::IrSensorsGroup::gp2Convert(int type, int value) {
    double distanceMillimetre = 0.0;
    if (type == 80) {
        //distanceMillimetre = 270.0 * pow(value * 2.5 / 128.0 * 3.3 / 5.0, -1.1); //pour le 80cm //a simplifier si le calcul est bon pour 3.3V

        //distanceMillimetre = pow((valeur * 2.5 / 128.0), -1.1) * 270.0; //version 5V


        if (value > 2500)//saturation
        {
            distanceMillimetre = 55;

        }else if (value < 200)//saturation
        {
            distanceMillimetre = 600;
        }else {
            distanceMillimetre = 845000 * pow(value, -1.15);
        }
    }
    if (type == 30) {
        //!\todo version 30cm
        distanceMillimetre = 93620.1 * pow(value, -0.949);
        //y = 9362,1x-0,949
    }
    if (type == 150) {
        //!\todo version 150cm
        //y = 135300x-1,112
        distanceMillimetre = 1353000 * pow(value, -1.112);
    }

    return distanceMillimetre;
}
