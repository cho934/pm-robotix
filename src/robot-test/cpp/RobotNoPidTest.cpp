
/*!
 * \file
 * \brief Implémentation de la classe RobotNoPidTest.
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include "RobotNoPidTest.hpp"
#include "Robot.hpp"
#include "SpeedTracerFusion.hpp"
#include "Md25.hpp"

using namespace std;
using namespace pmx;

void test::RobotNoPidTest::run(int argc, char *argv[])
{
    //logger().info() << "test::RobotNoPidTest: Start" << utils::end;
    std::cout << "test::RobotNoPidTest: Start" << std::endl;
    int targetL, targetR, time;

    if (argc < 5)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] <<" [targetL(motorCode)] [targetR(motorCode)] [Time:ms]" << std::endl;
    }

    if (argc > 2)
    {
        targetL = atoi(argv[2]);
        std::cout << "target-left: " << atoi(argv[2]) << std::endl;
    }else
    {
        //demande de la distance x
        std::cout << "target-left: " << std::flush;
        std::cin >> targetL;
    }

    if (argc > 3)
    {
        targetR = atoi(argv[3]);
        std::cout << "target-right: " << atoi(argv[3]) << std::endl;
    }else
    {
        //demande de la distance y
        std::cout << "target-right: " << std::flush;
        std::cin >> targetR;
    }

    if (argc > 4)
    {
        time = atoi(argv[4]);
        std::cout << "Time: " << atoi(argv[4]) << std::endl;
    }else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "Time: " << std::flush;
        std::cin >> time;
    }

    pmx::Robot robot;

    //initialisation de la trace excel
    test::SpeedTracerFusion* tracer = new test::SpeedTracerFusion(&robot.base());
    robot.addListener(tracer);

    robot.start(); //lancement des threads
    
    utils::Md25::instance().setCommand(MD25_DISABLE_SPEED_REGULATION);

    //!\todo robot.base(). => changer ENCODERMOTOR

    sleep(1);
    robot.chronometerRobot().start(); //Chronometre général (match) du robot

    robot.base().motorRight().applyMotorCode(targetR);
    robot.base().motorLeft().applyMotorCode(targetL);
    usleep(time*1000);


    logger().info() << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;

    
    robot.stop();
    logger().info() << "End-Of-PMX : "
            << robot.chronometerRobot().getElapsedTimeInMicroSec() << " us "
            << utils::end;

    robot.chronometerRobot().stop();
}
