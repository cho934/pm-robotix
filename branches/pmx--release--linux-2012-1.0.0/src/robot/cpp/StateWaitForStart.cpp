/*!
 * \file
 * \brief Implémentation de la classe StateWaitForStart.
 */

#include "StateWaitForStart.hpp"
#include "Robot.hpp"
#include "Wait90SecondsAction.hpp"
#include "LedIndicator.hpp"

pmx::IAutomateState*
pmx::StateWaitForStart::execute(Robot& robot, void *)
{
    logger().info() << "start" << utils::end;

    robot.firePulseEnabled(false);

    robot.startContact().wait();
    robot.rebootContact().wait();
    robot.leftBackContact().wait();
    robot.rightBackContact().wait();
    //attente de la prise en compte des états des contacts.
    usleep(50000);

    pmx::LedIndicator::instance().blink(5, 50000);

    robot.ledBar().k2Mil(50000);
    pmx::LedIndicator::instance().reset();

    logger().info() << "=> Tirer sur la ficelle !" << utils::end;

    //attente de l'appui enfoncé du reboot ou du tirage du fil de départ.
    while(robot.startContact().state() && !robot.rebootContact().state())
    {
        usleep(10000);
        //test des contacts arrières
        if(robot.leftBackContact().state())
        {
            pmx::LedIndicator::instance().setOn(0);
        }else
        {
            pmx::LedIndicator::instance().setOff(0);
        }
        if(robot.rightBackContact().state())
        {
            pmx::LedIndicator::instance().setOn(7);
        }else
        {
            pmx::LedIndicator::instance().setOff(7);
        }
    }

    //lecture du contact reboot
    bool reboot = robot.rebootContact().state();

    IAutomateState* result = NULL;
    if (reboot)
    {
        logger().info() << "REBOOT forced (clic reset)" << utils::end;
        //attente du relachement du reboot
        while(robot.rebootContact().state())
        {
            usleep(10000);
        }

        //retour à l'initialisation
        result = this->getState("rebootInitialize");
    }
    else
    {
        logger().info() << "Start Chronometer" << utils::end;
        //démarrage du chrono
        robot.chronometerRobot().start();

        printf(" Thread Wait90SecondsAction Start. \n");
        //lancement de l'etape Wait90Seconds
        pmx::Wait90SecondsAction* action = new pmx::Wait90SecondsAction(&robot);
        logger().info() << "debug 1" << utils::end;
        action->start();

        logger().info() << "debug 2" << utils::end;

        //Prog de decision
        result = this->getState("decisionMaker");

        logger().info() << "Attente du Robot lego....." << utils::end;
        //pause pour laisser partir le robot secondaire
        pmx::LedIndicator::instance().blink(6, 600000); 
        
    }
    
    robot.startContact().stop(true);
    robot.rebootContact().stop(true);
    robot.colorContact().stop(true);
    robot.leftBackContact().stop(true);
    robot.rightBackContact().stop(true);

    robot.ledBar().stop(true);
    robot.ledBar().reset();
    pmx::LedIndicator::instance().reset();

    return result;
}