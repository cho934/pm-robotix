/*!
 * \file
 * \brief Ce fichier contient la méthode main() pour le programme principal.
 */

//#include <dirent.h>
#include <stdlib.h>

#include "../../common/cpp/Automate.hpp"
#include "../../common/cpp/LedIndicator.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/LoggerFactory.hpp"
#include "../../common/cpp/Robot.hpp"
#include "Data.hpp"
#include "StateAdjustRobotPosition.hpp"
#include "StateInitialize.hpp"
#include "StateWaitForReboot.hpp"
#include "StateWaitForStart.hpp"
#include "StateIADecisionMaker.hpp"

using namespace pmx;

/*!
 * \brief Méthode principale pour le lancement du robot.
 *
 * \return Code de retour du programme.
 */
int main(int argc, char** argv)
{
	const utils::Logger& logger = utils::LoggerFactory::logger("main");

	pmx::Robot &robot = pmx::Robot::instance();

	pmx::LedIndicator::instance().reset();

	// Create the data used to run the automate
	Data *data = new Data();
	data->isEmpty(true);

	int mode = 0;
	//prise en compte des arguments

	logger.info()
			<< "USAGE: PMX  [0=Matches, 1=Homologation, 2=Tabletest, Default=Homologation] [1=Internal encoder] [1=don't setup]"
			<< utils::end;

	if (argc > 1)
	{
		mode = atoi(argv[1]);
		if (mode == 1)
		{
			robot.runMode(pmx::ROBOTHOMOLOGATION);
			logger.info() << "MODE HOMOLOGATION" << utils::end;
		}
		else if (mode == 0)
		{
			robot.runMode(pmx::ROBOTMATCHES);
			logger.info() << "MODE MATCHES" << utils::end;
		}
		else if (mode == 2)
		{
			robot.runMode(pmx::ROBOTTABLETEST);
			logger.info() << "MODE TABLETEST" << utils::end;
		}
	}
	else
	{
		//without parameters
		robot.runMode(pmx::ROBOTHOMOLOGATION);
		logger.info() << "Default:MODE HOMOLOGATION" << utils::end;
	}

	if (argc > 2)
	{
		data->useInternalEncoder(atoi(argv[2]));
		std::cout << "USE internal encoder : " << atoi(argv[2]) << std::endl;
		robot.start(0); //start Manager and asserv
	}
	else
	{
		data->useInternalEncoder(0);
		std::cout << "USE EXTERNAL ENCODER " << std::endl;
		robot.start(1); //start Manager and asserv
	}

	if (argc > 3)
	{
		data->skipSetup(atoi(argv[3]));
		std::cout << "skip setup: " << atoi(argv[3]) << ", COLOR is RED" << std::endl;
		robot.myColorIs(pmx::PMXRED);

	}
	else
	{
		data->skipSetup(0);
		std::cout << "FULL SETUP" << std::endl;
	}

	logger.info() << "Start of PMX, the robot..." << utils::end;


	IAutomateState* waitForReboot = new pmx::StateWaitForReboot();
	IAutomateState* initialize = new pmx::StateInitialize();
	IAutomateState* ajustRobotPosition = new pmx::StateAdjustRobotPosition();
	IAutomateState* waitForStart = new pmx::StateWaitForStart();
	pmx::StateIADecisionMaker* decisionMaker = new pmx::StateIADecisionMaker();

	waitForReboot->addState("next", initialize);
	initialize->addState("next", ajustRobotPosition);
	initialize->addState("waitForReboot", waitForReboot);
	ajustRobotPosition->addState("next", waitForStart);

	waitForStart->addState("rebootInitialize", initialize);
	waitForStart->addState("decisionMaker", decisionMaker);

	robot.lcdBoard().setBacklight(LCD_ON);
	robot.lcdBoard().clear();

	//Ajout des stratégies
	if (robot.myRunningMode() == pmx::ROBOTMATCHES)
	{
		logger.debug() << "ROBOTMATCHES" << utils::end;
		//configure IA
		decisionMaker->IASetupMatches();
		robot.lcdBoard().print("PMX MATCH GO !");
	}
	else if (robot.myRunningMode() == pmx::ROBOTHOMOLOGATION)
	{
		logger.debug() << "ROBOTHOMOLOGATION" << utils::end;
		//configure IA
		decisionMaker->IASetupHomologation();

		robot.lcdBoard().print("HOMOLOGATION GO !");
	}
	else if (robot.myRunningMode() == pmx::ROBOTTABLETEST)
	{
		logger.debug() << "ROBOTTABLETEST" << utils::end;
		//configure IA
		decisionMaker->IASetupTableTest();
		robot.lcdBoard().print("TABLE TEST GO !");
	}

	// Start the automate and wait for its return
	Automate *automate = new Automate();
	automate->run(robot, waitForReboot, data);

	robot.lcdBoard().setBacklight(LCD_OFF);

	logger.debug() << "robot.stop();" << utils::end;
	robot.stop();
	//logger.info() << "Position :" << robot.position().x() << " " << robot.position().y() << " " << (robot.position().angle()*180) / M_PI << utils::end;
	logger.info() << "PMX - Happy End" << utils::end;
	return 0;
}
