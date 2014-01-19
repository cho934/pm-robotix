/*!
 * \file
 * \brief Implémentation de la classe RobotFindPidTest.
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include "RobotFindPidTest.hpp"
#include "Robot.hpp"
#include "MotorWay.hpp"

using namespace std;
using namespace pmx;

void test::RobotFindPidTest::run(int argc, char *argv[])
{
    std::cout << "test::RobotFindPidTest: Start" << std::endl;

    double SpeedMotorRight, SpeedMotorLeft;
    uint startTime, wayToGo;
    double leftP, leftI, leftD;
    double rightP, rightI, rightD;

    if (argc < 5)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] << " [tickG=1...5] [tickD=1...5] [Tps(sec)] [PID_G] [PID_D] [1=FORWARD 2=BACK]" << std::endl;
    }

    if (argc > 2)
    {
        SpeedMotorLeft = atoi(argv[2]);
        std::cout << "Vitesse de départ moteur G en tick [1...5]: " << atoi(argv[2]) << std::endl;
    }else
    {
        //demande de la puissance moteur gauche à appliquer
        std::cout << "Vitesse de départ moteur G en tick [1...5]: " << std::flush;
        std::cin >> SpeedMotorLeft;
    }

    if (argc > 3)
    {
        SpeedMotorRight = atoi(argv[3]);
        std::cout << "Vitesse de départ moteur D en tick [1...5]: " << atoi(argv[3]) << std::endl;
    }else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "Vitesse de départ moteur D en tick [1...5]: " << std::flush;
        std::cin >> SpeedMotorRight;
    }

    if (argc > 4)
    {
        startTime = atoi(argv[4]);
        std::cout << "Temps de chaque phase en sec: " << atoi(argv[4]) << std::endl;
    }else
    {
        //demande du temps de marche
        std::cout << "Temps de chaque phase en sec: " << std::flush;
        std::cin >> startTime;
    }

    if (argc > 7)
    {
        leftP = atof(argv[5]);
        leftI = atof(argv[6]);
        leftD = atof(argv[7]);
        std::cout << "Gauche P: " << atof(argv[5]) << std::endl;
        std::cout << "       I: " << atof(argv[6]) << std::endl;
        std::cout << "       D: " << atof(argv[7]) << std::endl;
    }else
    {
        std::cout << "Gauche P: " << std::flush;
        std::cin >> leftP;
        std::cout << "       I: " << std::flush;
        std::cin >> leftI;
        std::cout << "       D: " << std::flush;
        std::cin >> leftD;
    }

    if (argc > 10)
    {
        rightP = atof(argv[8]);
        rightI = atof(argv[9]);
        rightD = atof(argv[10]);
        std::cout << "Droit  P: " << atof(argv[8]) << std::endl;
        std::cout << "       I: " << atof(argv[9]) << std::endl;
        std::cout << "       D: " << atof(argv[10]) << std::endl;
    }else
    {
        std::cout << "Droit  P: " << std::flush;
        std::cin >> rightP;
        std::cout << "       I: " << std::flush;
        std::cin >> rightI;
        std::cout << "       D: " << std::flush;
        std::cin >> rightD;
    }
    if (argc > 11)
    {
        wayToGo = atoi(argv[11]);
        std::cout << "Sens de marche: " << atoi(argv[11]) << std::endl;
    }else
    {
        //demande du sens de marche
        std::cout << "Sens de marche [1=FORWARD 2=BACK]: " << std::flush;
        std::cin >> wayToGo;
    }
    logger().debug() << "go" << utils::end;
    pmx::Robot robot; 
   
    logger().debug() << "chronometerRobot().start()" << utils::end;
    robot.chronometerRobot().start(); //Chronometre général (match) du robot

    robot.base().vecteurCorrectionEnabled(false); //Pas de rampe de vitesse
    robot.base().pidPositionEnabled(false);

    logger().debug() << "robot.start()" << utils::end;
    robot.start(); //lancement des threads
    robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID

    //activation du speedmanagerFusion
    logger().debug() << "pidCorrectionEnabled" << utils::end;
    robot.base().pidSpeedInitialize(pmx::LEFT, leftP, leftI, leftD);
    logger().debug() << "pidCorrectionEnabled" << utils::end;
    robot.base().pidSpeedInitialize(pmx::RIGHT,rightP, rightI, rightD);

    logger().debug() << "application du sens de marche" << utils::end;
    if (wayToGo == 2)
    {
        //activation du speedmanagerFusion
        logger().debug() << "pidCorrectionEnabled" << utils::end;
        robot.base().pidSpeedBackInitialize(pmx::LEFT, leftP, leftI, leftD);
        robot.base().pidSpeedBackInitialize(pmx::RIGHT,rightP, rightI, rightD);

        std::cout << "Sens de marche confirmé: BACK" << std::endl; 
        robot.base().orderWay(pmx::BBACK);
        robot.base().motorLeft().applyWay(pmx::BACK);
        robot.base().motorRight().applyWay(pmx::BACK);
    }else if (wayToGo == 1)
    {
        //activation du speedmanagerFusion
        logger().debug() << "pidCorrectionEnabled" << utils::end;
        robot.base().pidSpeedInitialize(pmx::LEFT, leftP, leftI, leftD);
        robot.base().pidSpeedInitialize(pmx::RIGHT,rightP, rightI, rightD);

        std::cout << "Sens de marche confirmé: FORWARD" << std::endl;
        robot.base().orderWay(pmx::BFORWARD);
        robot.base().motorLeft().applyWay(pmx::FORWARD);
        robot.base().motorRight().applyWay(pmx::FORWARD);
    }
    //laisse le temps aux relais de sens de marche de se positionner.
    while(!robot.base().motorLeft().wayApplied() || !robot.base().motorRight().wayApplied())
    {
        usleep(5000);
    }

    //ordre de vitesse de 0 à 5
    logger().debug() << "orderTick left" << utils::end;
    robot.base().motorLeft().orderTick(SpeedMotorLeft);
    logger().debug() << "orderTick right" << utils::end;
    robot.base().motorRight().orderTick(SpeedMotorRight);

    
    robot.base().pidSpeedActivate(); //start le timer de gestion PID


    //usleep(100000); //pour etre sûr que tout est bien lancé.
    logger().info() << "Changement de vitesse +5 :" << SpeedMotorLeft << utils::end;
    logger().debug() << "Sleep " << startTime << utils::end;
    usleep(startTime * 1000000);
/*
    //Changenent de vitesse
    logger().info() << "Changement de vitesse +5 :" << SpeedMotorLeft+5 << utils::end;
    robot.base().motorLeft().orderTick(SpeedMotorLeft+5);
    robot.base().motorRight().orderTick(SpeedMotorRight+5);
    usleep(startTime * 1000000);

    logger().info() << "Changement de vitesse +5 :" << SpeedMotorLeft+10 << utils::end;
    robot.base().motorLeft().orderTick(SpeedMotorLeft+10);
    robot.base().motorRight().orderTick(SpeedMotorRight+10);
    usleep(startTime * 1000000);

    logger().info() << "Changement de vitesse +5 :" << SpeedMotorLeft+15 << utils::end;
    robot.base().motorLeft().orderTick(SpeedMotorLeft+15);
    robot.base().motorRight().orderTick(SpeedMotorRight+15);
    usleep(startTime * 1000000);

    logger().info() << "Changement de vitesse +5 :" << SpeedMotorLeft+20 << utils::end;
    robot.base().motorLeft().orderTick(SpeedMotorLeft+20);
    robot.base().motorRight().orderTick(SpeedMotorRight+20);
    usleep(startTime * 1000000);
*/
    logger().debug() << "getElapsedTimeInSec" << utils::end;
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;

    logger().info() << "Stop" << utils::end;
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
    robot.chronometerRobot().stop();
    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}
