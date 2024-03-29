/*
 * Robot.cpp
 * test
 *
 */

#include "Robot.hpp"

#include <math.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "../Log/Logger.hpp"
#include "AsservIa/ccbase.h"
#include "ConsoleManager.hpp"
#include "State/Automate.hpp"
#include "State/Data.hpp"
#include "State/StateAdjustRobotPosition.hpp"
#include "State/StateIADecisionMaker.hpp"
#include "State/StateInitialize.hpp"
#include "State/StateWaitForReboot.hpp"
#include "State/StateWaitForStart.hpp"

using namespace std;

Robot::Robot() :
		myColor_(PMXNOCOLOR)
{
	actions_default = new Actions();
	asserv_default = new Asserv();
}

void Robot::start(ConsoleManager manager, int argc, char** argv)
{
	string select;
	int skip = 0;
	int detect = 1;
	std::string strat = "FirstCarpet";//"FirstSteps";// "none";


	//if no argument, display the textmenu
	if (argc <= 1)
	{
		select = manager.displayMenuFirstArgu();

		//Add new argument to argv
		char *c = const_cast<char*>(select.c_str());
		char **newv = static_cast<char**>(malloc((argc + 2) * sizeof(*newv)));
		// Error check omitted
		memmove(newv, argv, sizeof(*newv) * argc);
		newv[argc] = c; //new added value
		newv[argc + 1] = 0;
		argc++;
		argv = newv;
	}

	//Case if first argument exists or if you choose one above.
	if (argv[1])
	{
		if (strcmp(argv[1], "U") == 0 || strcmp(argv[1], "u") == 0 || strcmp(argv[1], "-usage") == 0
				|| strcmp(argv[1], "-USAGE") == 0 || strcmp(argv[1], "help") == 0
				|| strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-h") == 0)
		{
			cout << "USAGE" << endl;
			cout << argv[0]
					<< " [M] [color:y/g] [skip setup:0/1] [detect:0/1] [IAStrategy:FirstCarpet/FirstSteps]" // [encoder:ext/int]
					<< endl;
			cout << argv[0] << " [T] [Test:Num[1-100] [params...]" << endl;
			exit(0);
		}

		//Case if matches/homologation.
		if (strcmp(argv[1], "M") == 0 || strcmp(argv[1], "m") == 0)
		{

			if (argc > 2)
			{
				if ((strcmp(argv[2], "y") == 0) || (strcmp(argv[2], "Y") == 0))
				{
					this->setMyColor(PMXYELLOW);
				}
				if ((strcmp(argv[2], "g") == 0) || (strcmp(argv[2], "G") == 0))
				{
					this->setMyColor(PMXGREEN);
				}

			}
			if (argc > 3)
			{
				skip = atoi(argv[3]);

			}

			if (argc > 4)
			{
				detect = atoi(argv[4]);
			}

			if (argc > 5)
			{

				if ((strcmp(argv[5], "FirstCarpet") == 0) || (strcmp(argv[5], "firstcarpet") == 0))
				{
					logger().info() << "Strategy FirstCarpet..." << logs::end;
					strat = "FirstCarpet";
				}
				else if ((strcmp(argv[5], "FirstSteps") == 0)
						|| (strcmp(argv[5], "firststeps") == 0))
				{
					logger().info() << "Strategy FirstSteps..." << logs::end;
					strat = "FirstSteps";
				}
				else
				{
					logger().error() << "ERROR Bad Strategy ..." << logs::end;
					exit(0);
				}

			}

			//init Automate for Match
			// Create the data used to run the automate
			Data *data = new Data();

			data->isEmpty(true);
			data->strategy(strat);
			data->skipSetup(skip);
			cc_setIgnoreFrontCollision(!detect);

			logger().info() << "Start of PMX, the robot..." << logs::end;

			IAutomateState* waitForReboot = new StateWaitForReboot();
			IAutomateState* initialize = new StateInitialize();
			IAutomateState* ajustRobotPosition = new StateAdjustRobotPosition();
			IAutomateState* waitForStart = new StateWaitForStart();

			waitForReboot->addState("next", initialize);
			initialize->addState("next", ajustRobotPosition);
			//initialize->addState("waitForReboot", waitForReboot);
			ajustRobotPosition->addState("next", waitForStart);
			//ajustRobotPosition->addState("waitForReboot2", waitForReboot);

			//waitForStart->addState("rebootInitialize", initialize);
			waitForStart->addState("decisionMaker", data->decisionMaker);

			// Start the automate and wait for its return
			Automate *automate = new Automate();
			automate->run(*this, waitForReboot, data);

			logger().info() << "PMX - Happy End" << logs::end;
		}
		//Case to display or run a functional test.
		else if (strcmp(argv[1], "T") == 0 || strcmp(argv[1], "t") == 0)
		{
			if (argc == 2) // Case with 'T' argument to choose a Functional test.
			{
				manager.displayMenuFunctionalTestsAndRun(argv[1]);
			}
			else // Case with 'T' and all arguments according to the selected Functional test.
			{
				manager.run(atoi(argv[2]), argc, argv);
			}
		}
		else
		{
			logger().error() << "Command " << argv[1] << " not found !" << logs::end;
			//cout << "Command " << argv[1] << " not found !" << endl;
		}
	}
}

void Robot::moveForward(int mm, int power)
{
	//convert
	//diametre chenille = 37mm
	//360 ticks => PI*D = PI*37mm
	// ?  <= distmm
	//mm * 360* ticks = 37PI
	float ticksf = (360.0 * mm) / (M_PI * asserv_default->diam_);
	int tick = (int) ticksf;

	long rest = tick; //reste à faire en tick
	while (rest > 0)
	{
		logger().debug() << "rest=" << rest << logs::end;
		asserv_default->moveD(tick, rest, power);
		rest = asserv_default->moveDWaitTrajectory();
	}

}
