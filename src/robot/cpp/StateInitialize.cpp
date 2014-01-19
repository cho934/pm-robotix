#include "StateInitialize.hpp"
#include "StateWaitForReboot.hpp"
#include "StateWaitForStart.hpp"
#include "Robot.hpp"
#include "LedAction.hpp"

pmx::IAutomateState*
pmx::automate::StateInitialize::execute(Robot& robot)
{
    this->logger().info() << "start" << utils::end;
    bool error = false;
    
    pmx::LedAction* action = new pmx::LedAction();
    robot.addAction(action);
    
    utils::Chronometer chrono;
    chrono.start();
    
    while(chrono.getElapsedTimeInSec() < 1.0)
    {
        pthread_yield();
    }
    
    action->stop();
    
    if (error)
    {
        return new pmx::automate::StateWaitForReboot();
    }
    else
    {
        return new pmx::automate::StateWaitForStart();
    }
}
