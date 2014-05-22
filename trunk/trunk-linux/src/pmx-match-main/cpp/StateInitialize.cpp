/*!
 * \file
 * \brief Implémentation de la classe StateInitialize.
 */

#include "StateInitialize.hpp"

#include "../../common/cpp/LedBar.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"


pmx::IAutomateState*
pmx::StateInitialize::execute(Robot& robot, void *)
{
    this->logger().info() << "start" << utils::end;
    bool error = false;

    //actions d'initialisation
    logger().info() << "Initialize mechanical..." << utils::end;


    logger().info() << "End Initialize mechanical." << utils::end;


    logger().info() << "Initialize color..." << utils::end;

    //prise en compte de la couleur de match
    /*
    robot.colorContact().wait();
    for (int i = 0; i < 8; i++)
    {
        robot.ledBar().setOn(i);
        usleep(100000);
    }

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
        robot.myColorIs(pmx::PMXBLUE);
        logger().info() << "COLOR : BLUE " << pmx::PMXBLUE << utils::end;
        pmx::LedIndicator::instance().setOn(4);
        pmx::LedIndicator::instance().setOn(5);
        pmx::LedIndicator::instance().setOn(6);
        pmx::LedIndicator::instance().setOn(7);
    }
*/

    logger().debug() << "color:" << robot.myColor() << utils::end;

    logger().info() << "End Initialize color." << utils::end;

    robot.ledBar().startReset();
    robot.ledBar().stop(true);

    if (error) 
    {
    	//error and reboot
        return this->getState("waitForReboot");
    }
    else
    {


        logger().info() << "=> Clic RESET..." << utils::end;
        robot.ledBar().startK2Mil(50000, 50000, false);
        /*
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
        robot.ledBar().stopAndWait(true);
        robot.ledBar().reset();
*/
        return this->getState("next");
    }
}
