/*!
 * \file
 * \brief Implementation de la classe DistanceDetectorTest.
 */

#include <iostream>
#include "DistanceDetectorTest.hpp"
#include "Robot.hpp"

#include "RobotInOutFactory.hpp"
#include "IRobotOut.hpp"
#include "IRobotIn.hpp"

void test::DistanceDetectorTest::run(int argc, char *argv[])
{
    uint device;
    if(argc < 2)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] <<" [1=OPPONENT 2=LEFT-BORDER 3=RIGHT-BORDER]" << std::endl;
    }
    if(argc > 2)
    {
        device = atoi(argv[2]);
        std::cout << "Choix du GP2 [1=OPPONENT 2=LEFT-BORDER 3=RIGHT-BORDER] : " << atoi(argv[2]) << std::endl;
    }
    else
    {
        std::cout << "Choix du GP2: " << std::flush;
        std::cin >> device;
    }
    
    logger().info() << "Start (30s)" << utils::end;
    
    pmx::Robot robot;
    robot.start();
    robot.chronometerRobot().start(); //Chronometre général (match) du robot

    while(robot.chronometerRobot().getElapsedTimeInSec() <= 30)
    {
        if(device == 1)
        {
            if(robot.frontDistanceOpponent().received() == 1)
            {
                logger().info() << "frontDistanceOpponent:" << robot.frontDistanceOpponent().distance() << " : " << robot.frontDistanceOpponent().distanceMm() << "mm : Time: " << robot.chronometerRobot().getElapsedTimeInMicroSec() << utils::end;   
            }
            //relance d'une nouvelle valeur
            robot.frontDistanceOpponent().active(true);
        }
        if(device == 2)
        {
            if(robot.leftDistanceBorder().received() == 1)
            {
                logger().info() << "leftDistanceBorder:" << robot.leftDistanceBorder().distance() << " : " << robot.leftDistanceBorder().distanceMm() << "mm : Time: " << robot.chronometerRobot().getElapsedTimeInMicroSec() << utils::end;   
            }
            //relance d'une nouvelle valeur
            robot.leftDistanceBorder().active(true);
        }
        if(device == 3)
        {
            if(robot.rightDistanceBorder().received() == 1)
            {
                logger().info() << "rightDistanceBorder:" << robot.rightDistanceBorder().distance() << " : " << robot.rightDistanceBorder().distanceMm() << "mm : Time: " << robot.chronometerRobot().getElapsedTimeInMicroSec() << utils::end;   
            }
            //relance d'une nouvelle valeur
            robot.rightDistanceBorder().active(true);
        }
        usleep(500000);
        pthread_yield();
    }
    robot.stop();
    logger().info() << "End" << utils::end;
    
}
