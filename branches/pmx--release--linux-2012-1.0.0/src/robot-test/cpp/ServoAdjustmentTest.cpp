/*!
 * \file
 * \brief Implémentation de la classe ServoAdjustmentTest.
 */

#include <cstdio>
#include <cstdlib>
#include "ServoAdjustmentTest.hpp"
#include "Robot.hpp"
#include "RobotInOutFactory.hpp"
#include "SimpleSensorListener.hpp"

using namespace std;
using namespace pmx;

void test::ServoAdjustmentTest::run(int argc, char *argv[])
{
    std::cout << "test::ServoAdjustmentTest: Start" << std::endl;

    int num;
    int initpos;

    if (argc < 4)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] <<"[NumServo:0-31] [PositionValue:0-4096] " << std::endl;
    }

    if (argc > 2)
    {
        num = atoi(argv[2]);
        std::cout << "numero servo: " << atoi(argv[2]) << std::endl;
    }else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "numero servo: " << std::flush;
        std::cin >> num;
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

    long time;
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

    robot.start(); //lancement des threads
    robot.chronometerRobot().start();

    robot.ledBar().k2Mil(50000);

    //utilisation directe des servomotors
    pmx::ServoMotorApf * servo = pmx::RobotInOutFactory::instance()->outServoMotor();

/*
    robot.startContact().wait();
    robot.rebootContact().wait();


    std::cout << "Clic start or reboot button to continue..." << std::endl;
    //attente de l'appui enfoncé du reboot ou du tirage du fil de départ
    while(robot.startContact().state() && !robot.startContact().state())
    {
        usleep(10000);
    }*/

    time = robot.chronometerRobot().getElapsedTimeInMicroSec();
    int currentPos = servo->getServoCurrentPosition(num);
    std::cout << "Servo" << num << ": current:" << currentPos << " to desired position: " << initpos << std::endl;
    servo->setServoPosition(num, initpos);
    servo->setServoEnable(num, 1);

    while(currentPos == initpos)
    {
        usleep(10);
    }
    time = robot.chronometerRobot().getElapsedTimeInMicroSec() - time;
    std::cout << "Servo" << num << ": current:" << currentPos << " to desired position: " << initpos << " Time: " << time << " us" << std::endl;

    //std::cout << "REGLAGE POSITION with start and reboot button..." << std::endl;
    std::cout << "REGLAGE POSITION : choose UP ('p') or DOWN('m') or Quit ('q')" << std::endl;

    int pos = initpos;
    char c;
    //boucle de reglage position
    while ( ( c = getchar() ) != 'q' )
    {
        /*
        if(c=='\n') //essayer avec ENTER '\n'
        {
            break;
        }*/

        if (c == 'p' || robot.startContact().state())
        {
            pos = pos + 50;
            servo->setServoPosition(num, pos);
            servo->setServoEnable(num, 1);
            std::cout << "Servo" << num << ": adjusted position: " << pos << std::endl;
        }
        
        if (c == 'm' || robot.rebootContact().state())
        {
            pos = pos - 50;
            servo->setServoPosition(num, pos);
            servo->setServoEnable(num, 1);
            std::cout << "Servo" << num << ": adjusted position: " << pos << std::endl;
        }
        
    }

    std::cout << "REGLAGE OFFSET : choose UP('p') or DOWN('m') or Quit ('q')" << std::endl;
    int offset = 0;

    //boucle de reglage offset
    while ( ( c = getchar() ) != 'q' )
    {
        /*
        if(c=='\n')
        {
            break;
        }*/

        if (c == 'p' || robot.startContact().state())
        {
            offset = offset + 50;
            servo->setServoOffset(num, offset);
            std::cout << "Servo" << num << ": adjusted offset: " << offset << std::endl;
        }
        if (c == 'm' || robot.rebootContact().state())
        {
            offset = offset - 50;
            servo->setServoOffset(num, offset);
            std::cout << "Servo" << num << ": adjusted offset: " << offset << std::endl;
        }
    }

    std::cout << "REGLAGE POSITION : choose UP('p') or DOWN('m') or Quit ('q')" << std::endl;

    pos = initpos;
    
    //boucle de reglage position
    while ( ( c = getchar() ) != 'q' )
    {
        if (c == 'p' || robot.startContact().state())
        {
            pos = pos + 50;
            servo->setServoPosition(num, pos);
            servo->setServoEnable(num, 1);
            std::cout << "Servo" << num << ": adjusted position: " << pos << std::endl;
        }
        if (c == 'm' || robot.rebootContact().state())
        {
            pos = pos - 50;
            servo->setServoPosition(num, pos);
            servo->setServoEnable(num, 1);
            std::cout << "Servo" << num << ": adjusted position: " << pos << std::endl;
        }
    }

    servo->setServoEnable(num, 0);

    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}
