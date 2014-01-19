#include "SimpleSensorListener.hpp"

pmx::SimpleSensorListener::SimpleSensorListener(pmx::SimpleSensor & contact)
: contact_(contact), state_(false), stopped_(false)
{}

bool pmx::SimpleSensorListener::execute(IRobotIn * robotIn)
{
    this->state_ = robotIn->getValue(this->contact_.mu(), this->contact_.pin());
    
    if(logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "execute() - [pin:" << this->contact_.pin() << " state:" << this->state_ << "]" << utils::end;
    }
    
    return ! this->stopped_;
}
