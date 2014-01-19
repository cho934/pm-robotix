/*!
 * \file
 * \brief Implémentation de la classe PushGoldBarStrategy.
 */

#include "PushGoldBarStrategy.hpp"
#include "Robot.hpp"
#include "Data.hpp"
#include "Contract.hpp"

int
pmx::PushGoldBarStrategy::computeInterest(const pmx::Robot &, void * data)
{
    utils::Contract::isNotNull(data, "pmx::PushGoldBarStrategy::computeInterest - data is null");

    pmx::Data* sharedData = (pmx::Data*) data;
    if (sharedData->strategyPushGoldBar() == true)
    {
        return -1;
    }
    else
    {
        return 3;
    }

   
}

pmx::IAutomateState*
pmx::PushGoldBarStrategy::execute(pmx::Robot & robot, void * data)
{
    logger().info() << "start" << utils::end;
    pmx::Data* sharedData = (pmx::Data*) data;

    robot.base().pidSpeedEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidPositionEnabled(true);


    robot.base().vecteurCorrectionEnabled(true); //TODO!!!!!


    //debut avance
    robot.base().pidSpeedActivate();
    robot.firePulseEnabled(false);
    bool opponentDetected = false;


    robot.base().arrivedDestination(false);
    bool stopped=false;
    while(!robot.base().arrivedDestination())
    {
        this->logger().info() << "move to 660, 250, pmx::BFORWARD, true" << utils::end;
        opponentDetected = robot.base().movexy(660.0, 250.0, pmx::BFORWARD, true);
        if(opponentDetected == true)
        {
            logger().info() << " !! opponentDetected " << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
            sharedData->strategyCatchWithOpponent(true);
            //sleep(3);
            stopped=true;
        }else if(stopped){
            logger().info() << " opponent is now out, let's continue "<< utils::end;
            stopped=false;
        }

        usleep(5000);
    }

    this->logger().info() << "supposed to be arrived at 660, 250 :" <<robot.base().arrivedDestination()<< utils::end;
    robot.base().arrivedDestination(false);
    while(!robot.base().arrivedDestination())
    {
        this->logger().info() << "move to 660, 790, pmx::BFORWARD, 0, true" << utils::end;
        opponentDetected = robot.base().movexyTeta(660.0, 790.0, pmx::BFORWARD, 0, true);
        if(opponentDetected == true)
        {
            logger().info() << " !! opponentDetected " << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
            sharedData->strategyCatchWithOpponent(true);
            sleep(2);
        }
        usleep(5000);
    }


    //Ecriture dans le SVG
    utils::SvgWriter::writePosition(robot.position().x(),
        robot.position().y(),
        robot.position().angle(), utils::SVG_POS_ROBOT);


    //recul pour pousser le robot
    robot.base().arrivedDestination(false);
    while(!robot.base().arrivedDestination())
    {
        this->logger().info() << "move to 280, 790, pmx::BBACK, false" << utils::end;
        opponentDetected = robot.base().movexy(280.0, 790.0, pmx::BBACK, false);
        if(opponentDetected == true)
        {
            logger().info() << " !! opponentDetected " << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
            sharedData->strategyCatchWithOpponent(true);
            sleep(2);
        }
        usleep(5000);
    }

    //Ecriture dans le SVG
    utils::SvgWriter::writePosition(robot.position().x(),
        robot.position().y(),
        robot.position().angle(), utils::SVG_POS_ROBOT);


    robot.base().arrivedDestination(false);
    while(!robot.base().arrivedDestination())
    {
        this->logger().info() << "move to 500, 1000, pmx::BFORWARD, true" << utils::end;
        opponentDetected = robot.base().movexy(500.0, 1000.0, pmx::BFORWARD, true);
        if(opponentDetected == true)
        {
            logger().info() << " !! opponentDetected " << robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
            sharedData->strategyCatchWithOpponent(true);
            sleep(2);
        }
        usleep(5000);
    }

    //Ecriture dans le SVG
    utils::SvgWriter::writePosition(robot.position().x(),
        robot.position().y(),
        robot.position().angle(), utils::SVG_POS_ROBOT);
    
    //fin avance
    //robot.base().pidSpeedStop();
    robot.firePulseEnabled(false);
    robot.base().pidSpeedDesactivate();
    sharedData->strategyPushGoldBar(true);

logger().debug() << " debug 10 " << utils::end;

    return this->getState("decisionMaker");
    //return NULL; //fin du programme
    
}

