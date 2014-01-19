/*!
 * \file
 * \brief Implémentation de la classe RobotMoveByIncrementTest.
 */

#include <string>
#include <iostream>
#include "RobotMoveByIncrementTest.hpp"
#include "Robot.hpp"
#include "SpeedTracerFusion.hpp"
#include "Md25.hpp"

void test::RobotMoveByIncrementTest::run(int, char *[])
{
    std::cout << "test::RobotMoveByIncrementTest: Start" << std::endl;
    
    pmx::Robot robot;
    robot.start();
    robot.chronometerRobot().start();

    robot.base().pidSpeedEnabled(false);
    robot.base().pidPositionEnabled(false);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidSpeedDesactivate(); //par defaut
    
    utils::Md25::instance().setCommand(MD25_DISABLE_SPEED_REGULATION);

    //initialisation de la trace excel
    test::SpeedTracerFusion* tracer = new test::SpeedTracerFusion(&robot.base());
    robot.addListener(tracer);

    
    
    //incrémentation du code moteur
    for(ushort i = 1; i < 128; i++)
    {
        robot.base().motorLeft().applyMotorCode(i);
        robot.base().motorRight().applyMotorCode(i);

        usleep(100000);
        tracer->currentMotorCodeLeft(i);
        tracer->currentMotorCodeRight(i);

        logger().info() << " Code : " << i << " " << robot.chronometerRobot().getElapsedTimeInMicroSec()
                << " " << utils::Md25::instance().getBatteryVolts()
                << " 1Current:" << utils::Md25::instance().getMotor1Current()
                << " 2Current:" << utils::Md25::instance().getMotor2Current() << utils::end;
        robot.chronometerRobot().start(); //reinitialisation du compteur de temps
    }
    logger().info() << "Robot Stop()" << utils::end;
    robot.stop();    
    robot.chronometerRobot().stop();

    //calcul le rapport vitesse / motorcode de chaque moteur.
    tracer->computeApproximation(logger());

    logger().info() << "End-Of-PMX : "
            << robot.chronometerRobot().getElapsedTimeInMicroSec() << " us "
            << utils::end;
}
