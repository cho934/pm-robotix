/*!
 * \file
 * \brief Implémentation de la classe Robot.
 */

#include "Robot.hpp"
#include "RobotInOutFactory.hpp"
#include "Automate.hpp"
#include "LedIndicator.hpp"
#include <iostream>

pmx::Robot::Robot():
        base_(*this),
        myColor_(pmx::NOCOLOR),
        startContact_(*this, pmx::IRobotIn::M0, pmx::IRobotIn::PIN0),
        leftBackContact_(*this, pmx::IRobotIn::M0, pmx::IRobotIn::PIN2),
        rightBackContact_(*this, pmx::IRobotIn::M0, pmx::IRobotIn::PIN1),
        rebootContact_(*this, pmx::IRobotIn::M0, pmx::IRobotIn::PIN4),
        colorContact_(*this, pmx::IRobotIn::M0, pmx::IRobotIn::PIN3),
        pawnLeftIrSensor_(*this, pmx::IRobotOut::PIN0, 30),
        pawnRightIrSensor_(*this, pmx::IRobotOut::PIN6, 30),
        ledBar_(*this, pmx::IRobotOut::DM0),
        clamp_(*this),
        elevator_(*this, pmx::IRobotOut::DM7, pmx::IRobotOut::PIN0, pmx::IRobotOut::PIN1),
        opponent_(*this, pmx::IRobotIn::M4, pmx::IRobotIn::PIN7, pmx::IRobotIn::PIN6, pmx::IRobotIn::PIN5, pmx::IRobotIn::PIN4),
        opponentIrSensor_(*this, pmx::IRobotOut::PIN5, 150),
        modeZap_(0)


        /*,
        frontDistanceOpponent_(*this, pmx::IRobotIn::M5, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN7),
        rightDistanceBorder_(*this, pmx::IRobotIn::M4, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN6),
        leftDistanceBorder_(*this, pmx::IRobotIn::M3, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN5),
        rightLever_(*this, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN2, 900, 2000, 15000),
        leftLever_(*this, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN1, 2000, 900, 15000),
        stepper_(*this, pmx::IRobotOut::DM2),
        shovel_(*this, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN3, 10000),
        rightPushElement_(*this, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN0, 1000, 2000, 15000) */
{
    //reset des ledindicators de notification au démarrage
    pmx::LedIndicator::instance().blink(4);
    
    // Initialisation de la construction dans le thread principal.
    //! \todo supprimer cet appel "pmx::RobotInOutFactory::instance"en s'assurant qu'elle ne soit pas en conflit entre plusieurs
    pmx::RobotInOutFactory::instance();

    
    
}

void
pmx::Robot::initialize(const std::string& prefix, utils::Configuration& configuration)
{
    logger().debug() << "initialize: " << prefix << utils::end;
    //initialisation de la base roulante (PID)
    this->base_.initialize("base", configuration);

    //initialisation des autres composants au démarrage
    this->clamp_.initialize("clamp", configuration);

}

void
pmx::Robot::configure(const std::string & configurationFile)
{
    logger().debug("configure");
    utils::Configuration configuration;
    configuration.load(configurationFile);
    
    this->initialize("robot", configuration);
}

void
pmx::Robot::start()
{
    logger().info("Robot is started");
    //Ajouter ici les actions des composantes externes au démarrage

    //addListener(new pmx::IrSensorListener(pawnLeftIrSensor())); //par defaut active=false //!\todo !!composants à ajouter dans une fonction spécifique addActionListener





    /*addAction(new pmx::DistanceDetectorAction(frontDistanceOpponent()));
    addAction(new pmx::DistanceDetectorAction(rightDistanceBorder()));
    addAction(new pmx::DistanceDetectorAction(leftDistanceBorder()));
    addAction(new pmx::ColumnElementLeverAction(leftLever()));
    addAction(new pmx::ColumnElementLeverAction(rightLever()));
    //addAction(new pmx::StepperAction(stepper()));
    addAction(new pmx::ServoMotorAction(shovel()));
    addAction(new pmx::ColumnElementLeverAction(rightPushElement()));
    
    addListener(new pmx::DistanceDetectorListener(frontDistanceOpponent()));
    addListener(new pmx::DistanceDetectorListener(rightDistanceBorder()));
    addListener(new pmx::DistanceDetectorListener(leftDistanceBorder()));
    */

    //std::cout << "Thread::start: actionManager_" << std::endl;
    //std::cout << "Thread::start: sensorManager_" << std::endl;
    bool ret = true;
    ret = actionManager_.start();
    //affichage LEDINDICATOR
    if(ret == false)
    {
        pmx::LedIndicator::instance().setOn(2);
    }else
    {
        pmx::LedIndicator::instance().setOff(2);
    }
    logger().info("actionManager_ is started");

    ret = true;
    ret = sensorManager_.start();
    //affichage LEDINDICATOR
    if(ret == false)
    {
        pmx::LedIndicator::instance().setOn(3);
    }else
    {
        pmx::LedIndicator::instance().setOff(3);
    }
    logger().info("sensorManager_ is started");

    //! \todo optimisation : Gérer un seul thread pour tous les timers (créer un timerManager) afin d'éviter d'utiliser le noyau temps réel xenomai.

    //init du sens de marche en FORWARD par defaut
    this->base_.orderWay(pmx::BFORWARD);
    logger().debug() << "application du sens de marche:FORWARD" << utils::end;
    this->base_.motorLeft().applyWay(pmx::FORWARD);//application du sens de marche
    this->base_.motorRight().applyWay(pmx::FORWARD);

    //reset ledBar
    this->ledBar_.reset();
}

void
pmx::Robot::stop()
{
    logger().info("Stop");
    this->base().stop();
    logger().debug("Base is stopped");

    logger().debug("Stop elements Action and Listeners");
    //desactive les objets du robot pour supprimer les actions en cours
    this->ledBar_.stop(true);
    this->pawnLeftIrSensor_.stop(true);
    this->pawnRightIrSensor_.stop(true);
    this->startContact_.stop(true);
    this->rebootContact_.stop(true);
    this->colorContact_.stop(true);
    this->leftBackContact_.stop(true);
    this->rightBackContact_.stop(true);
    this->elevator_.stop(true);
    this->clamp_.stop(true);

    this->opponentIrSensor_.stop(true);

    this->elevator().noPosition();
    
    logger().debug("Stop managers");
    actionManager_.stop();
    sensorManager_.stop();
    
    logger().debug("Wait For actionManager and sensorManager");
    while (! (actionManager_.finished() && sensorManager_.finished()))
    {
        logger().debug() << "nb actions :" << actionManager_.count() << utils::end;
        usleep(20000);//on laisse faire les autres threads
    }
    
    logger().info("Robot is stopped");
    pmx::LedIndicator::instance().blink(6);
}

void
pmx::Robot::startAutomate(pmx::IAutomateState* first)
{
    Automate automate;
    automate.run(*this, first);
}
