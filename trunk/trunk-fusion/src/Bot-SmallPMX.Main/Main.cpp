
#include <iostream>

#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/ConsoleManager.hpp"
#include "EncoderTest.hpp"
#include "LedBarTest.hpp"
#include "MotorTest.hpp"
#include "SoundBarTest.hpp"


using namespace std;


int main(int argc, char** argv)
{
	cout << "!!!Hello SmallPMX EV3!!!" << endl;

	//SRobotExtended robot;
	SRobotExtended &robot = SRobotExtended::instance();

	//common manager
	ConsoleManager manager;

	//add specific tests for this robot
	manager.add(new LedBarTest());
	manager.add(new SoundBarTest());
	manager.add(new EncoderTest());
	manager.add(new MotorTest());

	//start the Robot (functional tests or match)
	robot.start(manager, argc, argv);

	return 0;
}
