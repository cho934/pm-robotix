/*
 * Robot.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: pmx
 */

#include <string.h>
#include <iostream>

#include "Robot.hpp"
#include "ConsoleUnitTestManager.hpp"

using namespace std;

void Robot::start(ConsoleUnitTestManager manager, int argc, char** argv)
{

	if (argc <= 1)
	{
		//print USAGE
		cout << "USAGE" << endl;
		cout << argv[0]
				<< " [M] [IAStrategy name] [encoder:Ext/Int] [setup:setup/nosetup] [color:yellow/green]"
				<< endl;
		cout << argv[0] << " [T] [Test name] [params..." << endl;

		exit(0);
	}

	//cas des matchs/homologations
	if (strcmp(argv[1], "M") == 0 || strcmp(argv[1], "m") == 0)
	{

		//init
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

	else if (strcmp(argv[1], "T") == 0 || strcmp(argv[1], "t") == 0) //cas des tests
	{
		//run
		if (argc == 2)
		{
			manager.run(argv[1]);
		}
		else
		{
			manager.run(atoi(argv[2]), argc, argv);
		}
	}
	else
	{
		//error
		cout << "Command " << argv[1] << " not found !" << endl;
	}
	cout << "PMX - Happy End" << endl;
	//logger.info() << "PMX - Happy End" << utils::end;
}
