
#include <iostream>

#include "../Bot-SmallPMX/LedBarTest.hpp"
#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/ConsoleManager.hpp"


using namespace std;


int main(int argc, char** argv)
{
	cout << "!!!Hello SmallPMX EV3!!!" << endl;

	SRobotExtended robot;

	//common manager
	ConsoleManager manager;

	//add specific tests for this robot
	manager.add(new LedBarTest());
	manager.add(new LedBarTest());
	manager.add(new LedBarTest());
	manager.add(new LedBarTest());
	manager.add(new LedBarTest());
	manager.add(new LedBarTest());

	//start the Robot (functional tests or match)
	robot.start(manager, argc, argv);

	return 0;

}
