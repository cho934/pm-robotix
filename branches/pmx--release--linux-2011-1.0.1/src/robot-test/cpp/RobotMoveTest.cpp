/*!
 * \file
 * \brief Implémentation de la classe RobotMoveTest.
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include "RobotMoveTest.hpp"
#include "Robot.hpp"
#include "MotorWay.hpp"

using namespace std;
using namespace pmx;

void test::RobotMoveTest::run(int argc, char *argv[])
{
    //logger().info() << "test::RobotMoveTest: Start" << utils::end;
    std::cout << "test::RobotMoveTest: Start" << std::endl;
    int targetX, targetY, cap;

    if (argc < 5)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] <<" [targetX(tick)] [targetY(tick)] [capActivation:0-1]" << std::endl;
    }

    if (argc > 2)
    {
        targetX = atoi(argv[2]);
        std::cout << "target-x: " << atoi(argv[2]) << std::endl;
    }else
    {
        //demande de la distance x
        std::cout << "target-x: " << std::flush;
        std::cin >> targetX;
    }

    if (argc > 3)
    {
        targetY = atoi(argv[3]);
        std::cout << "target-y: " << atoi(argv[3]) << std::endl;
    }else
    {
        //demande de la distance y
        std::cout << "target-y: " << std::flush;
        std::cin >> targetY;
    }

    if (argc > 4)
    {
        cap = atoi(argv[4]);
        std::cout << "Cap correction: " << atoi(argv[4]) << std::endl;
    }else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "Cap correction: " << std::flush;
        std::cin >> cap;
    }

    pmx::Robot robot;

    logger().debug() << "configure(robot_pmxtest.conf)" << utils::end;
    robot.configure("robot_pmxtest.conf");

    robot.start(); //lancement des threads
    robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID
    robot.chronometerRobot().start(); //Chronometre général (match) du robot
/*
    robot.base().motorRight().applyMotorCode(200);
    robot.base().motorLeft().applyMotorCode(200);

    usleep(3000000);

    //config du pid marche avant
    robot.base().pidSpeedInitialize(pmx::LEFT, 42, 16.5, 0.1);
    robot.base().pidSpeedInitialize(pmx::RIGHT, 34, 13.4, 0.1);
    //Config du pid marche arrière
    robot.base().pidSpeedBackInitialize(pmx::LEFT, 40, 16.5, 0.1);
    robot.base().pidSpeedBackInitialize(pmx::RIGHT, 42, 16, 0.1);
    //Config pid position
    robot.base().pidPositionInitialize(pmx::LEFT, 0.14, 0.00001, 0.001);
    robot.base().pidPositionInitialize(pmx::RIGHT, 0.14, 0.00001, 0.001);
*/
    if(cap)
    {
        robot.base().vecteurCorrectionEnabled(true);
    }

    robot.base().moveD(targetX, targetY); //en tick

    logger().info() << "Arrived D: " << targetX / pmx::PositionManager::DISTANCE_PER_UP_PULSE << " mm " << targetY / pmx::PositionManager::DISTANCE_PER_UP_PULSE  << " mm " << utils::end;
    logger().info() << "Real    x: " << robot.position().x() << " y: " << robot.position().y()<< utils::end;
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
      
    robot.chronometerRobot().stop();
    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}
