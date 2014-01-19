/*!
 * \file
 * \brief Implémentation de la classe IrSensor.
 */

#include "IrSensor.hpp"
#include "Robot.hpp"
#include <math.h>

pmx::IrSensorListener::IrSensorListener(pmx::IrSensor & irSensor)
: irSensor_(irSensor), nb_(0)
{}

pmx::IrSensor::IrSensor(pmx::Robot & robot, ushort adcPin, int type)
: ARobotElement(robot), active_(false), listenerStopped_(false),
        adcPin_(adcPin), type_(type), voltage_(0), distanceMm_(2000000.0),
        received_(false)
{
}

bool pmx::IrSensorListener::execute(IRobotIn * robotIn)
{
    if (nb_>20000) //boucle permettant de limiter le nombre d'appel a cette fonction
    {
        nb_= -1;
    }
    nb_++;
    if(nb_!=0)
    {
        return ! irSensor_.stop();
    }


    //logger().debug() << "execute " << utils::end;
    if (irSensor_.active() == false)
    {
        return ! irSensor_.stop(); //renvoi 0 pour supprimer le listener
    }
    
    logger().debug() << "pin: " << irSensor_.adcPin() << " type: " << irSensor_.type()
            << " val: " << irSensor_.voltage() << " dist: " << irSensor_.distanceMm() << utils::end;

    int value = robotIn->getValue(IRobotIn::ADC_USE, irSensor_.adcPin());

    irSensor_.voltage(value); //en volts

    double distanceMillimetre = 0.0;
    if (irSensor_.type() == 80)
    {
        //distanceMillimetre = 270.0 * pow(value * 2.5 / 128.0 * 3.3 / 5.0, -1.1); //pour le 80cm //a simplifier si le calcul est bon pour 3.3V

        //distanceMillimetre = pow((valeur * 2.5 / 128.0), -1.1) * 270.0; //version 5V


        if(value > 2500)//saturation
        {
            distanceMillimetre = 55;

        }else if(value < 200)//saturation
        {
            distanceMillimetre = 600;
        }
        else
        {
            distanceMillimetre = 845000 * pow(value, -1.15);
        }
    }
    if (irSensor_.type() == 30)
    {
        //!\todo version 30cm
        distanceMillimetre = 93620.1 * pow(value, -0.949);
        //y = 9362,1x-0,949
    }
    if (irSensor_.type() == 150)
    {
        //!\todo version 150cm
        //y = 135300x-1,112
        distanceMillimetre = 1353000 * pow(value, -1.112);
    }

    irSensor_.distanceMm((int) distanceMillimetre);

    irSensor_.received(true);

    logger().debug() << "pin: " << irSensor_.adcPin() << " type: " << irSensor_.type() << " val: " << irSensor_.voltage() << " dist: " << irSensor_.distanceMm() << utils::end;
    return ! irSensor_.stop(); //renvoi 0 pour supprimer le listener
}

void
pmx::IrSensor::getObjectDistance()
{
    this->stop(false);
    this->robot().addListener(new pmx::IrSensorListener(*this));
}

