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

void test::ServoTest::run(int argc, char *argv[])
{
    std::cout << "test::ServoTest: Start" << std::endl;
/*
    int servo;
    int initpos;

    std::cout << "USAGE: PMX_TEST " << argv[1] <<"[NumServo 0:levier 1:serrage 2:couleur 3:ballon] [PositionValue:1-2-3] " << std::endl;


    if (argc > 2)
    {
        servo = atoi(argv[2]);
        std::cout << "numero servo: " << atoi(argv[2]) << std::endl;
    }else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "numero servo: " << std::flush;
        std::cin >> servo;
    }
    if (argc > 3)
    {
        initpos = atoi(argv[3]);
        std::cout << "position value: " << atoi(argv[3]) << std::endl;
    }else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "position value: " << std::flush;
        std::cin >> initpos;
    }

*/



    pmx::Robot robot;

    logger().debug() << "Disable All features..." << utils::end;
    //Désactivation des moteurs, permet de ne pas envoyer d'action (applyMotorCode).
    robot.base().motorLeft().disabled(false);
    robot.base().motorRight().disabled(false);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().pidPositionEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidSpeedEnabled(false);
    robot.base().pidSpeedDesactivate();
    robot.firePulseEnabled(false);

    logger().info() << "WARNING : using file robot_pmxtest.conf..." << utils::end;
    robot.configure("robot_pmxtest.conf");

    //config
    logger().info() << "servoColorSorting min :" << robot.servoColorSorting().min() << utils::end;
    logger().info() << "servoColorSorting med :" << robot.servoColorSorting().med() << utils::end;
    logger().info() << "servoColorSorting max :" << robot.servoColorSorting().max() << utils::end;

    logger().info() << "servoBalloonInflate min :" << robot.servoBalloonInflate().min() << utils::end;
    logger().info() << "servoBalloonInflate med :" << robot.servoBalloonInflate().med() << utils::end;
    logger().info() << "servoBalloonInflate max :" << robot.servoBalloonInflate().max() << utils::end;

    robot.start(); //lancement des threads
    
    robot.chronometerRobot().start(); //Chronometre général (match) du robot


    logger().info() << "pressed 1 2 3 ..." << utils::end;

    char c;
    //boucle de reglage position
    while ( ( c = getchar() ) != 'q' )
    {
        if (c == '1') //|| !robot.startContact().state())
        {
            logger().info() << "1 pressed... servoColorSorting" << utils::end;
            usleep(10000);
            
            logger().info() << "MEDIUM" << utils::end;
            robot.servoColorSorting().turnMed(true);

            logger().info() << "MIN" << utils::end;
            robot.servoColorSorting().turnMin(true);

            logger().info() << "MEDIUM" << utils::end;
            robot.servoColorSorting().turnMed(true);

        }

        if (c == '2')
        {
            logger().info() << "2 pressed... servoBalloonInflate" << utils::end;
            usleep(10000);
            
            logger().info() << "MAX" << utils::end;
            robot.servoBalloonInflate().turnMax(true);

            
            logger().info() << "MIN" << utils::end;
            robot.servoBalloonInflate().turnMin(false);
            usleep(3000000);

            logger().info() << "MIN" << utils::end;
            robot.servoBalloonInflate().turnMin(true);


        }

         if (c == '3')
        {
            logger().info() << "3 pressed... servoLevier" << utils::end;
            usleep(10000);

            logger().info() << "MAX" << utils::end;
            robot.servoLevier().turnMax(true);

            usleep(2000000);
            logger().info() << "MIN" << utils::end;
            robot.servoLevier().turnMin(false);
            usleep(2000000);

            logger().info() << "MIN" << utils::end;
            robot.servoLevier().turnMin(true);
            usleep(2000000);

        }
        //logger().debug() << " getServoCurrentPosition ID=" << robot.servoColorSorting().id() << " pos=" << robot.servoColorSorting().getServoCurrentPosition(robot.servoColorSorting().id()) << utils::end;

        logger().info() << "while" << utils::end;

    }

/*

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
  */
    
    logger().info() << "chrono stop" << utils::end;
    robot.chronometerRobot().stop();
    logger().info() << "robot stop" << utils::end;
    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}

