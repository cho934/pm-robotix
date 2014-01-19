/*!
 * \File
 * \brief Implémentation de la classe MoveReleaseStrategy.
 */

#include "MoveReleaseStrategy.hpp"
#include "Robot.hpp"
#include "Data.hpp"
#include "Contract.hpp"

int
pmx::MoveReleaseStrategy::computeInterest(const pmx::Robot &, void * data)
{
    utils::Contract::isNotNull(data, "pmx::MoveReleaseStrategy::computeInterest - data is null");

    logger().info() << "computeInterest:start" << utils::end;

    pmx::Data* sharedData = (pmx::Data*) data;
    if (sharedData->isEmpty())
    {
        // Le robot est vide - il ne peut/doit pas attraper des CDs.
        return -1;
    }
    else
    {
        // Le robot est plein : aller déposer des CD peut rapporter 3 points.
        return 3;
    }
    
}

pmx::IAutomateState*
pmx::MoveReleaseStrategy::execute(pmx::Robot & robot, void * data)
{
    logger().info() << "start" << utils::end;
    pmx::Data* sharedData = (pmx::Data*) data;

    logger().debug() << "Color=" << robot.myColor()
            << utils::end;

    //debut avance
    robot.base().pidSpeedActivate();
    robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID
    robot.firePulseEnabled(false);
    bool opponentDetected = false;
    this->logger().info() << "move to 500, 250" << utils::end;
    opponentDetected = robot.base().movexy(500, 250, pmx::BFORWARD, false);
    if(opponentDetected == true)
    {
        logger().info() << " !! opponentDetected " << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
        sharedData->strategyCatchWithOpponent(true);
    }
    this->logger().info() << "move to 300, 250" << utils::end;
    opponentDetected = robot.base().movexy(300, 250, pmx::BFORWARD, false);
    if(opponentDetected == true)
    {
        logger().info() << " !! opponentDetected " << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
        sharedData->strategyCatchWithOpponent(true);
    }
    //fin avance
    robot.base().pidSpeedStop();
    robot.firePulseEnabled(false);


    //lacher cd
    robot.forkCenter().goLowPosition();
    while(robot.forkCenter().state() == 1)
    {
        usleep(10000);
    }
    sleep(1);

    //debut avance
    robot.base().pidSpeedActivate();
    robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID
    robot.firePulseEnabled(false);
    this->logger().info() << "move to 500, 250 BBACK false" << utils::end;
    opponentDetected = robot.base().movexy(500, 250, pmx::BBACK, false);
    //fin avance
    robot.base().pidSpeedStop();
    robot.firePulseEnabled(false);



    sharedData->isEmpty(true);


    logger().info() << "  END" << utils::end;

    //return this->getState("decisionMaker");
    return NULL; //fin du programme
}
