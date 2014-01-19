/*!
 * \file
 * \brief Implémentation de la classe RobotMoveByIncrementTest.
 */

#include <string>
#include <iostream>
#include "RobotMoveByIncrementTest.hpp"
#include "Robot.hpp"
#include "SpeedTracer.hpp"

void test::RobotMoveByIncrementTest::run(int, char *[])
{
    logger().info() << "test::RobotMoveByIncrementTest: Start" << utils::end;
    
    pmx::Robot robot;
    robot.start();
    robot.chronometerRobot().start();
    robot.base().motorLeft().speedCorrectionEnabled(false);
    robot.base().motorRight().speedCorrectionEnabled(false);
    
    test::SpeedTracer* leftTracer = new test::SpeedTracer(&robot.base().motorLeft());
    test::SpeedTracer* rightTracer = new test::SpeedTracer(&robot.base().motorRight());
    robot.addListener(leftTracer);
    robot.addListener(rightTracer);
    
    //incrémentation du code moteur
    for(ushort i = 0; i < 255 ; i++)
    {
        robot.base().motorLeft().applyMotorCode(i);
        leftTracer->currentMotorCode(i);
        robot.base().motorRight().applyMotorCode(i);
        rightTracer->currentMotorCode(i);
        
        //Toutes les 600ms
        while(robot.chronometerRobot().getElapsedTimeInMilliSec() < 600)
        {
            usleep(1); //TODO Observed that I am using usleep(1) inside the loop, without putting usleep, the programs is more responsive, but it uses high CPU resources. On the other hand, putting usleep(1) reduces the CPU resources and also decreases responsiveness of the program.
        }
        logger().info() << " Code : " << i << utils::end;
        robot.chronometerRobot().start(); //reinitialisation du compteur de temps
    }
    
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
    
    logger().info() << "test::RobotMoveByIncrementTest: Stop" << utils::end;
    robot.stop();
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
    
    robot.chronometerRobot().stop();
    
    leftTracer->computeApproximation(logger());
    rightTracer->computeApproximation(logger());
}
