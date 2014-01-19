/*!
 * \file
 * \brief Implémentation de la classe RobotMoveByIncrementTest.
 */

#include <string>
#include <iostream>
#include "RobotMoveByIncrementTest.hpp"
#include "Robot.hpp"
//#include "SpeedTracer.hpp"
#include "SpeedTracerFusion.hpp"

void test::RobotMoveByIncrementTest::run(int, char *[])
{
    std::cout << "test::RobotMoveByIncrementTest: Start" << std::endl;
    
    pmx::Robot robot;
    robot.start();
    robot.chronometerRobot().start();
    //Pas de correction de position par rapport au vecteur d'approche.
    robot.base().vecteurCorrectionEnabled(false); //Pas de rampe de vitesse
    robot.base().pidPositionEnabled(false);
    robot.base().pidSpeedEnabled(false); //Pas de PID et donc pas de SpeedManager onTimer

    //initialisation de la trace excel
    test::SpeedTracerFusion* tracer = new test::SpeedTracerFusion(&robot.base());
    robot.addListener(tracer);
    
    //incrémentation du code moteur
    for(ushort i = 1; i < 1024; i++)
    {
        robot.base().motorLeft().applyMotorCode(i);
        tracer->currentMotorCodeLeft(i);
        robot.base().motorRight().applyMotorCode(i);
        tracer->currentMotorCodeRight(i);
        
        usleep(150000);
        logger().info() << " Code : " << i << " " << robot.chronometerRobot().getElapsedTimeInMicroSec() << utils::end;
        robot.chronometerRobot().start(); //reinitialisation du compteur de temps
    }
    logger().info() << "Robot Stop()" << utils::end;
    robot.stop();    
    robot.chronometerRobot().stop();

    //calcul le rapport vitesse / motorcode de chaque moteur.
    tracer->computeApproximation(logger());
}
