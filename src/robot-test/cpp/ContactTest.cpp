/*!
 * \file
 * \brief Implementation de la classe ContactTest.
 */

#include <iostream>
#include "ContactTest.hpp"
#include "Robot.hpp"
#include "SimpleSensorListener.hpp"

void test::ContactTest::run(int, char *[])
{
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

    robot.start();
    robot.chronometerRobot().start(); //Chronometre général (match) du robot
    logger().info() << "Start - for 20 seconds" << utils::end;

    robot.startContact().wait();
    robot.rebootContact().wait();
    robot.colorContact().wait();
    robot.leftBackContact().wait();
    robot.rightBackContact().wait();

    bool startContactOldState = true;
    bool rebootContactOldState = true;
    bool colorContactOldState = true;
    bool leftBackContactOldState = true;
    bool rightBackContactOldState = true;

    while(robot.chronometerRobot().getElapsedTimeInSec() <= 20)
    {

        //start contact
        if(startContactOldState != robot.startContact().state())
        {
            logger().info() << "startContact: mu:" << robot.startContact().mu()
                    << " pin:" << robot.startContact().pin()
                    << " value:" << robot.startContact().state()
                    << utils::end;
        }
        startContactOldState = robot.startContact().state();

        //reboot contact
        if(rebootContactOldState != robot.rebootContact().state())
        {
            logger().info() << "rebootContact: mu:" << robot.rebootContact().mu()
                    << " pin:" << robot.rebootContact().pin()
                    << " value:" << robot.rebootContact().state()
                    << utils::end;
        }
        rebootContactOldState = robot.rebootContact().state();

        //color contact
        if(colorContactOldState != robot.colorContact().state())
        {
            logger().info() << "colorContact: mu:" << robot.colorContact().mu()
                    << " pin:" << robot.colorContact().pin()
                    << " value:" << robot.colorContact().state()
                    << utils::end;
        }
        colorContactOldState = robot.colorContact().state();

        //leftBackContact contact
        if(leftBackContactOldState != robot.leftBackContact().state())
        {
            logger().info() << "leftBackContact: mu:" << robot.leftBackContact().mu()
                    << " pin:" << robot.leftBackContact().pin()
                    << " value:" << robot.leftBackContact().state()
                    << utils::end;
        }
        leftBackContactOldState = robot.leftBackContact().state();

        //rightBackContact contact
        if(rightBackContactOldState != robot.rightBackContact().state())
        {
            logger().info() << "rightBackContact: mu:" << robot.rightBackContact().mu()
                    << " pin:" << robot.rightBackContact().pin()
                    << " value:" << robot.rightBackContact().state()
                    << utils::end;
        }
        rightBackContactOldState = robot.rightBackContact().state();

        usleep(10000);
    }

    robot.startContact().stop(true);
    robot.rebootContact().stop(true);
    robot.colorContact().stop(true);
    robot.leftBackContact().stop(true);
    robot.rightBackContact().stop(true);

    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}
