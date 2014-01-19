#include "StateWaitForReboot.hpp"
#include "StateInitialize.hpp"
#include "SimpleSensorListener.hpp"
#include "Robot.hpp"

pmx::IAutomateState*
pmx::automate::StateWaitForReboot::execute(Robot& robot)
{
    this->logger().info() << "start" << utils::end;
    pmx::SimpleSensorListener* listener = new pmx::SimpleSensorListener(robot.rebootContact());
    robot.addListener(listener);
    
    while(!listener->state())
    {
        pthread_yield();
    }
    
    while(listener->state())
    {
        pthread_yield();
    }
    
    listener->stop();
    
    return new pmx::automate::StateInitialize();
}
