/*!
 * \file
 * \brief Implémentation de la classe Robot.
 */

#include <iostream>
#include "Robot.hpp"
#include "RobotInOutFactory.hpp"
#include "LedIndicator.hpp"
#include "Md25.hpp"

pmx::Robot::Robot():
        base_(*this),
        myColor_(pmx::PMXNOCOLOR),
        startContact_(*this, pmx::IRobotIn::M1, pmx::IRobotIn::PIN0),
        rebootContact_(*this, pmx::IRobotIn::M1, pmx::IRobotIn::PIN1),
        colorContact_(*this, pmx::IRobotIn::M1, pmx::IRobotIn::PIN2),
        leftBackContact_(*this, pmx::IRobotIn::M1, pmx::IRobotIn::PIN5),
        rightBackContact_(*this, pmx::IRobotIn::M1, pmx::IRobotIn::PIN4),
        ledBar_(*this, pmx::IRobotOut::DM3),
        forkCenter_(*this, 0),
        forkRight_(*this, 1),
        forkLeft_(*this, 2),
        turnForkRight_(*this, 3),
        turnForkLeft_(*this, 4),
        opponentIrSensorLeft_(*this, pmx::IRobotOut::PIN0, 30),
        opponentIrSensorRight_(*this, pmx::IRobotOut::PIN1, 30),
        opponentIrSensorCenter_(*this, pmx::IRobotOut::PIN2, 150)

        //! \todo anciens elements : Comment garder une trace des élements de robot ?
        /*
        pawnLeftIrSensor_(*this, pmx::IRobotOut::PIN0, 30),
        pawnRightIrSensor_(*this, pmx::IRobotOut::PIN6, 30),

        elevator_(*this, pmx::IRobotOut::DM7, pmx::IRobotOut::PIN0, pmx::IRobotOut::PIN1),
        opponent_(*this, pmx::IRobotIn::M4, pmx::IRobotIn::PIN7, pmx::IRobotIn::PIN6, pmx::IRobotIn::PIN5, pmx::IRobotIn::PIN4),
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
    pmx::LedIndicator::instance().blink(4, 50000);
    
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
    this->forkCenter_.initialize("forkCenter", configuration);
    this->forkLeft_.initialize("forkLeft", configuration);
    this->forkRight_.initialize("forkRight", configuration);
    this->turnForkLeft_.initialize("turnForkLeft", configuration);
    this->turnForkRight_.initialize("turnForkRight", configuration);

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
    logger().debug("Robot is started");
    //Ajouter ici les actions des composantes externes au démarrage

    //! \todo Comment garder une trace des élements de robot ? composants à ajouter dans une fonction spécifique addActionListener ?

    //addListener(new pmx::IrSensorListener(pawnLeftIrSensor())); //par defaut active=false 
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

    //demarre les threads odométrie et SPM
    this->base_.startListener();

    bool ret = true;

    printf(" Thread actionManager_ Start \n");
    ret = actionManager_.start();
    //affichage LEDINDICATOR
    if(ret == false)
    {
        pmx::LedIndicator::instance().setOn(2);
    }else
    {
        pmx::LedIndicator::instance().setOff(2);
    }
    logger().debug("actionManager_ is started");

    ret = true;
    printf(" Thread sensorManager_ Start \n");
    ret = sensorManager_.start();
    //affichage LEDINDICATOR
    if(ret == false)
    {
        pmx::LedIndicator::instance().setOn(3);
    }else
    {
        pmx::LedIndicator::instance().setOff(3);
    }
    logger().debug("sensorManager_ is started");


    //init du sens de marche en FORWARD par defaut
    this->base_.orderWay(pmx::BFORWARD);
    logger().debug() << "application du sens de marche:FORWARD" << utils::end;


    this->opponentIrSensorLeft().startTimer();
    usleep(2000);
    this->opponentIrSensorRight().startTimer();
    usleep(2000);
    this->opponentIrSensorCenter().startTimer();

    

    //test de la valeur de batterie de motorisation => ARRET du ROBOT
    float bat = utils::Md25::instance().getBatteryVolts();
    if (bat < 10.9) //11 Volts
    {
        logger().error() << " !! RECHARGE BATTERIE NECESSAIRE !! (" << bat << " volts)" << utils::end;
        this->ledBar_.k2Mil(100000);
        pmx::LedIndicator::instance().blink(10, 500000);
        this->ledBar_.reset();
        this->stop();
    }
    else
    {
        logger().info() << "MD25:Batterie de motorisation : " << bat << " volts : Robot is started..." << utils::end;

        //config I2C par défaut sur la carte MD25 de motorisation
        utils::Md25::instance().setMode(MD25_MODE_1);
        utils::Md25::instance().setAccelerationRate(10);
        utils::Md25::instance().setCommand(MD25_ENABLE_SPEED_REGULATION);
        utils::Md25::instance().setCommand(MD25_RESET_ENCODERS);

        int soft = utils::Md25::instance().getSoftwareVersion();

        long countLeftMd25 = utils::Md25::instance().ensureGetEncoder(countLeftMd25, MD25_ENCODER1_REG);
        long countRightMd25 = utils::Md25::instance().ensureGetEncoder(countRightMd25, MD25_ENCODER2_REG);

        logger().info() << "MD25:soft : " << soft
                << " Left : " << countLeftMd25
                << " Right: " << countRightMd25
                << utils::end;
    }

    
    
    //reset ledBar
    this->ledBar_.reset();
}

void
pmx::Robot::stop()
{
    logger().info("Stop");
    this->base().stop();
    this->base().pidSpeedStop();
    logger().debug("Base is stopped");

    
    logger().debug("Stop LED");
    //desactive les objets du robot pour supprimer les actions en cours
    this->ledBar_.stop(true);
 logger().debug("Stop contact Listeners");
    this->startContact_.stop(true);
    this->rebootContact_.stop(true);
    this->colorContact_.stop(true);
    this->leftBackContact_.stop(true);
    this->rightBackContact_.stop(true);
    
 logger().debug("Stop IR Listeners");
    this->opponentIrSensorLeft().stopListener(true);
    this->opponentIrSensorRight().stopListener(true);
    this->opponentIrSensorCenter().stopListener(true);
logger().debug("Stop IR");

    this->opponentIrSensorLeft().stopTimer();
    this->opponentIrSensorRight().stopTimer();
    this->opponentIrSensorCenter().stopTimer();
     
    logger().debug("Stop managers");
    actionManager_.stop();
    sensorManager_.stop();
    
    logger().debug("Wait For actionManager and sensorManager");
    while (! (actionManager_.finished() && sensorManager_.finished()))
    {
        logger().debug() << "nb actions :" << actionManager_.count() << utils::end;
        usleep(20000);//on laisse faire les autres threads
    }
    
    logger().info("Robot Blink");
    pmx::LedIndicator::instance().blink(6, 50000);
    logger().info("Robot is stopped");
}


void pmx::Robot::goTo(double  x, double  y){
    base().arrivedDestination(false);
    bool stopped=false;
    bool opponentDetected=false;
    while(!base().arrivedDestination())
    {
        logger().debug() << "while(!base().arrivedDestination()) " << utils::end;
        opponentDetected =  base().movexy(x, y, pmx::BFORWARD, true);
        if(opponentDetected == true)
        {
            logger().info() << " !! opponentDetected " << chronometerRobot().getElapsedTimeInSec() << utils::end;
               stopped=true;
               sleep(2);
        }else if(stopped){
            logger().info() << " opponent is now out, let's continue "<< utils::end;
            stopped=false;
        }

        usleep(5000);
    }
}

void pmx::Robot::goToTeta(double  x,double  y, BaseWay way, double teta)
{
    base().arrivedDestination(false);
    bool stopped=false;
    bool opponentDetected=false;
    while(!base().arrivedDestination())
    {

        opponentDetected =  base().movexyTeta(x, y, way, teta, true);
        if(opponentDetected == true)
        {
            logger().info() << " !! opponentDetected " << chronometerRobot().getElapsedTimeInSec() << utils::end;
               stopped=true;
               sleep(3);
        }else if(stopped){
            logger().info() << " opponent is now out, let's continue "<< utils::end;
            stopped=false;
        }

        usleep(5000);
    }
}
