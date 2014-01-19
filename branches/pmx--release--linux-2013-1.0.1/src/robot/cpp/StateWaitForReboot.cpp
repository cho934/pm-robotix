/*!
 * \file
 * \brief Implémentation de la classe StateWaitForReboot.
 */

#include <cmath>
#include <cstdlib>
#include <linux/limits.h>
#include "StateWaitForReboot.hpp"
#include "Robot.hpp"

pmx::IAutomateState*
pmx::StateWaitForReboot::execute(Robot& robot, void *)
{
    logger().info() << "Start" << utils::end;

    //arret des moteurs
    robot.base().motorLeft().applyMotorCode(0);
    robot.base().motorRight().applyMotorCode(0);
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
        printf("StateWaitForReboot EXIT\n");
        exit(60);
    }

    logger().info() << "=> Clic RESET..." << utils::end;
    robot.ledBar().startK2Mil(50000, 50000, false);
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

    return this->getState("next");
}
