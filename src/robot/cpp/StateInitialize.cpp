/*!
 * \file
 * \brief Implémentation de la classe StateInitialize.
 */

#include "StateInitialize.hpp"
#include "StateWaitForReboot.hpp"
#include "StateAdjustRobotPosition.hpp"
#include "Robot.hpp"
#include "LedAction.hpp"
#include "StateWaitForStart.hpp"
#include "HstateMoveToPawn.hpp"

pmx::IAutomateState*
pmx::automate::StateInitialize::execute(Robot& robot)
{
    this->logger().info() << "start" << utils::end;
    bool error = false;

    //actions d'initialisation
    logger().info() << "initialisation..." << utils::end;

    robot.clamp().close();
    while(robot.clamp().stateOpened())
    {
        usleep(10000);
    }

    //prise en compte de la couleur de match
    robot.colorContact().wait();
    for(int i=0;i<8;i++)
    {
        robot.ledBar().setOn(i);
        usleep(300000);
    }
    robot.ledBar().blink(10);
    robot.ledBar().reset();


    if (robot.colorContact().state())
    {
        robot.myColorIs(pmx::RED);
        logger().info() << "COLOR : RED" << utils::end;
    }else
    {
        robot.myColorIs(pmx::BLUE);
        logger().info() << "COLOR : BLUE" << utils::end;
    }
    robot.colorContact().stop(true);

    //descente de l'ascenseur
    robot.elevator().goLowPosition();
    sleep(4);
    //monter en position little
    robot.elevator().goLittlePosition();
    while(robot.elevator().state() != pmx::ELEVATORLITTLE)
    {
        usleep(5000);
    }
    robot.elevator().noPosition();

    //ouverture et fermeture des pinces
    robot.clamp().openWidePosition();
    while(!robot.clamp().stateOpened())
    {
        usleep(10000);
    }
    robot.clamp().close();
    while(robot.clamp().stateOpened())
    {
        usleep(10000);
    }

    //!\todo test des elements mecanique

    //!\todo init camera/seuillage lumière

    

    logger().info() << "End initialisation..." << utils::end;

    if(robot.modeZap() == 1)
    {
        return new pmx::automate::HstateMoveToPawn();
    }

    if (error)
    {
        return new pmx::automate::StateWaitForReboot();
    }else
    {
        logger().info() << "clic RESET..." << utils::end;
        robot.ledBar().k2Mil();
        robot.rebootContact().wait();
        //attente d'un clic (seuil bas + seuil haut)
        while (!robot.rebootContact().state())
        {
            usleep(10000);
        }
        while (robot.rebootContact().state())
        {
            usleep(10000);
        }
        robot.rebootContact().stop(true); //arrete le listener associé.
        robot.ledBar().stop(true);
        robot.ledBar().reset();

        //return new pmx::automate::StateAdjustRobotPosition();
        return new pmx::automate::StateWaitForStart();
    }
}
