/*!
 * \file
 * \brief Implémentation de la classe Robot.
 */

#include "Robot.hpp"
#include "RobotInOutFactory.hpp"
#include "MovementAction.hpp"
#include "Automate.hpp"

pmx::Robot::Robot():
        base_(*this),
        startContact_(*this, pmx::IRobotIn::M0, pmx::IRobotIn::PIN0),
        rebootContact_(*this, pmx::IRobotIn::M0, pmx::IRobotIn::PIN1),
        frontDistanceOpponent_(*this, pmx::IRobotIn::M5, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN7),
        rightDistanceBorder_(*this, pmx::IRobotIn::M4, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN6),
        leftDistanceBorder_(*this, pmx::IRobotIn::M3, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN5),
        rightLever_(*this, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN2, 900, 2000, 15000),
        leftLever_(*this, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN1, 2000, 900, 15000),
        stepper_(*this, pmx::IRobotOut::DM2),
        shovel_(*this, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN3, 10000),
        rightPushElement_(*this, pmx::IRobotOut::DM0, pmx::IRobotOut::PIN0, 1000, 2000, 15000)      
{
    // Initialisation de la construction dans le thread principal.
    //! \todo supprimer cet appel en s'assurant qu'elle ne soit pas en conflit entre plusieurs
    pmx::RobotInOutFactory::instance();
    
    //ajout de la configuration des ServoMotor:
    shovel_.values().push_back(1000); //pushed
    shovel_.values().push_back(2000); //retired
}

void
pmx::Robot::initialize(const std::string&, utils::Configuration& configuration)
{
    this->base_.initialize("base", configuration);
    this->rightLever_.initialize("rightLever", configuration);
    this->leftLever_.initialize("leftLever", configuration);
    this->shovel_.initialize("shovel", configuration);
}

void
pmx::Robot::configure(const std::string & configurationFile)
{
    utils::Configuration configuration;
    configuration.load(configurationFile);
    
    this->initialize("robot", configuration);
}

void
pmx::Robot::start()
{
    logger().info("Robot is started");
    addAction(new pmx::DistanceDetectorAction(frontDistanceOpponent()));
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
    
    actionManager_.start();
    sensorManager_.start();
}

void
pmx::Robot::stop()
{
    logger().debug("Stop");
    this->base().stop();
    logger().debug("Base is stopped");
    
    logger().debug("Stop managers");
    actionManager_.stop();
    sensorManager_.stop();
    pthread_yield();
    logger().debug("Wait For actionManager and sensorManager");
    while (! (actionManager_.finished() && sensorManager_.finished()))
    {
        pthread_yield();
    }
    
    logger().info("Robot is stopped");
}

void
pmx::Robot::startAutomate(pmx::IAutomateState* first)
{
    Automate automate;
    automate.run(*this, first);
}
/*
pmx::MovementAction* 
pmx::Robot::moveTo(double x, double y)
{
    //this->addAction(new pmx::MovementAction(this, x, y));
    MovementAction* action = new pmx::MovementAction(this, x, y);
    this->addAction(action);
    return action;
}*/
