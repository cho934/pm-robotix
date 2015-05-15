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
			<< "USAGE: PMX  [0=Matches, 1=Homologation, 2=Tabletest, Default=Homologation] [1=External encoder] [1=skip setup] [0=YELLOW;1=GREEN]"
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
		std::cout << " external encoder : " << atoi(argv[2]) << std::endl;
		robot.start(atoi(argv[2]), 1); //start Manager and asserv
	}
	else
	{
		std::cout << "USE EXTERNAL ENCODER " << std::endl;
		exit(0); //No external encoder
		robot.start(1, 1); //start Manager and asserv
	}




	//robot.base().setupPID_AD(730.0f, 0.0f, 0.0f, 108.0f, 0.0f, 0.0f );






	if (argc > 3)
	{
		data->skipSetup(atoi(argv[3]));
		//std::cout << "skip setup: " << atoi(argv[3]) << std::endl;
	}
	else
	{
		data->skipSetup(0);
		//std::cout << "FULL SETUP" << std::endl;
	}
	if (argc > 4)
	{
		int color = atoi(argv[4]);
		if (color == 0)
		{
			robot.myColorIs(pmx::PMXYELLOW);
			//std::cout << " COLOR is YELLOW" << std::endl;
		}
		else
		{
			robot.myColorIs(pmx::PMXGREEN);
			//std::cout << " COLOR is GREEN" << std::endl;
		}
	}
	else
	{
		robot.myColorIs(pmx::PMXYELLOW);
		//std::cout << " COLOR is YELLOW" << std::endl;
	}

	logger.debug() << "Start of PMX, the robot..." << utils::end;

	IAutomateState* waitForReboot = new pmx::StateWaitForReboot();
	IAutomateState* initialize = new pmx::StateInitialize();
	IAutomateState* ajustRobotPosition = new pmx::StateAdjustRobotPosition();
	IAutomateState* waitForStart = new pmx::StateWaitForStart();


	waitForReboot->addState("next", initialize);
	initialize->addState("next", ajustRobotPosition);
	initialize->addState("waitForReboot", waitForReboot);
	ajustRobotPosition->addState("next", waitForStart);

	waitForStart->addState("rebootInitialize", initialize);
	waitForStart->addState("decisionMaker", data->decisionMaker);

	robot.lcdBoard().setBacklight(LCD_ON);
	robot.lcdBoard().clear();


	// Start the automate and wait for its return
	Automate *automate = new Automate();
	automate->run(robot, waitForReboot, data);

	robot.lcdBoard().setBacklight(LCD_OFF);


	logger.info() << "PMX - Happy End" << utils::end;

	//logger.info() << "robot.stop();" << utils::end;
	//robot.stop();
	//logger.info() << "Position :" << robot.position().x() << " " << robot.position().y() << " " << (robot.position().angle()*180) / M_PI << utils::end;
	return 0;
}
