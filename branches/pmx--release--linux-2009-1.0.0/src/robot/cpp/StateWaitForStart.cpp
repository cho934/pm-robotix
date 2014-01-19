#include "StateWaitForStart.hpp"
#include "StateInitialize.hpp"
#include "StateMoveToDistributor.hpp"
#include "Robot.hpp"
#include "SimpleSensorListener.hpp"
#include "Wait90SecondsAction.hpp"

pmx::IAutomateState*
pmx::automate::StateWaitForStart::execute(Robot& robot)
{
    this->logger().info() << "start" << utils::end;
    pmx::SimpleSensorListener* startListener = new pmx::SimpleSensorListener(robot.startContact());
    pmx::SimpleSensorListener* rebootListener = new pmx::SimpleSensorListener(robot.rebootContact());
    robot.addListener(startListener);
    robot.addListener(rebootListener);
    
    //attente de la prise en compte des états des contacts.
    usleep(1000000);
    
    //attente de l'appui enfoncé du reboot ou du tirage du fil de départ
    while(startListener->state() && !rebootListener->state())
    {
        pthread_yield();
    }

    //lecture du contact reboot
    bool reboot = rebootListener->state();
    
    IAutomateState* result;
    if (reboot)
    {
        //attente du relachement du reboot
        while(rebootListener->state())
        {
            pthread_yield();
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
        
        //Move to distributor
        result = new pmx::automate::StateMoveToDistributor();
    }
    
    startListener->stop();
    rebootListener->stop();
    
    return result;
}
