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

	int mode = 0;
	//prise en compte des arguments
	if (argc < 2)
	{
		logger.info() << "USAGE: PMX [1=Homologation] [0=Matches] [Default=Homologation]" << utils::end;
	}
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

	}
	else
	{
		robot.runMode(pmx::ROBOTHOMOLOGATION);
		logger.info() << "Default:MODE HOMOLOGATION" << utils::end;
	}

	logger.info() << "Start of PMX, the robot..." << utils::end;
	robot.start();

	IAutomateState* waitForReboot = new pmx::StateWaitForReboot();
	IAutomateState* initialize = new pmx::StateInitialize();
	IAutomateState* ajustRobotPosition = new pmx::StateAdjustRobotPosition();
	IAutomateState* waitForStart = new pmx::StateWaitForStart();
	//pmx::StateDecisionMaker* decisionMaker = new pmx::StateDecisionMaker();

	waitForReboot->addState("next", initialize);
	initialize->addState("next", ajustRobotPosition);
	initialize->addState("waitForReboot", waitForReboot);
	ajustRobotPosition->addState("next", waitForStart);

	waitForStart->addState("rebootInitialize", initialize);
	//waitForStart->addState("decisionMaker", decisionMaker);

	//Ajout des stratégies
	if (robot.myRunningMode() == pmx::ROBOTMATCHES)
	{
		logger.info() << "ROBOTMATCHES" << utils::end;
		//configure IA

	}
	else
	{
		logger.info() << "ROBOTHOMOLOGATION" << utils::end;
		//configure IA

	}

	// Create the data used to run the automate
	Data *data = new Data();
	data->isEmpty(true);

	// Start the automate and wait for its return
	Automate *automate = new Automate();
	automate->run(robot, waitForReboot, data);


	logger.info() << "robot.stop();" << utils::end;
	robot.stop();
	//logger.info() << "Position :" << robot.position().x() << " " << robot.position().y() << " " << (robot.position().angle()*180) / M_PI << utils::end;
	logger.info() << "PMX - Happy End" << utils::end;
	return 99;
}
