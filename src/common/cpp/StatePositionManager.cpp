#include <cmath>
#include "LoggerFactory.hpp"
#include "StatePositionManager.hpp"

pmx::StatePositionManager::StatePositionManager() : PositionManager(), haveLeft_(false), haveRight_(false)
{}

void
pmx::StatePositionManager::onLeftPulse(bool value, int, int)
{
    if (value)
    {
        if (haveLeft_)
        {
            turnRight();
        }
        else if (haveRight_)
        {
            goForward();
        }
        else
        {
            haveLeft_ = true;
        }
    }
}

void
pmx::StatePositionManager::onRightPulse(bool value, int, int)
{
    if (value)
    {
        if (haveRight_)
        {
            turnLeft();
        }
        else if (haveLeft_)
        {
            goForward();
        }
        else
        {
            haveRight_ = true;
        }
    }
}

pmx::Position
pmx::StatePositionManager::computeForward(const pmx::Position & position, double distance)
{
    double x = position.x() + distance * cos(position.angle());
    double y = position.y() + distance * sin(position.angle());
    
    return Position(x, y, position.angle());
}

void
pmx::StatePositionManager::log()
{
    static utils::Logger logger = utils::LoggerFactory::logger("pmx::StatePositionManager::csv");
    if (logger.level() >= utils::Level::DEBUG)
    {
        logger.debug() << ";" << position_.x() << ";" << position_.y() << ";" << position_.angle() << utils::end;
    }
}

void
pmx::StatePositionManager::goForward()
{
    position_ = computeForward(position_, DISTANCE_PER_UP_PULSE);
    haveLeft_ = false;
    haveRight_ = false;
    log();
}

void
pmx::StatePositionManager::turnLeft()
{
    position_ = position_.rotate(ANGLE_PER_UP_PULSE / 2.0);
    position_ = computeForward(position_, DISTANCE_PER_UP_PULSE / 2.0);
    position_ = position_.rotate(ANGLE_PER_UP_PULSE / 2.0);
    log();
}

void
pmx::StatePositionManager::turnRight()
{
    position_ = position_.rotate(-1.0 * ANGLE_PER_UP_PULSE / 2.0);
    position_ = computeForward(position_, DISTANCE_PER_UP_PULSE / 2.0);
    position_ = position_.rotate(-1.0 * ANGLE_PER_UP_PULSE / 2.0);
    log();
}
