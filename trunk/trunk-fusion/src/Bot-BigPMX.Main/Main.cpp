#include <iostream>

#include "../Bot-BigPMX/BRobotExtended.hpp"
#include "../Common/ConsoleManager.hpp"
#include "LedBarTest.hpp"


using namespace std;

int main(int argc, char** argv)
{
	cout << "!!! Hello BigPMX !!!" << endl;

	//Specific Robot BigPMX
	BRobotExtended robot;

	//common manager
	ConsoleManager manager;

	//add specific tests for this robot
	manager.add(new LedBarTest());

	//start the Robot (functional tests or match)
	robot.start(manager, argc, argv);

	return 0;
}
