/*!
 * \file
 * \brief Implémentation de la classe Robot.
 */

#include <iostream>
#include "Robot.hpp"
#include "Exception.hpp"
#include "RobotInOutFactory.hpp"
#include "LedIndicator.hpp"
#include "Md25.hpp"

pmx::Robot::Robot() :
base_(*this),
irSensorsGroup_(*this),
myColor_(pmx::PMXNOCOLOR),
startContact_(*this, pmx::IRobotIn::M1, pmx::IRobotIn::PIN2),
rebootContact_(*this, pmx::IRobotIn::M1, pmx::IRobotIn::PIN1),
colorContact_(*this, pmx::IRobotIn::M1, pmx::IRobotIn::PIN0),
leftBackContact_(*this, pmx::IRobotIn::M1, pmx::IRobotIn::PIN5),
rightBackContact_(*this, pmx::IRobotIn::M1, pmx::IRobotIn::PIN4),
ledBar_(*this, pmx::IRobotOut::DM7),
servoColorSorting_(*this, 2),
servoBalloonInflate_(*this, 0),
clamp_(*this, 4, 1),
servoLevier_(*this, 6)

 {

    //reset des ledindicators de notification au démarrage
    pmx::LedIndicator::instance().blink(8, 50000);
    pmx::LedIndicator::instance().reset();

    //LED INDICATOR TEST INIT
    pmx::LedIndicator::instance().setOn(0);
    //pmx::LedIndicator::instance().setOn(7);


    // Initialisation de la construction dans le thread principal.
    //! \todo supprimer cet appel "pmx::RobotInOutFactory::instance"en s'assurant qu'elle ne soit pas en conflit entre plusieurs
    pmx::RobotInOutFactory::instance();

}

void
pmx::Robot::initialize(const std::string& prefix, utils::Configuration& configuration) {
    logger().debug() << "initialize: " << prefix << utils::end;
    //initialisation de la base roulante (PID)
    this->base_.initialize("base", configuration);

    //initialisation des autres composants au démarrage
    //this->clamp_.initialize("Clamp", configuration);
    this->servoColorSorting_.initialize("servoColorSorting", configuration);
    this->servoBalloonInflate_.initialize("servoBalloonInflate", configuration);
    this->servoLevier_.initialize("servoLevier", configuration);

}

void
pmx::Robot::configure(const std::string & configurationFile) {
    logger().debug() << "configure configurationFile=" << configurationFile << utils::end;

    utils::Configuration configuration;
    configuration.load(configurationFile);

    this->initialize("robot", configuration);
}

void
pmx::Robot::start() {
    logger().info("Robot is started");

    //demarre les threads odométrie et SPM
    this->base_.startListener();

    bool ret = true;
    printf(" Thread actionManager_ Start \n");
    ret = actionManager_.start();
    //LED INDICATOR TEST INIT
    pmx::LedIndicator::instance().blinkPin(3, 3, 70000);
    if (!ret) {
        pmx::LedIndicator::instance().setOn(3);
    }else {
        pmx::LedIndicator::instance().setOff(3);
    }
    logger().debug("actionManager_ is started");

    ret = true;
    printf(" Thread sensorManager_ Start \n");
    ret = sensorManager_.start();
    //LED INDICATOR TEST INIT
    pmx::LedIndicator::instance().blinkPin(4, 3, 70000);

    if (!ret) {
        pmx::LedIndicator::instance().setOn(4);
    }else {
        pmx::LedIndicator::instance().setOff(4);
    }
    logger().debug("sensorManager_ is started");


    //init du sens de marche en FORWARD par defaut
    this->base_.orderWay(pmx::BFORWARD);
    logger().debug() << "application du sens de marche:FORWARD" << utils::end;



    //test de la valeur de batterie de motorisation => ARRET du ROBOT
    float bat = 0;
    bat = utils::Md25::instance().getBatteryVolts();

    int i2cErrors = utils::Md25::instance().getNbErrors();
    logger().error() << " v=" << bat << " volts i2cErrors=" << i2cErrors << utils::end;
    if (i2cErrors > 0) {
        logger().error() << "CONNECTER LES MOTEURS !! v=" << bat << " volts i2cErrors=" << i2cErrors << utils::end;
        this->ledBar().reset();
        this->ledBar().startAlternate(24, 200000, 0xF0, 0x0F, false);
        pmx::LedIndicator::instance().alternate(24, 200000, 0xF0, 0x0F);
        //sleep(6);
        this->ledBar().stopAndWait(true);

        this->stop();
        exit(0);
    }

    if (bat < 10.9 && bat > 0) //11 Volts (Avec l'alim 220, on est à 10.8v avec les diodes, sinon 11.6v)
    {
        logger().error() << "RECHARGER LES BATTERIES !! v=" << bat << " volts" << utils::end;
        this->ledBar().reset();
        this->ledBar().startAlternate(24, 200000, 0xC3, 0x3C, false);
        pmx::LedIndicator::instance().alternate(24, 200000, 0xC3, 0x3C);
        //sleep(6);
        this->ledBar().stopAndWait(true);

        this->stop();
        exit(0);
    }else {
        logger().info() << "MD25:Batterie de motorisation : " << bat << " volts : Robot is started..." << utils::end;

        //config I2C par défaut sur la carte MD25 de motorisation
        utils::Md25::instance().setMode(MD25_MODE_0); // valeur de commande 0(full reverse)-128(stop)-255(full forward)
        utils::Md25::instance().setAccelerationRate(10);
        utils::Md25::instance().setCommand(MD25_ENABLE_SPEED_REGULATION);
        utils::Md25::instance().setCommand(MD25_RESET_ENCODERS);

        int soft = utils::Md25::instance().getSoftwareVersion();

        long countLeftMd25 = utils::Md25::instance().ensureGetEncoder(0, MD25_ENCODER1_REG);
        long countRightMd25 = utils::Md25::instance().ensureGetEncoder(0, MD25_ENCODER2_REG);

        logger().info() << "MD25:soft : " << soft
                << " Left : " << countLeftMd25
                << " Right: " << countRightMd25
                << utils::end;
    }



    //reset ledBar
    this->ledBar_.reset();
}

