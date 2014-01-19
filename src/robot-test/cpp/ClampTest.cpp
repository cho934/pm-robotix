/*!
 * \file
 * \brief Implémentation de la classe ClampTest.
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include "ClampTest.hpp"
#include "Robot.hpp"

using namespace std;
using namespace pmx;

void test::ClampTest::run(int, char**)
{
    //!\TODO utiliser les argv pour lancer des actions indépendantes


    pmx::Robot robot;

    robot.ledBar().k2Mil();

    logger().debug() << "configure(robot_pmxtest.conf)" << utils::end;
    robot.configure("robot_pmxtest.conf");
    
    robot.start(); //lancement des threads
    
    robot.chronometerRobot().start(); //Chronometre général (match) du robot

    logger().info() << "ledBar..." << utils::end;
    /*
    logger().info() << "elevator high" << utils::end;
    robot.elevator().goHighPosition();
    sleep(4);

    logger().info() << "elevator low" << utils::end;
    robot.elevator().goLowPosition();
    sleep(4);
    
    logger().info() << "elevator middle" << utils::end;
    robot.elevator().goMiddlePosition();
    while(robot.elevator().state() != pmx::ELEVATORMIDDLE)
    {
        usleep(5000);
    }
*/
    logger().info() << "elevator low" << utils::end;
    robot.elevator().goLowPosition();
    sleep(2);
/*
    logger().info() << "openWidePosition" << utils::end;
    robot.clamp().openWidePosition();
    while(robot.clamp().stateOpened() == 0)
    {
        usleep(10000);
    }
*/
    logger().info() << "keep close" << utils::end;
    robot.clamp().keepClose();
    while(robot.clamp().stateOpened() == 1)
    {
        usleep(10000);
    }

    logger().info() << "elevator middle" << utils::end;
    robot.elevator().goMiddlePosition();
    while(robot.elevator().state() != pmx::ELEVATORMIDDLE)
    {
        usleep(5000);
    }

    usleep(6000000);

    logger().info() << "close" << utils::end;
    robot.clamp().close();
    while(robot.clamp().stateOpened() == 1)
    {
        usleep(10000);
    }

    usleep(1000000);

    logger().info() << "openWidePosition" << utils::end;
    robot.clamp().openWidePosition();
    while(robot.clamp().stateOpened() == 0)
    {
        usleep(10000);
    }

    robot.elevator().noPosition();

    robot.chronometerRobot().stop();
    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}
