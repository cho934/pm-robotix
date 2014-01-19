/*!
 * \file
 * \brief Implémentation de la classe ClampTest.
 */

#include <string>
#include <iostream>
#include <cstdlib>
#include "ServoTest.hpp"
#include "Robot.hpp"

using namespace std;
using namespace pmx;

void test::ServoTest::run(int, char**)
{
    //!\TODO utiliser les argv pour lancer des actions indépendantes


    pmx::Robot robot;

    //Désactivation des moteurs, permet de ne pas envoyer d'action (applyMotorCode).
    robot.base().motorLeft().disabled(false);
    robot.base().motorRight().disabled(false);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().pidPositionEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidSpeedEnabled(false);
    robot.base().pidSpeedDesactivate();
    robot.firePulseEnabled(false);


    robot.ledBar().k2Mil(600000);

    logger().debug() << "configure(robot_pmxtest.conf)" << utils::end;
    robot.configure("robot_pmxtest.conf");
    
    robot.start(); //lancement des threads
    
    robot.chronometerRobot().start(); //Chronometre général (match) du robot

    logger().info() << "ledBar..." << utils::end;

    logger().info() << "Fork - forkHighPosition=" << robot.forkCenter().forkHighPosition()
            << " forkLowPosition=" << robot.forkCenter().forkLowPosition()
            << utils::end;

    logger().info() << "goHigh" << utils::end;
    robot.forkCenter().goHighPosition();
    robot.forkCenter().waitPositionReached();

    logger().info() << "goLow" << utils::end;
    robot.forkCenter().goLowPosition();


    sleep(3);

    logger().info() << "goHigh" << utils::end;
    robot.forkCenter().goHighPosition();
   
    logger().info() << "goLow" << utils::end;
    robot.forkCenter().goLowPosition();
    

    logger().info() << "turnForkLeft goLow" << utils::end;
    robot.turnForkLeft().goLowPosition();
   

    logger().info() << "turnForkRight goLow" << utils::end;
    robot.turnForkRight().goLowPosition();
   

    logger().info() << "forkLeft goLow" << utils::end;
    robot.forkLeft().goLowPosition();
    

    logger().info() << "forkRight goLow" << utils::end;
    robot.forkRight().goLowPosition();

  logger().info() << "chrono stop" << utils::end;

    robot.chronometerRobot().stop();
    logger().info() << "robot stop" << utils::end;
    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}

