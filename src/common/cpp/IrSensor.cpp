/*!
 * \file
 * \brief Implémentation de la classe IrSensor.
 */

#include <cmath>
#include "IrSensor.hpp"
#include "Robot.hpp"
#include "RobotInOutFactory.hpp"

pmx::IrSensorListener::IrSensorListener(pmx::IrSensor & irSensor)
: irSensor_(irSensor), nb_(0)
{}

pmx::IrSensor::IrSensor(pmx::Robot & robot, ushort adcPin, int type)
: ARobotElement(robot), active_(false), listenerStopped_(false),
        adcPin_(adcPin), type_(type), voltage_(0), distanceMm_(2000000.0),
        received_(false), timerIrSensor_(PERIOD_IR, 1000, this)
{
}

bool pmx::IrSensorListener::execute(IRobotIn * robotIn)
{
    if (nb_>1000) //boucle permettant de limiter le nombre d'appel a cette fonction
    {
        nb_= -1;
    }
    nb_++;
    if(nb_!=0)
    {
        //logger().debug() << "Ne rien faire !" << utils::end;
        return ! irSensor_.stopListener(); //renvoi 0 pour supprimer le listener
    }


    //logger().debug() << "execute " << utils::end;
    if (irSensor_.active() == false)
    {
        return ! irSensor_.stopListener(); //renvoi 0 pour supprimer le listener
    }
    
    int value = robotIn->getValue(IRobotIn::ADC_USE, irSensor_.adcPin());
    irSensor_.voltage(value); //en volts

    double distanceMillimetre = 0.0;
    distanceMillimetre = irSensor_.gp2Convert(irSensor_.type(), value);
    irSensor_.distanceMm((int) distanceMillimetre);

    irSensor_.received(true);

    logger().debug() << "pin: " << irSensor_.adcPin()
            << " type: " << irSensor_.type()
            << " val: " << irSensor_.voltage()
            << "V dist: " << irSensor_.distanceMm() << "mm "
            << utils::end;
    return ! irSensor_.stopListener(); //renvoi 0 pour supprimer le listener
}

void
pmx::IrSensor::getObjectDistance()
{
    this->stopListener(false);
    this->robot().addListener(new pmx::IrSensorListener(*this));
}

void
pmx::IrSensor::onTimer(utils::Chronometer)
{
    //logger().info() << "onTimer" << utils::end;

    pmx::IRobotIn * robotIn = pmx::RobotInOutFactory::instance()->robotIn();

    logger().info() << "onTimer robotIn" << utils::end;
    int count = 2;
    int tabvalue[count];
    int sumvalue = 0;
    for (int i= 0; i < count ; i++)
    {
        usleep(5000);
        tabvalue[i] = robotIn->getValue(IRobotIn::ADC_USE, this->adcPin());
        sumvalue += tabvalue[i];

        logger().info()
                << "i=" << i
                << " pin=" << this->adcPin()
            << " type=" << this->type()
            << " tabvalue=" << tabvalue[i]
            << " sumvalue=" << sumvalue
            << utils::end;
    }
    int value = 1.0 * (sumvalue) / count;
    this->voltage(value); //en volts
    double distanceMillimetre = 0.0;
    distanceMillimetre = this->gp2Convert(this->type(), value);

    logger().info()
                << "gp2Convert done." << sumvalue
            << utils::end;

    this->distanceMm((int) distanceMillimetre);

    logger().info() << "pin: " << this->adcPin()
            << " type: " << this->type()
            << " val: " << this->voltage()
            << "V dist: " << this->distanceMm() << "mm "
            << utils::end;
    
}


double
pmx::IrSensor::gp2Convert(int type, int value)
{
    double distanceMillimetre = 0.0;
    if (type == 80)
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
    if (type == 30)
    {
        //!\todo version 30cm
        distanceMillimetre = 93620.1 * pow(value, -0.949);
        //y = 9362,1x-0,949
    }
    if (type == 150)
    {
        //!\todo version 150cm
        //y = 135300x-1,112
        distanceMillimetre = 1353000 * pow(value, -1.112);
    }

    return distanceMillimetre;
}
