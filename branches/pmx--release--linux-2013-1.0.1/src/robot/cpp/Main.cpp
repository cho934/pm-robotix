/*!
 * \file
 * \brief Ce fichier contient la méthode main() pour le programme principal.
 */

#include <iostream>
#include <cmath>
#include <dirent.h>
#include <stdlib.h>
#include "Robot.hpp"
#include "LoggerFactory.hpp"
#include "Macro.hpp"
#include "StateWaitForReboot.hpp"
#include "StateInitialize.hpp"
#include "StateWaitForStart.hpp"
#include "StateDecisionMaker.hpp"
#include "StateAdjustRobotPosition.hpp"
#include "Automate.hpp"
#include "Data.hpp"
#include "StrategyLaunchBalls.hpp"
#include "StrategyLaunchOpponentBalls.hpp"
#include "StrategyPushGlasses.hpp"
#include "StrategySwallowBalls.hpp"

using namespace pmx;

/*!
 * \brief Méthode principale pour le lancement du robot.
 *
 * \return Code de retour du programme.
 */
int main(int argc, char** argv) {
    const utils::Logger& logger = utils::LoggerFactory::logger("main");

    Robot robot;
    robot.firePulseEnabled(false); //pour ne pas prendre en compte les impulsions des codeurs.

    int mode = 0;
    //prise en compte des arguments
    if (argc < 2) {
        logger.info() << "USAGE: PMX [1=Homologation] [0=Matches] [Default=Homologation]" << utils::end;
    }
    if (argc > 1) {
        mode = atoi(argv[1]);
        if (mode == 1) {
            robot.runMode(pmx::ROBOTHOMOLOGATION);
            logger.info() << "MODE HOMOLOGATION" << utils::end;
        }else if (mode == 0) {
            robot.runMode(pmx::ROBOTMATCHES);
            logger.info() << "MODE MATCHES" << utils::end;
        }

    }else {
        robot.runMode(pmx::ROBOTHOMOLOGATION);
        logger.info() << "Default:MODE HOMOLOGATION" << utils::end;
    }

    logger.info() << "Start of PMX, the robot..." << utils::end;
    robot.start();

    robot.base().pidSpeedEnabled(false);
    robot.base().pidPositionEnabled(true);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidSpeedDesactivate();
    robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID

    IAutomateState* waitForReboot = new pmx::StateWaitForReboot();
    IAutomateState* initialize = new pmx::StateInitialize();
    IAutomateState* ajustRobotPosition = new pmx::StateAdjustRobotPosition();
    IAutomateState* waitForStart = new pmx::StateWaitForStart();
    pmx::StateDecisionMaker* decisionMaker = new pmx::StateDecisionMaker();

    waitForReboot->addState("next", initialize);
    initialize->addState("next", ajustRobotPosition);
    initialize->addState("waitForReboot", waitForReboot);
    ajustRobotPosition->addState("next", waitForStart);

    waitForStart->addState("decisionMaker", decisionMaker);
    waitForStart->addState("rebootInitialize", initialize);


    //Ajout des stratégies
    if (robot.myRunningMode() == pmx::ROBOTMATCHES) {
        logger.info() << "ROBOTMATCHES" << utils::end;

    }else {
        logger.info() << "ROBOTHOMOLOGATION" << utils::end;
        decisionMaker->addStrategy(new pmx::StrategyPushGlasses(decisionMaker));
    }

    // Create the data used to run the automate
    Data *data = new Data();
    //data->strategyPushGoldBar(false);
    //data->strategyCatchWithOpponent(false);
    data->isEmpty(true);

    // Start the automate and wait for its return
    Automate *automate = new Automate();
    automate->run(robot, waitForReboot, data);

    logger.info() << "robot.stop();" << utils::end;
    robot.stop();
    logger.info() << "Position :" << robot.position().x() << " " << robot.position().y() << " " << (robot.position().angle()*180) / M_PI << utils::end;
    logger.info() << "PMX - Happy End" << utils::end;
    return 99;
}
