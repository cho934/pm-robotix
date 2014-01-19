#include "MovementAction.hpp"
#include <cmath>

pmx::MovementAction::MovementAction(pmx::Robot& robot, double x, double y) : robot_(robot), x_(x), y_(y), arrived_(false), vdInitial_(0), b_(0), xIntersect_(0), yIntersect_(0), activ_(false), timer_(PERIOD_TIMER, this)
{
}

bool
pmx::MovementAction::execute(pmx::IRobotOut*)
{
    if(this->activ_ == false)
    {
        logger().debug() << "timer start" << utils::end;
        this->timer_.start();
        this->activ(true);
    }

    return true; //pas false sinon destruction de l'objet
}

void 
pmx::MovementAction::onTimer(int timeSpan)
{
    //TODO autre manière:
    //La manière la plus simple de réaliser ce type d'asservissement et de considérer la somme des moteurs gauche et droit comme un moteur virtuel 
    //traduisant l'avancement du robot (noté delta), 
    //et la différence de ces mêmes moteurs comme un second moteur virtuel traduisant cette fois l'orientation du robot (noté alpha).
    
    //logger().debug() << "execute()" << utils::end;
    const Position & position = this->robot_.base().positionManager().position();
    
    // Calcul du vecteur v reliant le point actuel (position) au point de destination.
    // vx et vy sont les coordonnées de ce vecteur, vd sa longueur.
    double vx = this->x_ - position.x();
    double vy = this->y_ - position.y();
    double vd = std::pow(std::pow(vx, 2) + std::pow(vy, 2), 0.5);
    
    if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "[x():" << position.x() << " y():" << position.y() << "]" << "[vd:" << vd << " vx:" << vx << " vy:" << vy << "]" << timeSpan << utils::end;
    }
    
    if (std::abs(vd) < EPSILON)
    {
        if (logger().isActive(utils::Level::DEBUG))
        {   
            logger().debug("stop");
        }
        this->arrived(true);
        this->timer_.stop(); //arret du timer
        
    }
    
    // Calcul de l'angle de v par rapport à l'origine
    double va = std::acos(vx / vd);
    /* 
    if (vy < 0)
    {
        va = -va; //problème avec cette inversion, mauvais comportement du robot.
    }*/
    
    // Comparaison des angles
    double diffAngles = va - position.angle();
    while (diffAngles < -M_PI)
    {
        diffAngles += 2.0 * M_PI;
    }
    while (diffAngles > M_PI)
    {
        diffAngles -= 2.0 * M_PI;
    }
    
    if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "[diffAngles:" << diffAngles << " va:" << va << " pa:" << position.angle() << "]" << utils::end;
    }
    
    if (std::abs(diffAngles) > M_PI)
    {
        if (logger().isActive(utils::Level::DEBUG))
        {
        logger().debug("turn");
        }
        if(diffAngles > 0)
        {
            this->robot_.base().turnLeft(150);
        }
        else
        {
            this->robot_.base().turnRight(150);
        }
    }
    else
    {
        if (logger().isActive(utils::Level::DEBUG))
        {
            logger().debug("forward");
        }
        
        //1. calcul de la droite descendante à partir du vd initial forme y=gradientAccx+b (a défini)
        if(this->vdInitial_ == 0)
        {
            this->vdInitial(vd);
            this->b(SPEED_MIN - (GRADIENT_ACC * vd));
        
            //2. calcul de l'intersection des 2 droites
            this->xIntersect((this->b_ - SPEED_MIN) / (GRADIENT - GRADIENT_ACC));
            this->yIntersect(GRADIENT * this->xIntersect_ + SPEED_MIN);
        }

        //si avant ou après et pour chaque cas seuillage à Vmax     
        if (logger().isActive(utils::Level::DEBUG))
        {
            logger().debug() << "[vdInitial_:" << this->vdInitial_ << " vd:" << vd << " b:" << this->b_ << " xIntersect:" << this->xIntersect_ << " yIntersect:" << this->yIntersect_ << "]" << utils::end;
        }
        
        double speed = 0;    
        if(this->yIntersect_ > SPEED_MAX)
        {
            //Alors 3 phases de trajectoire en position.
            if (logger().isActive(utils::Level::DEBUG))
            {
                logger().debug() << "[3 phases]" << utils::end;
            }
            if(vd < this->xIntersect_) //phase de décélération
            {             
                speed = GRADIENT * vd + SPEED_MIN;
            }else //phase d'accélération
            {
                speed = GRADIENT_ACC * vd + this->b_;
            }
            //saturation 
            if (speed > SPEED_MAX)
            {
                if (logger().isActive(utils::Level::DEBUG))
                {
                    logger().debug() << "[saturation]" << utils::end;
                }
                speed = SPEED_MAX;
            }
            
        }else
        {
            //alors 2 phases.
            if(vd < this->xIntersect_) //phase de décélération
            {
                if (logger().isActive(utils::Level::DEBUG))
                {
                    logger().debug() << "[2 phases]" << utils::end;
                }
                speed = GRADIENT * vd + SPEED_MIN;
            }else //phase d'accélération
            {
                speed = GRADIENT_ACC * vd + this->b_;
            }
        }
        
        /*
        //calcul de la pente de freinage
        double speed = GRADIENT * vd + SPEED_MIN;

        if (speed > SPEED_MAX)
        {
            speed = SPEED_MAX;
        }
        */
        // TODO par rapport à l'angle
        double ratio = 1.0; 
        //double reducedSpeed = (1 - (std::abs(diffAngles))) * speed;
        double reducedSpeed = speed * ratio;
        if(reducedSpeed < 0)
        {
            reducedSpeed = 0;
        }
        
        if (diffAngles < 0.0)
        {
            //reduction à gauche
            this->robot_.base().defineMotorSpeed(reducedSpeed, speed);
            //
            if (logger().isActive(utils::Level::DEBUG))
            {
                logger().debug() << "[reducedSpeed:" << reducedSpeed << " speed:" << speed << "]" << utils::end;
            }
        }
        else
        {
            //reduction à droite
            this->robot_.base().defineMotorSpeed(speed, reducedSpeed);
            if (logger().isActive(utils::Level::DEBUG))
            {
                logger().debug() << "[ speed:" << speed << " reducedSpeed:" << reducedSpeed << "]" << utils::end;
            }
        }
        
    }

}

