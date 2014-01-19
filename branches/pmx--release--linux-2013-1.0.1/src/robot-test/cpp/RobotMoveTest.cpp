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
    int targetL, targetR, cap, timems;

    std::cout << "USAGE: PMX_TEST " << argv[1] <<" [Time(ms)] [targetL(-127=>128)] [targetR(-127=>128)] [capActivation:0-1]" << std::endl;

    if (argc > 2)
    {
        timems = atoi(argv[2]);
        std::cout << "time(ms): " << atoi(argv[2]) << std::endl;
    }else
    {
        //demande de la distance x
        std::cout << "time(ms): " << std::flush;
        std::cin >> timems;
    }

    if (argc > 3)
    {
        targetL = atoi(argv[3]);
        std::cout << "targetL(-127=>128): " << atoi(argv[3]) << std::endl;
    }else
    {
        //demande de la distance x
        std::cout << "targetL(-127=>128): " << std::flush;
        std::cin >> targetL;
    }

    if (argc > 4)
    {
        targetR = atoi(argv[4]);
        std::cout << "targetR(-127=>128): " << atoi(argv[4]) << std::endl;
    }else
    {
        //demande de la distance y
        std::cout << "targetR(-127=>128): " << std::flush;
        std::cin >> targetR;
    }

    if (argc > 5)
    {
        cap = atoi(argv[5]);
        std::cout << "Cap correction: " << atoi(argv[5]) << std::endl;
    }else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "Cap correction: " << std::flush;
        std::cin >> cap;
    }

    pmx::Robot robot;

    robot.start(); //lancement des threads
    robot.chronometerRobot().start(); //Chronometre général (match) du robot
    //robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID
    robot.base().motorRight().applyMotorCode(targetR);
    robot.base().motorLeft().applyMotorCode(targetL);
    usleep(timems * 1000);

    robot.chronometerRobot().stop();
    robot.stop();

    logger().info() << "Arrived targetR=" << targetR << " targetL=" << targetL  << utils::end;
    logger().info() << "Arrived Real    x: " << robot.position().x() << " y: " << robot.position().y()<< utils::end;
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
      
    
    logger().info() << "End-Of-PMX : "
            << robot.chronometerRobot().getElapsedTimeInMicroSec() << " us "
            << utils::end;
}