void
pmx::Robot::stop() {
    logger().info("Stop");

    this->stopDevices();

    this->stopManagers();

    logger().info("Robot is stopped");
    logger().info("Robot Blink");
    pmx::LedIndicator::instance().blink(60, 50000);

}

void
pmx::Robot::stopDevices() {
    this->base().stop();

    this->base().pidSpeedStop();
    this->base().stop();
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

    logger().debug("Stop IR Timer");
    this->irSensorsGroup().stopTimer();
}

void
pmx::Robot::stopManagers() {
    logger().debug("Stop managers");
    actionManager_.stop();
    sensorManager_.stop();

    logger().debug("Wait For actionManager and sensorManager");
    while (!(actionManager_.finished() && sensorManager_.finished())) {
        logger().debug() << "nb actions :" << actionManager_.count() << utils::end;
        usleep(20000); //on laisse faire les autres threads
    }
}

void pmx::Robot::goTo(double x, double y, BaseWay way, bool detection) {
    /*base().arrivedDestination(false);
    bool stopped = false;
    bool opponentDetected = false;
    while (!base().arrivedDestination()) {
        logger().debug() << "while(!base().arrivedDestination()) " << utils::end;
        opponentDetected = base().movexy(x, y, pmx::BFORWARD, true);
        if (opponentDetected == true) {
            logger().info() << " !! opponentDetected " << chronometerRobot().getElapsedTimeInSec() << utils::end;
            stopped = true;
            sleep(2);
        }else if (stopped) {
            logger().info() << " opponent is now out, let's continue " << utils::end;
            stopped = false;
        }

        usleep(5000);
    }*/

    if (detection == true) {
        irSensorsGroup().startTimer();
    }

    base().arrivedDestination(false);
    bool opponentDetected = false;

    while (base().arrivedDestination() == false) {
        opponentDetected = base().checkOpponent();
        if (!opponentDetected) {
            opponentDetected = base().movexy(x, y, way, detection);

            if (opponentDetected == true) {
                base().stop();
                logger().info() << " !! opponentDetected time=" << chronometerRobot().getElapsedTimeInSec() << utils::end;
            }
        }else {
            base().stop();
            logger().info() << " sleep" << utils::end;
            sleep(1);
        }
    }

    if (detection == true) {
        irSensorsGroup().stopTimer();
    }







}

void pmx::Robot::goToTeta(double x, double y, double teta, BaseWay way, bool detection) {
    /*base().arrivedDestination(false);
    bool stopped = false;
    bool opponentDetected = false;
    while (!base().arrivedDestination()) {

        opponentDetected = base().movexyTeta(x, y, way, teta, true);
        if (opponentDetected == true) {
            logger().info() << " !! opponentDetected " << chronometerRobot().getElapsedTimeInSec() << utils::end;
            stopped = true;
            sleep(3);
        }else if (stopped) {
            logger().info() << " opponent is now out, let's continue " << utils::end;
            stopped = false;
        }

        usleep(5000);
    }*/

     if (detection == true) {
        irSensorsGroup().startTimer();
    }

    base().arrivedDestination(false);
    bool opponentDetected = false;

    while (base().arrivedDestination() == false) {
        opponentDetected = base().checkOpponent();
        if (!opponentDetected) {
            opponentDetected = base().movexyTeta(x, y, way, teta, detection);

            if (opponentDetected == true) {
                base().stop();
                logger().info() << " !! opponentDetected time=" << chronometerRobot().getElapsedTimeInSec() << utils::end;
            }
        }else {
            base().stop();
            logger().info() << " sleep" << utils::end;
            sleep(1);
        }
    }

    if (detection == true) {
        irSensorsGroup().stopTimer();
    }

}
