/*!
 * \file
 * \brief Implémentation de la classe RobotMoveByPositionTest.
 */

#include <string>
#include <iostream>
#include "RobotMoveByPositionTest.hpp"
#include "Robot.hpp"
#include "MotorWay.hpp"
#include <math.h>

using namespace std;
using namespace pmx;

void test::RobotMoveByPositionTest::run(int argc, char* argv[])
{
    std::cout << "test::RobotMoveByPositionTest: Start" << std::endl;

    int targetX;
    int mode;

    if(argc > 2 && argc < 4)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] <<" [targetX] [Mode:1=Pid:Vit+Pos 2=Pid:Vit+Vecteur 3=Pid:Vit+Pos+Vecteur]]" << std::endl;
    }

    if(argc < 4)
    {
        std::cout << "target-x: " << std::flush;
        std::cin >> targetX;
        
        std::cout << "Mode [1=Pid:Vit+Pos 2=Pid:Vit+Vecteur 3=Pid:Vit+Pos+Vecteur]: " << std::flush;
        std::cin >> mode;
    }
    else
    {
        targetX = atof(argv[2]);
        mode = atof(argv[3]);
    }
    
    pmx::Robot robot;
    logger().debug() << "configure(robot_pmxtest.conf)" << utils::end;
    robot.configure("robot_pmxtest.conf");

    robot.chronometerRobot().start(); //Chronometre général (match) du robot

    robot.base().pidPositionEnabled(false);
    robot.base().vecteurCorrectionEnabled(false);

    robot.start(); //lancement des threads
    robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID
/*
    //config du pid marche avant
    robot.base().pidSpeedInitialize(pmx::LEFT, 42, 16.5, 0.1);
    robot.base().pidSpeedInitialize(pmx::RIGHT, 34, 13.4, 0.1);
    //Config du pid marche arrière
    robot.base().pidSpeedBackInitialize(pmx::LEFT, 40, 16.5, 0.1);
    robot.base().pidSpeedBackInitialize(pmx::RIGHT, 42, 16, 0.1);
*/

    if(mode == 1)
    {
        robot.base().pidPositionInitialize(pmx::LEFT, 0.12, 0.00001, 0.4);
        robot.base().pidPositionInitialize(pmx::RIGHT, 0.12, 0.00001, 0.4);
        //robot.base().pidPositionInitialize(pmx::LEFT, 0.09, 0.0005, 0.01);
        //robot.base().pidPositionInitialize(pmx::RIGHT, 0.09, 0.0005, 0.01);
        //robot.base().pidPositionInitialize(pmx::LEFT,  0.09, 0.003, 0.01);
        //robot.base().pidPositionInitialize(pmx::RIGHT, 0.09, 0.003, 0.01);
    }else if(mode == 2)
    {
        robot.base().vecteurCorrectionEnabled(true);
    }else if(mode == 3)
    {
        robot.base().vecteurCorrectionEnabled(true);
        robot.base().pidPositionInitialize(pmx::LEFT, 0.12, 0.00001, 0.4);
        robot.base().pidPositionInitialize(pmx::RIGHT, 0.12, 0.00001, 0.4);
    }
    
    robot.base().moveD(targetX / pmx::PositionManager::DISTANCE_PER_UP_PULSE, 0);
    while(robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(10000);
    }
    robot.base().stop();
    logger().info() << "Arrived D: " << targetX / pmx::PositionManager::DISTANCE_PER_UP_PULSE << utils::end;
    logger().info() << "Real    x: " << robot.position().x() << " y: " << robot.position().y()<< utils::end;
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;       


    robot.base().moveD(100 / pmx::PositionManager::DISTANCE_PER_UP_PULSE, 0);
    while(robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(10000);
    }
    robot.base().stop();
    logger().info() << "Arrived D: " << targetX / pmx::PositionManager::DISTANCE_PER_UP_PULSE << utils::end;
    logger().info() << "Real    x: " << robot.position().x() << " y: " << robot.position().y()<< utils::end;
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;

    
    robot.base().turnLeft(M_PI/2);
    while(robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(10000);
    }


    robot.base().moveD(300 / pmx::PositionManager::DISTANCE_PER_UP_PULSE, 0); //en tick
    while(robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(10000);
    }


    robot.base().turnLeft(M_PI/2);
    while(robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(10000);
    }

    
    robot.base().moveD(700 / pmx::PositionManager::DISTANCE_PER_UP_PULSE, 0); //en tick
    while(robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(10000);
    }


    robot.base().turnLeft(M_PI/4);
    while(robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(10000);
    }

    robot.base().moveD(300 / pmx::PositionManager::DISTANCE_PER_UP_PULSE, 0); //en tick
    while(robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(10000);
    }

    robot.base().stop();
    logger().info() << "Arrived D: " << targetX / pmx::PositionManager::DISTANCE_PER_UP_PULSE << utils::end;
    logger().info() << "Real    x: " << robot.position().x() << " y: " << robot.position().y()<< utils::end;
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;

    robot.chronometerRobot().stop();
    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}
