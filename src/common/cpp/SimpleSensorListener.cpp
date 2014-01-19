#include "SimpleSensorListener.hpp"

pmx::SimpleSensorListener::SimpleSensorListener(pmx::SimpleSensor & contact)
: contact_(contact)
{}

bool pmx::SimpleSensorListener::execute(IRobotIn * robotIn)
{
    this->contact_.state(robotIn->getValue(this->contact_.mu(), this->contact_.pin()));
    
    if(logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "execute() - [pin:" << this->contact_.pin() << " state:" << this->contact_.state() << "]" << utils::end;
    }
    
    //return ! this->stopped_; //renvoi 0 pour supprimer le listener
    return ! this->contact_.stop(); //renvoi 0 pour supprimer le listener
}
