/*
 * Robot.cpp
 * test
 *
 */

#include "Robot.hpp"

#include <string.h>
#include <cstdlib>
#include <iostream>

using namespace std;

void Robot::start(ConsoleManager manager, int argc, char** argv)
{
	string select;
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
		if (strcmp(argv[1], "U") == 0 || strcmp(argv[1], "-usage") == 0
				|| strcmp(argv[1], "-USAGE") == 0
				|| strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-help") == 0
				|| strcmp(argv[1], "-h") == 0)
		{
			cout << "USAGE" << endl;
			cout << argv[0]
					<< " [M] [IAStrategy:code] [encoder:ext/int] [choose:setup/nosetup] [color:yellow/green]"
					<< endl;
			cout << argv[0] << " [T] [Test:Num[1-100] [params...]" << endl;
			exit(0);
		}

		//Case if matches/homologation.
		if (strcmp(argv[1], "M") == 0 || strcmp(argv[1], "m") == 0)
		{
			//init Automate for Match
			/*
			 // Create the data used to run the automate
			 Data *data = new Data();
			 data->isEmpty(true);

			 //launch state machine / Automate / IAExtend
			 IAutomateState* waitForReboot = new pmx::StateWaitForReboot();
			 IAutomateState* initialize = new pmx::StateInitialize();
			 IAutomateState* waitForStart = new pmx::StateWaitForStart();

			 waitForReboot->addState("next", initialize);

			 initialize->addState("next", ajustRobotPosition);
			 initialize->addState("waitForReboot", waitForReboot);

			 ajustRobotPosition->addState("next", waitForStart);

			 waitForStart->addState("rebootInitialize", initialize);
			 waitForStart->addState("decisionMaker", data->decisionMaker);

			 // Start the automate and wait for its return
			 Automate *automate = new Automate();
			 automate->run(robot, waitForReboot, data);

			 //TODO : stop all
			 */
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
	//cout << "PMX - Happy End" << endl;
}
