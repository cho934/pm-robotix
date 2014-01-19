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

void test::ServoAdjustmentTest::run(int argc, char *argv[]) {
    std::cout << "test::ServoAdjustmentTest: Start" << std::endl;

    int num;
    int initpos;

    logger().info() << "USAGE: PMX_TEST " << argv[1] << "[NumServo:0-31] [PositionValue:0-4096] " << utils::end;

    if (argc > 2) {
        num = atoi(argv[2]);
        logger().info() << "numero servo: " << atoi(argv[2]) << utils::end;
    }else {
        //demande de la vitesse moteur droit à appliquer
        logger().info() << "numero servo: " << utils::end;
        std::cin >> num;
    }
    if (argc > 3) {
        initpos = atoi(argv[3]);
        logger().info() << "position value: " << atoi(argv[3]) << utils::end;
    }else {
        //demande de la vitesse moteur droit à appliquer
        logger().info() << "position value: " << utils::end;
        std::cin >> initpos;
    }

    long time;
    pmx::Robot robot;
/*
    //Désactivation des moteurs, permet de ne pas envoyer d'action (applyMotorCode).
    robot.base().motorLeft().disabled(false);
    robot.base().motorRight().disabled(false);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().pidPositionEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidSpeedEnabled(false);
    robot.base().pidSpeedDesactivate();
    robot.firePulseEnabled(false);
*/
    robot.start(); //lancement des threads
    robot.chronometerRobot().start();

    robot.ledBar().startK2Mil(50000, 50000, false);

    //utilisation directe des servomotors
    pmx::ServoMotorApf * servo = pmx::RobotInOutFactory::instance()->outServoMotor();
/*
    servo->setServoPosition(0, 2000);
    servo->setServoEnable(0, 1);
    servo->setServoPosition(1, 2000);
    servo->setServoEnable(1, 1);
    servo->setServoPosition(2, 2000);
    servo->setServoEnable(2, 1);
    servo->setServoPosition(3, 2000);
    servo->setServoEnable(3, 1);
    servo->setServoPosition(4, 2000);
    servo->setServoEnable(4, 1);

*/

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
    logger().info() << "Servo" << num << ": current:" << currentPos << " to desired position: " << initpos << utils::end;
    servo->setServoPosition(num, initpos);
    servo->setServoEnable(num, 1);

    while (currentPos == initpos) {
        usleep(10);
    }
    time = robot.chronometerRobot().getElapsedTimeInMicroSec() - time;
    logger().info() << "Servo" << num << ": current:" << currentPos << " to desired position: " << initpos << " Time: " << time << " us" << utils::end;

    //std::cout << "REGLAGE POSITION with start and reboot button..." << std::endl;
    logger().info() << "REGLAGE POSITION : choose UP ('p') or DOWN('m') or Quit ('q')" << utils::end;

    int pos = initpos;
    char c;


    if (&robot == NULL) {
        logger().error() << "Robot is null" << utils::end;
    }else if (&robot.startContact() == NULL) {
        logger().error() << "robot.startContact()==NULL" << utils::end;
    }else if (&robot.rebootContact() == NULL) {
        logger().error() << "robot.rebootContact()==NULL" << utils::end;
    }else {
        //boucle de reglage position
        while ((c = getchar()) != 'q') {
            if (c == 'p' || robot.startContact().state()) {
                pos = pos + 50;
                logger().info() << "Servo" << num << ": START: adjusted position=" << pos << " getServoCurrentPosition=" << servo->getServoCurrentPosition(num) << utils::end;

                servo->setServoPosition(num, pos);
                //servo->setServoEnable(num, 1);
                //std::cout << "Servo" << num << ": adjusted position=" << pos << " getServoCurrentPosition=" << servo->getServoCurrentPosition(num) << std::endl;
                logger().debug() << "Servo" << num << ": END  : adjusted position=" << pos << " getServoCurrentPosition=" << servo->getServoCurrentPosition(num) << utils::end;

            }else if (c == 'm' || robot.rebootContact().state()) {
                pos = pos - 50;
                logger().info() << "Servo" << num << ": START: adjusted position=" << pos << " getServoCurrentPosition=" << servo->getServoCurrentPosition(num) << utils::end;

                servo->setServoPosition(num, pos);
                //servo->setServoEnable(num, 1);
                //std::cout << "Servo" << num << ": adjusted position=" << pos << " getServoCurrentPosition=" << servo->getServoCurrentPosition(num) << std::endl;
                logger().debug() << "Servo" << num << ": END  :adjusted position=" << pos << " getServoCurrentPosition=" << servo->getServoCurrentPosition(num) << utils::end;

            }
            //usleep(10000);
        }
    }
    /*
        std::cout << "REGLAGE OFFSET : choose UP('p') or DOWN('m') or Quit ('q')" << std::endl;
        int offset = 0;

        //boucle de reglage offset
        while ( ( c = getchar() ) != 'q' )
        {
        
            //if(c=='\n')
            //{
            //    break;
            //}

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
                //servo->setServoEnable(num, 1);
                std::cout << "Servo" << num << ": adjusted position: " << pos << std::endl;
            }
            if (c == 'm' || robot.rebootContact().state())
            {
                pos = pos - 50;
                servo->setServoPosition(num, pos);
                //servo->setServoEnable(num, 1);
                std::cout << "Servo" << num << ": adjusted position: " << pos << std::endl;
            }
        }
     */
    servo->setServoEnable(num, 0);


/*
    servo->setServoEnable(0, 0);

    servo->setServoEnable(1, 0);

    servo->setServoEnable(2, 0);

    servo->setServoEnable(3, 0);

    servo->setServoEnable(4, 0);
*/
    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}
