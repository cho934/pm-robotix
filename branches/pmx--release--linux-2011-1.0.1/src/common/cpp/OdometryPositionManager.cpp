#include <cmath>
#include "OdometryPositionManager.hpp"
#include "LoggerFactory.hpp"
#include "SvgWriter.hpp"
#include <iostream>
#include <cmath>

pmx::OdometryPositionManager::OdometryPositionManager() : PositionManager(), countLeft_(0), countRight_(0)
{
    if (csv().level() >= utils::Level::DEBUG)
    {
        csv().debug() << ";alpha;delta;x;y;xTick;yTick;angle" << utils::end;
    }
}

void
pmx::OdometryPositionManager::onLeftPulse(int value, utils::Chronometer, MotorWay)
{
    this->countLeft_ += value;
    this->count_ += std::abs(value);
    this->compute();
}

void
pmx::OdometryPositionManager::onRightPulse(int value, utils::Chronometer, MotorWay)
{
    this->countRight_ += value;
    this->count_ += std::abs(value);
    this->compute();
}

void
pmx::OdometryPositionManager::compute()
{
    //prise en compte d'une petite distance en avant ou en arrière
    if (this->count_ >= 4)
    {
        // variation de l'angle ; ATTENTION ici pas de division par 2 ! (à expliquer)
        double dAlpha = (this->countRight_ - this->countLeft_);

        // variation de l'avancement
        double dDelta = (this->countRight_ + this->countLeft_) / 2;

        this->count_ = 0;
        this->countLeft_ = 0;
        this->countRight_ = 0;

        // conversion en radian
        double angle = this->position().angle() + (dAlpha * this->ANGLE_PER_UP_PULSE );

        // calcul des décalages selon X et Y
        double dX = cos(angle) * dDelta;
        double dY = sin(angle) * dDelta;

        // conversion de la position en millimètre
        double x = this->position().x() + dX * this->DISTANCE_PER_UP_PULSE;
        double y = this->position().y() + dY * this->DISTANCE_PER_UP_PULSE;

        this->position_ = pmx::Position(x, y, angle);

        utils::SvgWriter::writePosition(position_.x(), position_.y());
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
    }
}
