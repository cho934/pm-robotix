/*!
 * \file
 * \brief Implémentation de la classe SensorManager.
 */

#include <iostream>
#include "SensorManager.hpp"
#include "RobotInOutFactory.hpp"
#include "MotorWay.hpp"

pmx::SensorManager::SensorManager(): stop_(false), leftPulseState_(false), rightPulseState_(false), chronometer_()
{}

void
pmx::SensorManager::fireLeftPulse(bool value, int time, int nbTests, MotorWay way)
{
    if(logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "fireLeftPulse() [value:" << value << "] [time:" << time << "]" << utils::end;
    }
    utils::PointerList <IMotorListener*>::iterator i = this->motorListeners_.begin();
    while (i != motorListeners_.end())
    {
        IMotorListener* listener = *i;
        listener->onLeftPulse(value, time, nbTests, way);
        i++;
    }
}

void
pmx::SensorManager::fireRightPulse(bool value, int time, int nbTests, MotorWay way)
{
    if(logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "fireRightPulse() [value:" << value << "] [time:" << time << "]" << utils::end;
    }
    utils::PointerList <IMotorListener*>::iterator i = this->motorListeners_.begin();
    while (i != motorListeners_.end())
    {
        IMotorListener* listener = *i;
        listener->onRightPulse(value, time, nbTests, way);
        i++;
    }
}

void
pmx::SensorManager::execute()
{
    logger().info() << "Execute : SensorManager is started with "
            << this->motorListeners_.size() << " + "
            << this->sensorListeners_.size() << " listener(s)"
            << utils::end;
    pmx::IRobotIn * robotIn = pmx::RobotInOutFactory::instance()->robotIn();
    
    //Démarrage du chronometer permettant le relevé des impulsions.
    chronometer_.start();
    
    MotorWay leftWay, rightWay;
    int nbTestLeft = 0;
    int nbTestRight = 0;
    while (!stop_)
    {
        //Traitement des impulsions
        bool leftPulse = robotIn->getImpLeft();
        bool rightPulse = robotIn->getImpRight();
        
        bool bLeftWay = robotIn->getImpLeftWay();
        if(bLeftWay)
        {
            leftWay = pmx::FORWARD;
        }
        else
        {
            leftWay = pmx::BACK;
        }
        bool bRightWay = robotIn->getImpRightWay();
        if(bRightWay)
        {
            rightWay = pmx::FORWARD;
        }
        else
        {
            rightWay = pmx::BACK;
        }
        
        nbTestLeft++;
        nbTestRight++;
        
        if (leftPulse != leftPulseState_)
        {
            if (logger().isActive(utils::Level::DEBUG))
            {
                utils::LoggerFactory::logger("pmx::SensorManager::left").debug() << nbTestLeft << utils::end;
            }
            fireLeftPulse(leftPulse, chronometer_.getElapsedTimeInMicroSec(), nbTestLeft, leftWay);
            leftPulseState_ = leftPulse;
            nbTestLeft = 0;
        }
        
        if (rightPulse != rightPulseState_)
        {
            if (logger().isActive(utils::Level::DEBUG))
            {
                utils::LoggerFactory::logger("pmx::SensorManager::right").debug() << nbTestRight << utils::end;
            }
            fireRightPulse(rightPulse, chronometer_.getElapsedTimeInMicroSec(), nbTestRight, rightWay);
            rightPulseState_ = rightPulse;
            nbTestRight = 0;
        }
        
        // Traitement des autres capteurs
        if (sensorListeners_.size() > 0)
        {
            utils::PointerList <ISensorListener *>::iterator i = sensorListeners_.begin();
            while (i != sensorListeners_.end())
            {
                ISensorListener * listener = *i;
                bool persist = listener->execute(robotIn);
                
                if (!persist)
                {
                    utils::PointerList <ISensorListener *>::iterator old = i;
                    i++;
                    
                    delete listener;
                    sensorListeners_.erase(old);
                }
                else
                {
                    i++;
                }
                this->yield();
            }
        }
        
        this->yield();
    }
    
    if (sensorListeners_.size() > 0)
    {
        if (logger().isActive(utils::Level::DEBUG))
        {
            logger().debug() << "Number of end ISensorListener : " << sensorListeners_.size() << utils::end;
        }
        utils::PointerList <ISensorListener *>::iterator i = sensorListeners_.begin();
        while (i != sensorListeners_.end())
        {
            ISensorListener * listener = *i;
            listener->execute(robotIn);
            
            utils::PointerList <ISensorListener *>::iterator old = i;
            i++;
            
            delete listener;
            this->sensorListeners_.erase(old);
        }
    }
    
    //! \todo Libérer la mémoire lorsque le thread est arrété.
    
    logger().info("SensorManager is stopped");
}
