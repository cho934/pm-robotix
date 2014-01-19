/*!
 * \file
 * \brief Implémentation de la classe RobotMoveToPawnTest.
 */

#include "RobotMoveToPawnTest.hpp"

void test::RobotMoveToPawnTest::run(int argc, char *argv[])
{

    //int speedmin = 18; //en tick
    int motorcodemin = 400; //motorcode
    int distmin = 280;

    //logger().info() << "test::RobotMoveToPawnTest: Start" << utils::end;
    std::cout << "test::RobotMoveToPawnTest: Start" << std::endl;
    pmx::Robot robot;

    robot.configure("robot_pmxtest.conf");

    robot.base().pidPositionEnabled(false);
    robot.base().vecteurCorrectionEnabled(false);

    robot.start(); //lancement des threads
    robot.chronometerRobot().start(); //Chronometre général (match) du robot

    robot.base().motorLeft().applyWay(pmx::FORWARD);
    robot.base().motorRight().applyWay(pmx::FORWARD);

    robot.base().motorLeft().applyMotorCode(motorcodemin);
    robot.base().motorRight().applyMotorCode(motorcodemin);


    robot.pawnLeftIrSensor().getObjectDistance();//active le listener:
    robot.pawnLeftIrSensor().reset(); //reset des valeurs


    robot.pawnRightIrSensor().getObjectDistance();//active le listener:
    robot.pawnRightIrSensor().reset();

    robot.pawnLeftIrSensor().active(true); //activation des calculs
    robot.pawnRightIrSensor().active(true); //activation des calculs

    int distPawnLeft;
    int distPawnRight;
    while(robot.chronometerRobot().getElapsedTimeInSec()<60)
    {
        usleep(50000);

        robot.pawnLeftIrSensor().reset(); //reset des valeurs
        robot.pawnLeftIrSensor().active(true); //activation des calculs
        while(robot.pawnLeftIrSensor().received() == false) //attente de la reponse
        {
            usleep(100);
        }
        distPawnLeft = robot.pawnLeftIrSensor().distanceMm();

        robot.pawnRightIrSensor().reset(); //reset des valeurs
        robot.pawnRightIrSensor().active(true); //activation des calculs
        while(robot.pawnRightIrSensor().received() == false) //attente de la reponse
        {
            usleep(100);
        }
        distPawnRight = robot.pawnRightIrSensor().distanceMm();

        logger().info() << " distPawnLeft : "
                << distPawnLeft
                << " distPawnRight: " << distPawnRight
                << utils::end;

        if(distPawnLeft<distmin && distPawnRight<distmin)
        {
            robot.base().motorLeft().applyMotorCode(0);
            robot.base().motorRight().applyMotorCode(0);

        }else if(distPawnLeft>distmin && distPawnRight>distmin)
        {
            robot.base().motorLeft().applyMotorCode(motorcodemin);
            robot.base().motorRight().applyMotorCode(motorcodemin);
        }else if((distPawnLeft<distmin && distPawnRight>distmin) || (distPawnLeft>distmin && distPawnRight<distmin)) //si detection
        {
            if(distPawnLeft>distPawnRight)
            {
                robot.base().motorLeft().applyMotorCode(0);
                robot.base().motorRight().applyMotorCode(motorcodemin);
            }else if(distPawnLeft<distPawnRight)
            {
                robot.base().motorLeft().applyMotorCode(motorcodemin);
                robot.base().motorRight().applyMotorCode(0);
            }
        }
    }

    robot.pawnLeftIrSensor().stop(true);
    robot.pawnRightIrSensor().stop(true);
    
    robot.chronometerRobot().stop();
    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;   
}
