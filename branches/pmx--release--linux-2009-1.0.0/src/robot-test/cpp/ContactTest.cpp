/*!
 * \file
 * \brief Implementation de la classe ContactTest.
 */

#include <iostream>
#include "ContactTest.hpp"
#include "Robot.hpp"
#include "SimpleSensorListener.hpp"

void test::ContactTest::run(int, char *[])
{
    pmx::Robot robot;
    robot.start();
    robot.chronometerRobot().start(); //Chronometre général (match) du robot
    logger().info() << "Start - for 30 seconds" << utils::end;
    
    pmx::SimpleSensorListener* startListener = new pmx::SimpleSensorListener(robot.startContact());
    pmx::SimpleSensorListener* rebootListener = new pmx::SimpleSensorListener(robot.rebootContact());
    robot.addListener(startListener);
    robot.addListener(rebootListener);
    
    bool startContactOldState = true;
    bool rebootContactOldState = true;
    while(robot.chronometerRobot().getElapsedTimeInSec() <= 30)
    {
        //start contact
        if(startContactOldState != startListener->state())
        {
            logger().info() << "startContact: mu:" << startListener->contact().mu()
                    << " pin:" << startListener->contact().pin()
                    << " value:" << startListener->state()
                    << utils::end;
        }
        startContactOldState = startListener->state();
        
        //reboot contact
        if(rebootContactOldState != rebootListener->state())
        {
            logger().info() << "rebootContact: mu:" << rebootListener->contact().mu()
                    << " pin:" << rebootListener->contact().pin()
                    << " value:" << rebootListener->state()
                    << utils::end;
        }
        rebootContactOldState = rebootListener->state();
        
        pthread_yield();
    }
    
    rebootListener->stop();
    startListener->stop();
    pthread_yield();
    
    logger().info() << "Stop" << utils::end;
    robot.stop();
}
