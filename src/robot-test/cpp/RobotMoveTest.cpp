/*!
 * \file
 * \brief Implémentation de la classe RobotMoveTest.
 */

#include <string>
#include <iostream>
#include "RobotMoveTest.hpp"
#include "Robot.hpp"
#include "SpeedTracer.hpp"
#include "MotorWay.hpp"

using namespace std;
using namespace pmx;

void test::RobotMoveTest::run(int argc, char *argv[])
{
    logger().info() << "test::RobotMoveTest: Start" << utils::end;
    uint motorRight, motorLeft, startTime, wayToGo;
    double leftP, leftI, leftD;
    double rightP, rightI, rightD;
    
    if(argc < 5)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] <<" [VitesseG] [VitesseD] [Tps(sec)] [PID_G] [PID_D] [1=FORWARD 2=BACK]" << std::endl;
    }
    
    
    if(argc > 2)
    {
        motorLeft = atoi(argv[2]);
        std::cout << "Vitesse moteur G en mm/s: " << atoi(argv[2]) << std::endl;
    }
    else
    {
        //demande de la puissance moteur gauche à appliquer
        std::cout << "Vitesse moteur G en mm/s: " << std::flush;
        std::cin >> motorLeft;
    }
    
    if(argc > 3)
    {
        motorRight = atoi(argv[3]);
        std::cout << "Vitesse moteur D en mm/s: " << atoi(argv[3]) << std::endl;
    }
    else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "Vitesse moteur D en mm/s: " << std::flush;
        std::cin >> motorRight;
    }
    
    if(argc > 4)
    {
        startTime = atoi(argv[4]);
        std::cout << "Temps de fonctionnement en sec: " << atoi(argv[4]) << std::endl;
    }
    else
    {
        //demande du temps de marche
        std::cout << "Temps de fonctionnement en sec: " << std::flush;
        std::cin >> startTime;
    }
    
    if(argc > 7)
    {
        leftP = atof(argv[5]);
        leftI = atof(argv[6]);
        leftD = atof(argv[7]);
        std::cout << "Gauche P: " << atof(argv[5]) << std::endl;
        std::cout << "       I: " << atof(argv[6]) << std::endl;
        std::cout << "       D: " << atof(argv[7]) << std::endl;
    }
    else
    {
        std::cout << "Gauche P: " << std::flush;
        std::cin >> leftP;
        std::cout << "       I: " << std::flush;
        std::cin >> leftI;
        std::cout << "       D: " << std::flush;
        std::cin >> leftD;
    }
    
    if(argc > 10)
    {
        rightP = atof(argv[8]);
        rightI = atof(argv[9]);
        rightD = atof(argv[10]);
        std::cout << "Droit  P: " << atof(argv[8]) << std::endl;
        std::cout << "       I: " << atof(argv[9]) << std::endl;
        std::cout << "       D: " << atof(argv[10]) << std::endl;
    }
    else
    {
        std::cout << "Droit  P: " << std::flush;
        std::cin >> rightP;
        std::cout << "       I: " << std::flush;
        std::cin >> rightI;
        std::cout << "       D: " << std::flush;
        std::cin >> rightD;
    }
    if(argc > 11)
    {
        wayToGo = atoi(argv[11]);
        std::cout << "Sens de marche: " << atoi(argv[11]) << std::endl;
    }
    else
    {
        //demande du sens de marche
        std::cout << "Sens de marche [1=FORWARD 2=BACK]: " << std::flush;
        std::cin >> wayToGo;
    }
    logger().debug() << "go" << utils::end;
    
    pmx::Robot robot;
    logger().debug() << "robot.start()" << utils::end;
    robot.start(); //lancement des threads
    logger().debug() << "chronometerRobot().start()" << utils::end;
    robot.chronometerRobot().start(); //Chronometre général (match) du robot
    logger().debug() << "application du sens de marche" << utils::end;
    
    if (wayToGo == 2)
    {
        std::cout << "Sens de marche confirmé: BACK" << std::endl;
        robot.base().motorLeft().applyWay(pmx::BACK);
        robot.base().motorRight().applyWay(pmx::BACK);
        pthread_yield();
    }
    else if(wayToGo == 1)
    {
        std::cout << "Sens de marche confirmé: FORWARD" << std::endl;
        
        robot.base().motorLeft().applyWay(pmx::FORWARD);
        robot.base().motorRight().applyWay(pmx::FORWARD);
        pthread_yield();
    }
    
    logger().debug() << "speedCorrectionEnabled" << utils::end;
    robot.base().motorLeft().speedCorrectionEnabled(leftP, leftI, leftD);
    logger().debug() << "orderSpeed left" << utils::end;
    robot.base().motorLeft().orderSpeed(motorLeft);
    logger().debug() << "speedCorrectionEnabled" << utils::end;
    robot.base().motorRight().speedCorrectionEnabled(rightP, rightI, rightD);
    logger().debug() << "orderSpeed right" << utils::end;
    robot.base().motorRight().orderSpeed(motorRight);
    pthread_yield();
    
    logger().debug() << "Tracer" << utils::end;
    
    test::SpeedTracer* leftTracer = new test::SpeedTracer(&robot.base().motorLeft());
    test::SpeedTracer* rightTracer = new test::SpeedTracer(&robot.base().motorRight());
    
    logger().debug() << "addListener" << utils::end;
    robot.addListener(leftTracer);
    robot.addListener(rightTracer);
    logger().debug() << "while" << utils::end;
    while(robot.chronometerRobot().getElapsedTimeInSec() < startTime)
    {
        pthread_yield();
    }
    logger().debug() << "getElapsedTimeInSec" << utils::end;
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
    
    logger().info() << "Stop" << utils::end;
    robot.base().stop();
    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
    pthread_yield();
    robot.chronometerRobot().stop();
    robot.stop();
}
