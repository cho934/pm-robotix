/*!
 * \file
 * \brief Implémentation de la classe RobotMoveByXYTest.
 */

#include <string>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "RobotMoveByXYTest.hpp"
#include "Robot.hpp"

using namespace std;
using namespace pmx;

void test::RobotMoveByXYTest::run(int argc, char* argv[])
{
    std::cout << "test::RobotMoveByXYTest: Start" << std::endl;

    //nb de coord
    int lot = argc/4;
    int targetX[lot], targetY[lot], back[lot];
    double angle[lot];
    int cap=0, detect=0;


    if (argc < 8)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] <<" [capActivation:0-1] [OpponentDetect:0-1]  [[coordX(mm)] [coordY(mm)] [angle(deg -179...+180)] [FORWARD-BACK:0-1] ...] " << std::endl;
    }

    if (argc > 2)
    {
        cap = atoi(argv[2]);
        std::cout << "Cap correction: " << atoi(argv[2]) << std::endl;
    }else
    {
        std::cout << "Cap correction (0-1): " << std::flush;
        std::cin >> cap;
    }

    if (argc > 3)
    {
        detect = atoi(argv[3]);
        std::cout << "OpponentDetect: " << atoi(argv[3]) << std::endl;
    }else
    {
        std::cout << "OpponentDetect (0-1): " << std::flush;
        std::cin >> detect;
    }

    int nb = 0;
    for(int i=4;i<argc;i=i+4)
    {
        if (argc > i)
        {
            targetX[nb] = atoi(argv[i]);
            std::cout << "coord-x (en mm): " << atoi(argv[i]) << std::endl;
        }else
        {
            std::cout << "coord-x (en mm): " << std::flush;
            std::cin >> targetX[nb];
        }

        if (argc > i+1)
        {
            targetY[nb] = atoi(argv[i+1]);
            std::cout << "coord-y (en mm): " << atoi(argv[i+1]) << std::endl;
        }else
        {
            std::cout << "coord-y (en mm): " << std::flush;
            std::cin >> targetY[nb];
        }

        if (argc > i+2)
        {
            angle[nb] = atoi(argv[i+2]);
            std::cout << "angle (en degré): " << atoi(argv[i+2]) << std::endl;
        }else
        {
            std::cout << "angle (en degré): " << std::flush;
            std::cin >> angle[nb];
        }

        if (argc > i+3)
        {
            back[nb] = atoi(argv[i+3]);
            std::cout << "go [FORWARD:0 BACK:1]: " << atoi(argv[i+3]) << std::endl;
        }else
        {
            std::cout << "go [FORWARD:0 BACK:1]: " << std::flush;
            std::cin >> back[nb];
        }
        nb++;
    }
    
    pmx::Robot robot;

    logger().debug() << "configure(robot_pmxtest.conf)" << utils::end;
    robot.configure("robot_pmxtest.conf");

    robot.base().pidSpeedEnabled(false);
    robot.base().pidPositionEnabled(true);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.myColorIs(pmx::PMXRED);
    robot.position().y(250.0,pmx::PMXRED);
    robot.position().angle(0.0,pmx::PMXRED);

    robot.start(); //lancement des threads
    robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID
    robot.chronometerRobot().start(); //Chronometre général (match) du robot
    
    if(cap)
    {
        robot.base().vecteurCorrectionEnabled(true);
    }
    BaseWay way;
    for(int y=0;y<nb;y++)
    {
        if(back[y] == 0)
        {
            way = pmx::BFORWARD;
        }else if(back[y] == 1)
        {
            way = pmx::BBACK;
        }else
        {
            logger().info() << "DATA PROBLEM !!" << utils::end;
        }
        logger().info() << "Go    x: " << targetX[y] << " y: " << targetY[y] << " way: "<< way
                << " time(s): " << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;

        bool opponentDetected = false;
        if(angle[y] > 180.0)
        {
            opponentDetected = robot.base().movexy(targetX[y], targetY[y], way, detect);
        }else
        {
            opponentDetected = robot.base().movexyTeta(targetX[y], targetY[y], way, angle[y] * M_PI / 180.0, detect);
        }

        if(opponentDetected == true)
        {
            logger().info() << " !! opponentDetected time=" << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
        }

        //sleep(3);
        logger().info() << "Arrived    x: " << robot.position().x() << " mm y: " << robot.position().y()
                << " mm angle: "<< robot.position().angle() * 180.0 / M_PI
                << " degré time(s): " << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
    }
        
    robot.chronometerRobot().stop();
    robot.stop();
    
    logger().info() << "End-Of-PMX : "
            << robot.chronometerRobot().getElapsedTimeInMicroSec() << " us "
            << utils::end;
}
