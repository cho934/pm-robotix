#include "StateMoveToDistributor.hpp"
#include "Robot.hpp"

pmx::IAutomateState*
pmx::automate::StateMoveToDistributor::execute(Robot& robot)
{
    this->logger().info() << "start" << utils::end;
    
    
    //application du PID 
    //TODO a corriger car la conf ne marche pas
    robot.base().motorLeft().speedCorrectionEnabled(4, 0.435, 0);
    robot.base().motorRight().speedCorrectionEnabled(5, 0.435, 0);
    pthread_yield();
    
    robot.base().movexy(1500, 0);
    while(robot.base().arrived() == false)
    {
        pthread_yield();
    }
    robot.base().movexy(1500, 500);
    while(robot.base().arrived() == false)
    {
        pthread_yield();
    }
    
    
    logger().info() << "Robot arrived" << utils::end;
    
    return NULL;
}
