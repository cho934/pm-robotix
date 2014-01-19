/*!
 * \file
 * \brief Implémentation de la classe SpeedTracerFusion.
 */

#include "SpeedTracerFusion.hpp"
#include <iostream>

test::SpeedTracerFusion::SpeedTracerFusion(pmx::Base * base) : base_(base), lastTimeUp_(0), nbPulsesLeft_(0), nbPulsesRight_(0), lastNbPulsesLeft_(0), lastNbPulsesRight_(0), timerStf_(PERIOD_TIMER, this)
{
    
    utils::LoggerFactory::logger("test::SpeedTracerFusion::csv").info()
    << ";motor;nbpulses;distance sur la periode(mm);vitesse mesurée (mm/s);code moteur appliqué;TimeSpan;Time Elapsed;" << utils::end;

    //initialisation des valeurs pour le computeApproximation
    for(int i = 0 ; i < 1024 ; i++)
    {
        this->numberSpeedLeft_[i] = 0;
        this->averageSpeedLeft_[i] = 0;
        this->numberSpeedRight_[i] = 0;
        this->averageSpeedRight_[i] = 0;
    }

    logger().info() << "timer start" << utils::end;
    std::cout << "Thread::start: SpeedTracerFusion timer_"  << std::endl;
    chronoTime_.start();//Lancement du chrono de log
    timerStf_.start(); //Lancement du onTimer
}

void test::SpeedTracerFusion::onTimer(utils::Chronometer chrono)
{
    logger().debug() << "onTimer" << utils::end;
    int timeElapsed = chronoTime_.getElapsedTimeInMicroSec();
    long timeSpan = chrono.getElapsedTimeInMicroSec();

    logger().debug() << "MOTOR LEFT" << utils::end;    
    long nbPulsesLeft = nbPulsesLeft_;
    ushort motorCodeLeft = this->currentMotorCodeLeft();
    //distance parcourue depuis le dernier calcul en mm
    double distanceLeft = pmx::PositionManager::DISTANCE_PER_UP_PULSE * (nbPulsesLeft - lastNbPulsesLeft_);
    lastNbPulsesLeft_ = nbPulsesLeft;
    //vitesse moyenne en mm/s sur la période timeSpan (timeSpan en ms)
    double speedLeft = distanceLeft * 1000000.0 / timeSpan;

    if (utils::LoggerFactory::logger("test::SpeedTracerFusion::csv").isActive(utils::Level::INFO))
    {
        utils::LoggerFactory::logger("test::SpeedTracerFusion::csv").info() << ";"
        << "LEFT" << ";"
        << nbPulsesLeft << ";"
        << distanceLeft << ";"
        << speedLeft << ";"
        << motorCodeLeft << ";"
        << lastTimeUp_ << ";"
        << timeElapsed << utils::end;
    }
    //remplissage du tableau  de moyenne pour la fonction computeApproximation : objectif reduire les données à un seul motorCode different.
    this->averageSpeedLeft_[motorCodeLeft] = (this->averageSpeedLeft_[motorCodeLeft] * this->numberSpeedLeft_[motorCodeLeft] + speedLeft) / (this->numberSpeedLeft_[motorCodeLeft] + 1);
    this->numberSpeedLeft_[motorCodeLeft]++;

    logger().debug() << "MOTOR RIGHT" << utils::end;
    long nbPulsesRight = nbPulsesRight_;
    ushort motorCodeRight = this->currentMotorCodeRight();
    //distance parcourue depuis le dernier calcul en mm
    double distanceRight = pmx::PositionManager::DISTANCE_PER_UP_PULSE * (nbPulsesRight - lastNbPulsesRight_);
    lastNbPulsesRight_ = nbPulsesRight;
    //vitesse moyenne en mm/s sur la période timeSpan (timeSpan en ms)
    double speedRight = distanceRight * 1000000.0 / timeSpan;
    if (utils::LoggerFactory::logger("test::SpeedTracerFusion::csv").isActive(utils::Level::INFO))
    {
        utils::LoggerFactory::logger("test::SpeedTracerFusion::csv").info() << ";"
        << "RIGHT" << ";"
        << nbPulsesRight << ";"
        << distanceRight << ";"
        << speedRight << ";"
        << motorCodeRight << ";"
        << lastTimeUp_ << ";"
        << timeElapsed << utils::end;
    }
    //remplissage du tableau  de moyenne pour la fonction computeApproximation : objectif reduire les données à un seul motorCode different.
    this->averageSpeedRight_[motorCodeRight] = (this->averageSpeedRight_[motorCodeRight] * this->numberSpeedRight_[motorCodeRight] + speedRight) / (this->numberSpeedRight_[motorCodeRight] + 1);
    this->numberSpeedRight_[motorCodeRight]++;

    lastTimeUp_ += timeSpan;
}

/*!
 * \brief Détermine les coeficients a et b de la correspondance vitesse/motorcode y=ax+b de chaque moteur.
 * \deprecated ne sert plus.
 */
void test::SpeedTracerFusion::computeApproximation(const utils::Logger & logger)
{
    double speed1 = 10; //en tick
    double speed2 = 45; //en tick
    int motorCode1Left = -1;
    int motorCode2Left = -1;
    int motorCode1Right = -1;
    int motorCode2Right = -1;

    for(int i = 1 ; i < 1024 ; i++)
    {        
        if (this->averageSpeedLeft_[i-1] <= speed1 && this->averageSpeedLeft_[i] > speed1)
        {
            motorCode1Left = i;
        }
        if (this->averageSpeedLeft_[i-1] <= speed2 && this->averageSpeedLeft_[i] > speed2)
        {
            motorCode2Left = i;
        }

        if (this->averageSpeedRight_[i-1] <= speed1 && this->averageSpeedRight_[i] > speed1)
        {
            motorCode1Right = i;
        }
        if (this->averageSpeedRight_[i-1] <= speed2 && this->averageSpeedRight_[i] > speed2)
        {
            motorCode2Right = i;
        }
    }
    
    if (motorCode1Left == -1)
    {
        logger.error() << "MotorLEFT : erreur sur motorCode1" << utils::end;
        return;
    }
    
    if (motorCode2Left == -1)
    {
        logger.error() << "MotorLEFT : erreur sur motorCode2" << utils::end;
        return;
    }
    
    double aL = (speed1 - speed2) / (motorCode1Left - motorCode2Left);
    double bL = speed2 - aL * motorCode2Left;

    if (motorCode1Right == -1)
    {
        logger.error() << "MotorRIGHT : erreur sur motorCode1" << utils::end;
        return;
    }

    if (motorCode2Right == -1)
    {
        logger.error() << "MotorRIGHT : erreur sur motorCode2" << utils::end;
        return;
    }
    double aR = (speed1 - speed2) / (motorCode1Right - motorCode2Right);
    double bR = speed2 - aR * motorCode2Right;
       
    logger.info() << "LEFT : " << " a:" << aL << " b:" << bL << utils::end;
    logger.info() << "RIGHT: " << " a:" << aR << " b:" << bR << utils::end;
}
