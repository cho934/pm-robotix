/*!
 * \file
 * \brief Implémentation de la classe StateInitialize.
 */

#include "StateInitialize.hpp"
#include "Robot.hpp"
#include "LedAction.hpp"
#include "LedIndicator.hpp"

pmx::IAutomateState*
pmx::StateInitialize::execute(Robot& robot, void *)
{
    this->logger().info() << "start" << utils::end;
    bool error = false;
/*
    //actions d'initialisation
    logger().info() << "Initialize mechanical..." << utils::end;



    robot.forkCenter().goHighPosition();

    robot.forkCenter().waitPositionReached();



    robot.forkCenter().goLowPosition();
    robot.forkCenter().waitPositionReached();

    logger().info() << "L&R to HIGH" << utils::end;
     robot.forkLeft().goHighPosition();
    robot.forkRight().goHighPosition();
    usleep(50*1000);
    robot.turnForkLeft().goHighPosition();
    robot.turnForkRight().goHighPosition();
   
    sleep(1);
   logger().info() << "L&R to LOW" << utils::end;
    // Tout a LOW
   
     
    robot.turnForkLeft().goLowPosition();
    robot.turnForkRight().goLowPosition();
  
   usleep(50*1000);
    robot.forkLeft().goLowPosition();
    robot.forkRight().goLowPosition();
  


    logger().info() << "End Initialize mechanical." << utils::end;*/
    logger().info() << "Initialize color..." << utils::end;

    //prise en compte de la couleur de match
    robot.colorContact().wait();
    for (int i = 0; i < 8; i++)
    {
        robot.ledBar().setOn(i);
        usleep(100000);
    }
    //robot.ledBar().blink(10, 100000);
    //sleep(1);

    pmx::LedIndicator::instance().reset();
    if (robot.colorContact().state())
    {
        robot.myColorIs(pmx::PMXRED);
        logger().info() << "COLOR : RED " << pmx::PMXRED << utils::end;
        pmx::LedIndicator::instance().setOn(0);
        pmx::LedIndicator::instance().setOn(1);
        pmx::LedIndicator::instance().setOn(2);
        pmx::LedIndicator::instance().setOn(3);
    }
    else
    {
        robot.myColorIs(pmx::PMXPURPLE);
        logger().info() << "COLOR : PURPLE " << pmx::PMXPURPLE << utils::end;
        pmx::LedIndicator::instance().setOn(4);
        pmx::LedIndicator::instance().setOn(5);
        pmx::LedIndicator::instance().setOn(6);
        pmx::LedIndicator::instance().setOn(7);
    }


    logger().debug() << "color:" << robot.myColor() << utils::end;

    robot.ledBar().reset();

    robot.colorContact().stop(true);
    robot.ledBar().stop(true);
    robot.ledBar().reset();

    logger().info() << "End Initialize color." << utils::end;

    if (error) //TODO  Ne sert pas ?  et sinon fermer les actions
    {
        return this->getState("waitForReboot");
    }
    else
    {


        logger().info() << "=> Clic RESET..." << utils::end;
        robot.ledBar().k2Mil(50000);
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

        return this->getState("next");
    }
}
