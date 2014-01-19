/*!
 * \file
 * \brief Implémentation de la classe StateWaitForStart.
 */

#include "StateWaitForStart.hpp"
#include "StateInitialize.hpp"
#include "HstateMoveToPawn.hpp"
#include "Robot.hpp"
#include "Wait90SecondsAction.hpp"
#include "LedIndicator.hpp"

pmx::IAutomateState*
pmx::automate::StateWaitForStart::execute(Robot& robot)
{
    logger().info() << "start" << utils::end;

    robot.firePulseEnabled(false);

    robot.startContact().wait();
    robot.rebootContact().wait();
    //attente de la prise en compte des états des contacts.
    usleep(50000);

    pmx::LedIndicator::instance().blink(20);
    robot.ledBar().k2Mil();  
    pmx::LedIndicator::instance().flash();

    logger().info() << "Tirer sur la ficelle !" << utils::end;

    //attente de l'appui enfoncé du reboot ou du tirage du fil de départ (startContact=.
    while(robot.startContact().state() && !robot.rebootContact().state())
    {
        usleep(10000);
    }

    //lecture du contact reboot
    bool reboot = robot.rebootContact().state();

    IAutomateState* result;
    if (reboot)
    {
        //attente du relachement du reboot
        while(robot.rebootContact().state())
        {
            usleep(10000);
        }

        //retour à l'initialisation
        result = new pmx::automate::StateInitialize();
    }
    else
    { 
        //démarrage du chrono
        robot.chronometerRobot().start();
        //lancement de l'etape Wait90Seconds
        pmx::Wait90SecondsAction* action = new pmx::Wait90SecondsAction(&robot);
        action->start();

        //Prog d'homologation
        result = new pmx::automate::HstateMoveToPawn();
    }
    
    robot.startContact().stop(true);
    robot.rebootContact().stop(true);
    robot.colorContact().stop(true);
    robot.leftBackContact().stop(true);
    robot.rightBackContact().stop(true);

    robot.ledBar().stop(true);
    robot.ledBar().reset();
    pmx::LedIndicator::instance().reset();

    

    if(robot.myRunningMode() == pmx::ROBOTHOMOLOGATION)
    {
        logger().info() << "ROBOT HOMOLOGATION" << utils::end;
        return new pmx::automate::HstateMoveToPawn();

    }else if(robot.myRunningMode() == pmx::ROBOTMATCHES)
    {
        logger().info() << "ROBOT MATCHES" << utils::end;
        //return new pmx::automate::StateQueenDetection();
    }

    return NULL;
}
