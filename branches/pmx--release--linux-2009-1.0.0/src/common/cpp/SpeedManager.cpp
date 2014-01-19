/*!
 * \file
 * \brief Implementation de la classe SpeedManager.
 */

#include "Macro.hpp"
#include "SpeedManager.hpp"
#include "Robot.hpp"
#include <cmath>

pmx::SpeedManager* pmx::SpeedManager::createInstance(pmx::Motor * motor, const utils::PID & pid)
{
    switch (motor->location())
    {
        case pmx::LEFT:
            return new pmx::SpeedManagerLeft(motor, pid);
            break;
        case pmx::RIGHT:
            return new pmx::SpeedManagerRight(motor, pid);
            break;
        default:
            /// \todo Lever une exception
            break;
    }
    return NULL;
}

pmx::SpeedManager::SpeedManager(pmx::Motor * motor, const utils::PID & pid) : motor_(motor), lastUp_(0), nbPulses_(0), lastNbPulses_(0), timer_(PERIOD_PID, this), pid_(pid)
{
    timer_.start();
    
    //init du fichier log-pid
    if (utils::LoggerFactory::logger("pmx::SpeedManager::log-pid").isActive(utils::Level::DEBUG))
    {
        utils::LoggerFactory::logger("pmx::SpeedManager::log-pid").debug()
        << ";motor;nbpulse;distance totale(mm);distance sur la periode(mm);vitesse moyenne sur la période (mm/s);motorCode converti convertToMotorCode(speed + correction);consigne de vitesse (mm/s);error;correction;speed+correction;" << utils::end;
    }
    if (utils::LoggerFactory::logger("pmx::SpeedManager::log").isActive(utils::Level::DEBUG))
    {
        utils::LoggerFactory::logger("pmx::SpeedManager::log").debug()
        << ";test;test;" << utils::end;
    }
}

void
        pmx::SpeedManager::initialize(const std::string& prefix, utils::Configuration& configuration)
{
    double p = configuration.getDouble(prefix + "-P");
    double i = configuration.getDouble(prefix + "-I");
    double d = configuration.getDouble(prefix + "-D");
    this->initializeSpeedControler(utils::PID(p, i, d));
}

void pmx::SpeedManager::onPulse(bool value, int, int, MotorWay)
{
    /*
     * //Code avec LOG
     * static int nbTestsTotal = 0;
     * nbTestsTotal += nbTests;
     * if (value)
     * {
     * nbPulses_++;
     * if (lastUp_ == 0)
     * {
     * lastUp_ = time;
     * utils::LoggerFactory::logger("pmx::SpeedManager::instant").info() << ";motor;timeOnPulse(us);motorCode;speed(mm/s);nbTests" << utils::end;
     * }
     * else
     * {
     * int timeInMicroSeconds = time - lastUp_;
     * //Definition de la vitesse = distance / temps en secondes
     * double speed = DISTANCE_PER_UP_PULSE * 1000000 / (double) timeInMicroSeconds;
     * lastUp_ = time;
     *
     * utils::LoggerFactory::logger("pmx::SpeedManager::instant").info() << ";" << (motor_->location() == pmx::LEFT ? "LEFT" : "RIGHT") << ";" << time << ";" << motor_->motorCode() << ";" << speed << ";" << nbTestsTotal << utils::end;
     * }
     * nbTestsTotal = 0;
     * }
     */
    //CODE minimum
    if (value)
    {
        nbPulses_++;
    }
}

