/*!
 * \file
 * \brief Implémentation de la classe RobotMoveByXYTest.
 */

#include <string>
#include <iostream>
#include "RobotMoveByXYTest.hpp"
#include "Robot.hpp"

using namespace std;
using namespace pmx;

void test::RobotMoveByXYTest::run(int argc, char* argv[])
{
    std::cout << "test::RobotMoveByXYTest: Start" << std::endl;

    //nb de coord
    int lot = argc/3;
    int targetX[lot], targetY[lot], back[lot];
    int cap=0;


    if (argc < 5)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] <<"[capActivation:0-1] [[coordX] [coordY] [FORWARD-BACK:0-1] ...] " << std::endl;
    }

    if (argc > 2)
    {
        cap = atoi(argv[2]);
        std::cout << "Cap correction: " << atoi(argv[2]) << std::endl;
    }else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "Cap correction (0-1): " << std::flush;
        std::cin >> cap;
    }
    int nb = 0;
    for(int i=3;i<argc;i=i+3)
    {
        if (argc > i)
        {
            targetX[nb] = atoi(argv[i]);
            std::cout << "coord-x (en mm): " << atoi(argv[i]) << std::endl;
        }else
        {
            //demande de la puissance moteur gauche à appliquer
            std::cout << "coord-x (en mm): " << std::flush;
            std::cin >> targetX[nb];
        }

        if (argc > i+1)
        {
            targetY[nb] = atoi(argv[i+1]);
            std::cout << "coord-y (en mm): " << atoi(argv[i+1]) << std::endl;
        }else
        {
            //demande de la vitesse moteur droit à appliquer
            std::cout << "coord-y (en mm): " << std::flush;
            std::cin >> targetY[nb];
        }

        if (argc > i+2)
        {
            back[nb] = atoi(argv[i+2]);
            std::cout << "go [FORWARD:0 BACK:1]: " << atoi(argv[i+2]) << std::endl;
        }else
        {
            //demande de la vitesse moteur droit à appliquer
            std::cout << "go [FORWARD:0 BACK:1]: " << std::flush;
            std::cin >> back[nb];
        }
        nb++;
    }
    
    pmx::Robot robot;
    robot.base().pidPositionEnabled(false);
    robot.base().vecteurCorrectionEnabled(false);

    logger().debug() << "configure(robot_pmxtest.conf)" << utils::end;
    robot.configure("robot_pmxtest.conf");
   
    
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
        robot.base().movexy_Dpawn(targetX[y], targetY[y], way, NULL, 0, 0);

        logger().info() << "Arrived    x: " << robot.position().x() << " y: " << robot.position().y() << " angle: "<< robot.position().angle()
                << " time(s): " << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
    }
        
    robot.chronometerRobot().stop();
    robot.stop();
    
    logger().info() << "End-Of-PMX" << utils::end;
}
