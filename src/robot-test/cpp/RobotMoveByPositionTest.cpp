/*!
 * \file
 * \brief Implémentation de la classe RobotMoveByPositionTest.
 */

#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "RobotMoveByPositionTest.hpp"
#include "Robot.hpp"
#include "MotorWay.hpp"
#include "Md25.hpp"

using namespace std;
using namespace pmx;

void test::RobotMoveByPositionTest::run(int argc, char* argv[])
{
    std::cout << "test::RobotMoveByPositionTest: Start" << std::endl;

    int targetX, ecartY;
    int mode;

    if (argc < 5)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] << " [targetX(mm)] [ecartY(mm)] [Mode:1=Pid:Vit+Pos 2=Pid:Pos 3=Pid:Vit+Pos+Vec 4=Ramp 5=Ramp+Vec 6=Pos+Vec]" << std::endl;
    }

    if (argc > 2)
    {
        targetX = atof(argv[2]);
        std::cout << "targetX: " << atoi(argv[2]) << std::endl;
    }else
    {
        std::cout << "target-x (mm): " << std::flush;
        std::cin >> targetX;
    }

    if (argc > 3)
    {
        ecartY = atof(argv[3]);
        std::cout << "ecartY : " << atoi(argv[3]) << std::endl;
    }else
    {
        std::cout << "ecartY (mm): " << std::flush;
        std::cin >> ecartY;
    }

    if (argc > 4)
    {
        mode = atof(argv[4]);
        std::cout << "mode  : " << atoi(argv[4]) << std::endl;
    }else
    {
        std::cout << "Mode [1=Pid:Vit+Pos 2=Pid:Pos 3=Pid:Vit+Pos+Vec 4=Ramp 5=Ramp+Vec 6=Pos+Vec] " << std::flush;
        std::cin >> mode;
    }

    pmx::Robot robot;
    //robot.configure("robot_pmxtest.conf");

    robot.chronometerRobot().start(); //Chronometre général (match) du robot

    robot.base().pidSpeedEnabled(false);
    robot.base().pidPositionEnabled(false);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().rampPositionEnabled(false);

    utils::Md25::instance().setAccelerationRate(10);
    
    robot.start(); //lancement des threads  
    robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID

    if (mode == 1)
    {
        //todo ajouter pid vitesse
        robot.base().pidPositionInitialize(pmx::MLEFT, 0.14, 0.00005, 0);
        robot.base().pidPositionInitialize(pmx::MRIGHT, 0.14, 0.00005, 0);
        //robot.base().pidPositionInitialize(pmx::MLEFT, 0.12, 0.00001, 0.4);
        //robot.base().pidPositionInitialize(pmx::MRIGHT, 0.12, 0.00001, 0.4);
        //robot.base().pidPositionInitialize(pmx::LEFT, 0.09, 0.0005, 0.01);
        //robot.base().pidPositionInitialize(pmx::RIGHT, 0.09, 0.0005, 0.01);
        //robot.base().pidPositionInitialize(pmx::LEFT,  0.09, 0.003, 0.01);
        //robot.base().pidPositionInitialize(pmx::RIGHT, 0.09, 0.003, 0.01);
    }else if (mode == 2)
    {
        robot.base().pidPositionInitialize(pmx::MLEFT, 0.14, 0.00005, 0);
        robot.base().pidPositionInitialize(pmx::MRIGHT, 0.14, 0.00005, 0);
        robot.base().vecteurCorrectionEnabled(false);
    }else if (mode == 3)
    {
        //todo ajouter pid vitesse
        robot.base().vecteurCorrectionEnabled(true);
        //robot.base().pidPositionInitialize(pmx::MLEFT, 0.12, 0.00001, 0.4);
        //robot.base().pidPositionInitialize(pmx::MRIGHT, 0.12, 0.00001, 0.4);
        robot.base().pidPositionInitialize(pmx::MLEFT, 0.14, 0.00005, 0);
        robot.base().pidPositionInitialize(pmx::MRIGHT, 0.14, 0.00005, 0);
    }else if (mode == 4)
    {
        robot.base().rampPositionEnabled(true);
    }else if (mode == 5)
    {
        robot.base().rampPositionEnabled(true);
        robot.base().vecteurCorrectionEnabled(true);
    }else if (mode == 6)
    {
        robot.base().pidPositionInitialize(pmx::MLEFT, 0.14, 0.00005, 0);
        robot.base().pidPositionInitialize(pmx::MRIGHT, 0.14, 0.00005, 0);
        robot.base().vecteurCorrectionEnabled(true);
    }

    //xDestination mis a jour pour que le vecteur approche fonctionne.
    robot.base().xDestination(targetX);
    robot.base().yDestination(ecartY);

    robot.base().moveD(targetX / pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE, ecartY); //en tick

    while (robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(1000);

    }

    robot.base().stop();

    logger().info() << "Arrived moveD: " << targetX / pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE << " ticks" << utils::end;
    logger().info() << "Real        x: " << robot.position().x() << " mm, y: " << robot.position().y() << " mm" << utils::end;
    logger().info() << "Time elapsed : " << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;

    /*
        robot.base().moveD(100 / pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE, 0);
        while(robot.base().arrived() == false) //boucle d'attente d'arrivée
        {
            usleep(10000);
        }
        robot.base().stop();
        logger().info() << "Arrived D: " << targetX / pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE << utils::end;
        logger().info() << "Real    x: " << robot.position().x() << " y: " << robot.position().y()<< utils::end;
        logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;

    
        robot.base().turnLeft(M_PI/2);
        while(robot.base().arrived() == false) //boucle d'attente d'arrivée
        {
            usleep(10000);
        }


        robot.base().moveD(300 / pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE, 0); //en tick
        while(robot.base().arrived() == false) //boucle d'attente d'arrivée
        {
            usleep(10000);
        }


        robot.base().turnLeft(M_PI/2);
        while(robot.base().arrived() == false) //boucle d'attente d'arrivée
        {
            usleep(10000);
        }

    
        robot.base().moveD(700 / pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE, 0); //en tick
        while(robot.base().arrived() == false) //boucle d'attente d'arrivée
        {
            usleep(10000);
        }


        robot.base().turnLeft(M_PI/4);
        while(robot.base().arrived() == false) //boucle d'attente d'arrivée
        {
            usleep(10000);
        }

        robot.base().moveD(300 / pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE, 0); //en tick
        while(robot.base().arrived() == false) //boucle d'attente d'arrivée
        {
            usleep(10000);
        }

        robot.base().stop();
        logger().info() << "Arrived D: " << targetX / pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE << utils::end;
        logger().info() << "Real    x: " << robot.position().x() << " y: " << robot.position().y()<< utils::end;
        logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
     */
    robot.chronometerRobot().stop();
    robot.stop();
    logger().info() << "End-Of-PMX : "
            << robot.chronometerRobot().getElapsedTimeInMicroSec() << " us "
            << utils::end;
}