void pmx::SpeedManager::onTimer(int timeSpan)
{
    //TODO CC Voir pour passer en ulong et simplifier les calculs en int
    
    double angle, vx, vy, vd, va, diffAngles;
    if (this->motor_->robot().base().positionCorrectionEnabled() == true)
    {
        //TODO calcul de la position
        //vx, vy, vd, va
        //calcul des coefficients à partir de la destination
        //todo
        const Position & position = this->motor_->robot().position();
        Base & base = this->motor_->robot().base();
        
        vx = this->motor_->robot().base().x() - position.x();
        vy = this->motor_->robot().base().y() - position.y();
        vd = std::pow(std::pow(vx, 2) + std::pow(vy, 2), 0.5);
        angle = this->motor_->robot().position().angle();
        // Calcul de l'angle de v par rapport à l'origine
        va = std::acos(vx / vd);
        if (vy < 0)
        {
            va = -va; //problème avec cette inversion, mauvais comportement du robot.
        }
        diffAngles = va - position.angle();
        
        //rotation pour se repositionner
        while (diffAngles < -M_PI)
        {
            diffAngles += 2.0 * M_PI;
        }
        while (diffAngles > M_PI)
        {
            diffAngles -= 2.0 * M_PI;
        }
        
        //arret du movexy
        if (std::abs(vd) < base.EPSILON)
        {
            if (utils::LoggerFactory::logger("pmx::SpeedManager::log").isActive(utils::Level::DEBUG))
            {   
                utils::LoggerFactory::logger("pmx::SpeedManager::log").debug("stop");
            }
            base.arrived(true);
            //this->pid_.reset(); // TODO reset du PID
            this->timer_.stop(); //arret du timer

        }

        if (std::abs(diffAngles) > M_PI)
        {
            if (utils::LoggerFactory::logger("pmx::SpeedManager::log").isActive(utils::Level::DEBUG))
            {
                utils::LoggerFactory::logger("pmx::SpeedManager::log").debug() << "[turn]" << utils::end;
            }
            if(diffAngles > 0)
            {
                base.turnLeft(150);
            }
            else
            {
                base.turnRight(150);
            }
        }else
        {
            if (utils::LoggerFactory::logger("pmx::SpeedManager::log").isActive(utils::Level::DEBUG))
            {
                utils::LoggerFactory::logger("pmx::SpeedManager::log").debug() << "[forward]" << utils::end;
            }
            //calcul des phases de trajectoires en position
            if(base.yIntersect() > base.SPEED_MAX)
            {
                //Alors 3 phases de trajectoire en position.
                if (utils::LoggerFactory::logger("pmx::SpeedManager::log").isActive(utils::Level::DEBUG))
                {
                    utils::LoggerFactory::logger("pmx::SpeedManager::log").debug() << "[3 phases]" << utils::end;
                }
                if(vd < base.xIntersect()) //phase de décélération
                {             
                    motor_->orderSpeed(base.GRADIENT * vd + base.SPEED_MIN);
                }else //phase d'accélération
                {
                    motor_->orderSpeed(base.GRADIENT_ACC * vd + base.b());
                }
                //saturation 
                if (motor_->orderSpeed() > base.SPEED_MAX)
                {
                    if (utils::LoggerFactory::logger("pmx::SpeedManager::log").isActive(utils::Level::DEBUG))
                    {
                        utils::LoggerFactory::logger("pmx::SpeedManager::log").debug() << "[saturation]" << utils::end;
                    }
                    motor_->orderSpeed(base.SPEED_MAX);
                }         
            }else
            {
                //alors 2 phases.
                if(vd < base.xIntersect()) //phase de décélération
                {
                    if (utils::LoggerFactory::logger("pmx::SpeedManager::log").isActive(utils::Level::DEBUG))
                    {
                        utils::LoggerFactory::logger("pmx::SpeedManager::log").debug() << "[2 phases]" << utils::end;
                    }
                    motor_->orderSpeed(base.GRADIENT * vd + base.SPEED_MIN);
                }else //phase d'accélération
                {
                    motor_->orderSpeed(base.GRADIENT_ACC * vd + base.b());
                }
            }
        
            /*
            //Formule demi trapeze de trajectoires en position
            //double speed = GRADIENT * vd + SPEED_MIN;
            motor_->orderSpeed(0.4 * vd + 40);

            if (motor_->orderSpeed() > 100)
            {
                motor_->orderSpeed(100);
            }*/
        
        }
        
        if (utils::LoggerFactory::logger("pmx::SpeedManager::log").isActive(utils::Level::DEBUG))
        {    
            utils::LoggerFactory::logger("pmx::SpeedManager::log").debug() << " motor_->orderSpeed(): "  << motor_->orderSpeed()  
            << " vd: "  << vd << " vx: " << vx  << " vy: "  << vy << " va:" << va << " diffAngles:" << diffAngles << utils::end; 
        }
    }
    
    //distance parcourue depuis le dernier calcul en mm
    double distance = DISTANCE_PER_UP_PULSE * (nbPulses_ - lastNbPulses_);
    
    //vitesse moyenne en mm/s sur la période timeSpan (timeSpan en ms)
    double speed = distance * 1000.0 / timeSpan;
    
    //distance linéaire parcourue depuis le début du comptage en mm.
    double distanceTotal = DISTANCE_PER_UP_PULSE * nbPulses_;
    
    lastNbPulses_ = nbPulses_;
    
    //CORRECTION PID
    if (this->motor_->speedCorrectionEnabled())
    {
        int motorCode = 0;
        //si non ordre d'arret 
        if (motor_->orderSpeed() > 0.01)
        {
            //logger().info("pid");
            
            
            //CORRECTION POSITION
            if (this->motor_->robot().base().positionCorrectionEnabled() == true)
            { 
                
                 double temp = motor_->orderSpeed();
                //Correction en position
                if((diffAngles > 0.005 & this->motor_->way() == pmx::FORWARD) | (diffAngles < -0.005 & this->motor_->way() == pmx::BACK)) //variation sur la droite
                {
                    if(this->motor_->location() == pmx::LEFT)
                    {
                        temp = (1-(std::abs(diffAngles) * 2)) * motor_->orderSpeed();
                    }
                    if(this->motor_->location() == pmx::RIGHT)
                    {
                        temp = (1+(std::abs(diffAngles) * 2)) * motor_->orderSpeed();
                    }

                }else
                if((diffAngles < -0.005 & this->motor_->way() == pmx::FORWARD) | (diffAngles > 0.005 & this->motor_->way() == pmx::BACK)) //variation sur la gauche
                {
                    if(this->motor_->location() == pmx::LEFT)
                    {
                        temp = (1+(std::abs(diffAngles) * 2)) * motor_->orderSpeed();
                    }
                    if(this->motor_->location() == pmx::RIGHT)
                    {
                        temp = (1-(std::abs(diffAngles) * 2)) * motor_->orderSpeed();
                    }
                }
                motor_->orderSpeed(temp);
                
                if (utils::LoggerFactory::logger("pmx::SpeedManager::log").isActive(utils::Level::DEBUG))
                {    
                    utils::LoggerFactory::logger("pmx::SpeedManager::log").debug() << " location: "  << this->motor_->location() 
                    << " orderSpeedAndWay: "  << temp  << utils::end; 
                }
            }
            
            //Régulation de la vitesse (via le PID)
            double error = motor_->orderSpeed() - speed;
            double correction = this->pid_.ComputePID(error);
            double speedCorrection = speed + correction;
            
            //conversion
            motorCode = motor_->convertToMotorCode(speedCorrection);
            //log du pid
            if(logger().isActive(utils::Level::DEBUG))
            {
                if(utils::LoggerFactory::logger("pmx::SpeedManager::log-pid").isActive(utils::Level::DEBUG))
                {
                    //utils::LoggerFactory::logger("pmx::SpeedManager::log-pid").debug() << "
                    //;motor;nbpulse;distance totale(mm);distance sur la periode(mm);motorCode;vitesse moy(mm/s);error;correction;speed+correction;" << utils::end;
                    utils::LoggerFactory::logger("pmx::SpeedManager::log-pid").debug() << ";"
                    << (motor_->location() == pmx::LEFT ? "LEFT" : "RIGHT") << ";"
                    << nbPulses_ << ";"
                    << distanceTotal << ";"
                    << distance << ";"
                    << speed << ";"
                    << motorCode << ";"
                    << motor_->orderSpeed() << ";"
                    << error << ";"
                    << correction << ";"
                    << speed + correction << ";"
                    << utils::end;
                }
            }
        }
        
        motor_->applyMotorCode(motorCode);
    }
}
