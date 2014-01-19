/*!
 * \file
 * \brief Implémentation de la classe RobotMoveByPositionTest.
 */

#include <string>
#include <iostream>
#include "RobotMoveByPositionTest.hpp"
#include "Robot.hpp"
#include "MotorWay.hpp"

using namespace std;
using namespace pmx;

void test::RobotMoveByPositionTest::run(int, char **)
{
    logger().info() << "Start" << utils::end; 
    
    pmx::Robot robot;
    
    //TODO pb avec le PID avec le fichier de conf !!!!!
    //robot.configure("robot.conf");
    robot.start(); //lancement des threads

    robot.chronometerRobot().start(); //Chronometre général (match) du robot
    
    //robot.base().motorLeft().speedCorrectionEnabled(1, 0, 0);
    robot.base().motorLeft().speedCorrectionEnabled(4, 0.435, 0);

    //robot.base().motorRight().speedCorrectionEnabled(1, 0, 0);
    robot.base().motorRight().speedCorrectionEnabled(5, 0.435, 0);
    pthread_yield();
    
    //robot.base().arrived(false);
    robot.base().movexy(-1000,0);
    while(robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        pthread_yield();
    }
    logger().info() << "Arrived 1000 0" << utils::end;
    /*
    robot.base().arrived(false);
    robot.base().movexy(1000,0);
    while(robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        pthread_yield();
    }

    logger().info() << "Arrived 1000 0" << utils::end;
    robot.base().stop();
    pthread_yield();
    */
    
    logger().info() << "Stop" << utils::end;
    robot.base().stop();
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
      
    robot.chronometerRobot().stop();
    robot.stop();
}
