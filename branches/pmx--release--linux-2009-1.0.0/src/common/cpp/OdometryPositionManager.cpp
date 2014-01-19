#include <cmath>
#include "OdometryPositionManager.hpp"
#include "LoggerFactory.hpp"
#include <iostream>

pmx::OdometryPositionManager::OdometryPositionManager() : PositionManager(), countLeft_(0), countRight_(0)
{
    if (csv().level() >= utils::Level::DEBUG)
    {
        csv().debug() << ";alpha;delta;x;y;angle" << utils::end;
    }
}

void
pmx::OdometryPositionManager::onLeftPulse(bool value, int, int, MotorWay way)
{
    if (value)
    {
        if (way == pmx::FORWARD)
        {
            this->countLeft_++;
        }
        else if(way == pmx::BACK)
        {
            this->countLeft_--;
        }
        this->count_++;
        this->compute();
    }
}

void
pmx::OdometryPositionManager::onRightPulse(bool value, int, int, MotorWay way)
{
    if (value)
    {
        if (way == pmx::FORWARD)
        {
            this->countRight_++;
        }
        else if(way == pmx::BACK)
        {
            this->countRight_--;
        }
        this->count_++;
        this->compute();
    }
}

void
pmx::OdometryPositionManager::compute()
{
    //prise en compte d'une petite distance en avant ou en arrière
    if (this->count_ >= 6)
    {
        // variation de l'angle ; ATTENTION ici par de division par 2 ! (à expliquer)
        double dAlpha = (this->countRight_ - this->countLeft_);
        
        // variation de l'avancement
        double dDelta = (this->countRight_ + this->countLeft_) / 2;
        
        this->count_ = 0;
        this->countLeft_ = 0;
        this->countRight_ = 0;
        
        // conversion en radian
        double angle = this->position().angle() + dAlpha * this->ANGLE_PER_UP_PULSE;
        
        // calcul des décalages selon X et Y
        double dX = cos(angle) * dDelta;
        double dY = sin(angle) * dDelta;
        
        // conversion de la position en millimètre
        double x = this->position().x() + dX * this->DISTANCE_PER_UP_PULSE;
        double y = this->position().y() + dY * this->DISTANCE_PER_UP_PULSE;
        
        this->position_ = pmx::Position(x, y, angle);
        
        if (csv().isActive(utils::Level::DEBUG))
        {
            csv().debug()
                    << ";" << dAlpha
                    << ";" << dDelta
                    << ";" << position_.x()
                    << ";" << position_.y()
                    << ";" << position_.angle()
                    << utils::end;
        }
        if (svg().isActive(utils::Level::DEBUG))
        {
            //inversion du y pour affichage dans le bon sens dans le SVG
            svg().debug()
                    << "<circle cx=\""
                    << position_.x()
                    << "\" cy=\""
                    << -position_.y()
                    << "\" r=\"1\" fill=\"blue\" />"
                    << utils::end;
        }
    }
}
