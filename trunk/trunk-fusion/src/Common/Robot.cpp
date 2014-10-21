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

	//cas des matchs/homologations
	if (strcmp(argv[1], "M") == 0 || strcmp(argv[1], "m") == 0)
	{

		//init

		//launch state machine / Automate / IAExtend

		//logger.info() << "PMX - Happy End" << utils::end;
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
}
