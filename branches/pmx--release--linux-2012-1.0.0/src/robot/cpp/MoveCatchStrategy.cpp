/*!
 * \file
 * \brief Implémentation de la classe CatchStrategy.
 */

#include "MoveCatchStrategy.hpp"
#include "Robot.hpp"
#include "Data.hpp"
#include "Contract.hpp"

int
pmx::MoveCatchStrategy::computeInterest(const pmx::Robot &, void * data)
{
    utils::Contract::isNotNull(data, "pmx::MoveCatchStrategy::computeInterest - data is null");

    int val;
    logger().info() << "computeInterest:start" << utils::end;

    pmx::Data* sharedData = (pmx::Data*) data;
    if (sharedData->isEmpty())
    {
        // Le robot est vide : aller attraper des CD peut rapporter 3 points
        val = 3;
    }
    else
    {
        // Le robot est plein - il ne peut/doit pas attraper des CDs.
        val = -1;
    }
    if (sharedData->strategyCatchWithOpponent())
    {
        val = 0;
    }

    return val;
}

pmx::IAutomateState*
pmx::MoveCatchStrategy::execute(pmx::Robot & robot, void * data)
{
    logger().info() << "start" << utils::end;
    pmx::Data* sharedData = (pmx::Data*) data;

    logger().debug() << "Color=" << robot.myColor()
            << utils::end;
    
    robot.base().pidSpeedEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidPositionEnabled(true);


    robot.base().vecteurCorrectionEnabled(false); //TODO!!!!!

    // Ouverture des pinces
     openFork(robot);

    //debut avance
    robot.base().pidSpeedActivate();
    robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID
    robot.firePulseEnabled(false);
    bool opponentDetected = false;

    logger().info() << "x=" << robot.position().x()
            << " y=" << robot.position().y()
            << " a=" << robot.position().angle()
            << utils::end;

    int xDevantCD= 100+130;//700
    int yDevantCD= 250 ; // 1000

    
    opponentDetected = robot.base().movexy(xDevantCD, yDevantCD, pmx::BFORWARD, false);

     // Ouverture des pinces
     closeFork(robot);



   
    //fin avance
    robot.base().pidSpeedStop();
    robot.firePulseEnabled(false);


    logger().info() << " Prise CD " << utils::end;
    //prendre cd
   
    sleep(1); //todo sleep a supprimer

    



    //modification des informations
    sharedData->isEmpty(false);

    this->logger().info() << "move ok" << utils::end;

    
    return this->getState("decisionMaker");
}

void pmx::MoveCatchStrategy::openFork(pmx::Robot & robot){

    // Ecartement des pinces
    robot.turnForkLeft().goLowPosition();
    robot.turnForkRight().goLowPosition();

    while(robot.turnForkLeft().state() == 0)
    {
        usleep(10000);
    }  
    while(robot.turnForkRight().state() == 0)
    {
        usleep(10000);
    }

    sleep(1);

    // Abaissement des pinces
    robot.forkLeft().goLowPosition();
    robot.forkRight().goLowPosition();
    robot.forkCenter().goLowPosition();
    while(robot.forkLeft().state() == 0)
    {
        usleep(10000);
    } 
    while(robot.forkRight().state() == 0)
    {
        usleep(10000);
    }

    // Milieu
    
    while(robot.forkCenter().state() == 0)
    {
        usleep(10000);
    }

    sleep(1);
}
void pmx::MoveCatchStrategy::closeFork(pmx::Robot & robot){

    // Abaissement des pinces
    robot.forkLeft().goHighPosition();
    robot.forkRight().goHighPosition();
    robot.forkCenter().goHighPosition();
    while(robot.forkLeft().state() == 0)
    {
        usleep(10000);
    }
    while(robot.forkRight().state() == 0)
    {
        usleep(10000);
    }
     while(robot.forkCenter().state() == 0)
    {
        usleep(10000);
    }
    usleep(500*1000);
    // Ecartement des pinces
    robot.turnForkLeft().goHighPosition();
    robot.turnForkRight().goHighPosition();

    while(robot.turnForkLeft().state() == 0)
    {
        usleep(10000);
    }
    while(robot.turnForkRight().state() == 0)
    {
        usleep(10000);
    }

    sleep(1);



  
}
