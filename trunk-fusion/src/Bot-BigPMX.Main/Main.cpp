#include <iostream>

#include "../Common/ConsoleManager.hpp"
#include "../Common/Action/LedBar.hpp"
#include "../Bot-BigPMX/BRobotExtended.hpp"
#include "../Bot-BigPMX/LedBarTest.hpp"

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
