#include <iostream>

#include "../Common/Action/LedBar.hpp"

#include "../Bot-BigPMX/BRobotExtended.hpp"
#include "../Bot-BigPMX/LedBarTest.hpp"

#include "../Common/ConsoleUnitTestManager.hpp"


using namespace std;

int main(int argc, char** argv)
{
	cout << "!!! Hello BigPMX !!!" << endl;

	//Specific Robot BigPMX
	BRobotExtended robot;

	//common manager
	ConsoleUnitTestManager manager;

	//add specific tests for this robot
	manager.add(new LedBarTest());

	//start the Robot
	robot.start(manager, argc, argv);

	return 0;
}
