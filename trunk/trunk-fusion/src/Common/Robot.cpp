/*
 * Robot.cpp
 * test
 *
 */

#include "Robot.hpp"

#include <string.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "../Log/Logger.hpp"
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
}

void Robot::start(ConsoleManager manager, int argc, char** argv)
{
	string select;
	int skip = 0;
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
			cout << argv[0] << " [M] [color:y/g] [skip setup:0/1]  " //[IAStrategy:code] [encoder:ext/int]
					<< endl;
			cout << argv[0] << " [T] [Test:Num[1-100] [params...]" << endl;
			exit(0);
		}

		//Case if matches/homologation.
		if (strcmp(argv[1], "M") == 0 || strcmp(argv[1], "m") == 0)
		{

			if (argc > 2)
			{
				if ((strcmp(argv[2], "y") == 0)||(strcmp(argv[2], "Y") == 0))
				{
					this->setMyColor(PMXYELLOW);
				}
				if ((strcmp(argv[2], "g") == 0)||(strcmp(argv[2], "G") == 0))
				{
					this->setMyColor(PMXGREEN);
				}

			}
			if (argc > 3)
			{
				skip = atoi(argv[3]);
			}

			//init Automate for Match

			// Create the data used to run the automate
			Data *data = new Data();
			data->isEmpty(true);

			data->skipSetup(skip);

			logger().info() << "Start of PMX, the robot..." << logs::end;

			IAutomateState* waitForReboot = new StateWaitForReboot();
			IAutomateState* initialize = new StateInitialize();
			IAutomateState* ajustRobotPosition = new StateAdjustRobotPosition();
			IAutomateState* waitForStart = new StateWaitForStart();

			waitForReboot->addState("next", initialize);
			initialize->addState("next", ajustRobotPosition);
			initialize->addState("waitForReboot", waitForReboot);
			ajustRobotPosition->addState("next", waitForStart);

			waitForStart->addState("rebootInitialize", initialize);
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
			cout << "Command " << argv[1] << " not found !" << endl;
		}
	}
}
