/*!
 * \file
 * \brief Implémentation de la classe SpeedTracer.
 */

#include "SpeedTracer.hpp"

test::SpeedTracer::SpeedTracer(pmx::Motor * motor) : motor_(motor), lastTimeUp_(0), nbPulses_(0), lastNbPulses_(0), timer_(PERIOD_TIMER, this)
{
    timer_.start();
    chronoTime_.start();
    utils::LoggerFactory::logger("test::SpeedTracer::csv").info() 
    << ";motor;nbpulses;distance sur la periode(mm);vitesse mesurée (mm/s);code moteur demandée;consigne de vitesse (mm/s);TimeSpan;Time Elapsed;" << utils::end;
    
    for(int i = 0 ; i < 256 ; i++)
    {
        this->numberSpeed_[i] = 0;
        this->averageSpeed_[i] = 0;
    }
}

void test::SpeedTracer::onPulse(bool value, int, int)
{
    if (value)
    {
        nbPulses_++;
    }
}

void test::SpeedTracer::onTimer(int timeSpan)
{
    lastTimeUp_ = lastTimeUp_ + timeSpan;
    ushort motorCode = this->currentMotorCode();
    
    //TODO CC Voir pour passer en ulong et simplifier les calculs en int
    
    //distance parcourue depuis le dernier calcul en mm
    double distance = pmx::SpeedManager::DISTANCE_PER_UP_PULSE * (nbPulses_ - lastNbPulses_);
    
    //vitesse moyenne en mm/s sur la période timeSpan (timeSpan en ms)
    double speed = distance * 1000.0 / timeSpan;
    
    lastNbPulses_ = nbPulses_;
    
    utils::LoggerFactory::logger("test::SpeedTracer::csv").info() << ";"
    << (motor_->location() == pmx::LEFT ? "LEFT" : "RIGHT") << ";"
    << nbPulses_ << ";"
    << distance << ";"
    << speed << ";"
    << motorCode << ";"
    << motor_->orderSpeed() << ";"
    << lastTimeUp_ << ";"
    << chronoTime_.getElapsedTimeInMicroSec() << utils::end;
    
    this->averageSpeed_[motorCode] = (this->averageSpeed_[motorCode] * this->numberSpeed_[motorCode] + speed) / (this->numberSpeed_[motorCode] + 1);
    this->numberSpeed_[motorCode]++;
}

void test::SpeedTracer::computeApproximation(const utils::Logger & logger)
{
    double speed1 = 25;
    double speed2 = 90;
    int motorCode1 = -1;
    int motorCode2 = -1;

    for(int i = 1 ; i < 256 ; i++)
    {
        if (this->averageSpeed_[i-1] <= speed1 && this->averageSpeed_[i] > speed1)
        {
            motorCode1 = i;
        }
        if (this->averageSpeed_[i-1] <= speed2 && this->averageSpeed_[i] > speed2)
        {
            motorCode2 = i;
        }
    }
    
    if (motorCode1 == -1)
    {
        logger.error() << "erreur sur motorCode1" << utils::end;
        return;
    }
    
    if (motorCode2 == -1)
    {
        logger.error() << "erreur sur motorCode2" << utils::end;
        return;
    }
    
    double a = (speed1 - speed2) / (motorCode1 - motorCode2);
    double b = speed2 - a * motorCode2;
    
    logger.info() << " " << (this->motor_->location() == pmx::LEFT ? "LEFT" : "RIGHT") << " a:" << a << " b:" << b << utils::end;
}
