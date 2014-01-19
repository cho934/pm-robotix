/*!
 * \file
 * \brief Implémentation de la classe StateWaitForReboot.
 */

#include "StateWaitForReboot.hpp"
#include "StateWaitForStart.hpp"
#include "StateInitialize.hpp"
#include "HstateMoveToPawn.hpp"
#include "Robot.hpp"
#include <math.h>

pmx::IAutomateState*
pmx::automate::StateWaitForReboot::execute(Robot& robot)
{
    logger().info() << "start" << utils::end;

    //arret des moteurs
    robot.base().motorLeft().applyMotorCode(0);
    robot.base().motorRight().applyMotorCode(0);
    
/*
    //initialisation des valeurs
    robot.base().reset();
    robot.position().x(0);
    robot.position().y(0, robot.myColor());
    robot.position().angle(M_PI_2, robot.myColor());
*/

    robot.base().pidSpeedDesactivate();

    char currentPath[PATH_MAX];
    getcwd(currentPath, PATH_MAX);
   
    try
    {
        robot.configure("robot_pmx.conf");
        logger().info() << "Current directory:" << currentPath << " : Configuration 'robot_pmx.conf' loaded." << utils::end;
    }
    catch (utils::ConfigurationException* exception)
    {
        logger().error() << "Error in the configuration file" << utils::end;
        logger().error() << "Message: " << exception->what() << utils::end;
        std::cerr << "Error !! " << exception->what() << std::endl;

        robot.stop();
        exit(0);
    }

    if(robot.modeZap() == 1)
    {
        return new pmx::automate::StateInitialize();
    }

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

    return new pmx::automate::StateInitialize();
}
