#include <iostream>

#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/ConsoleManager.hpp"
#include "ButtonBarTest.hpp"
#include "DetectionTest.hpp"
#include "EncoderTest.hpp"
#include "LedBarTest.hpp"
#include "MotorTest.hpp"
#include "MoveTest.hpp"
#include "ServoTest.hpp"
#include "SoundBarTest.hpp"
#include "SupportTest.hpp"
#include "TiretteTest.hpp"

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
	manager.add(new ButtonBarTest());
	manager.add(new TiretteTest());
	manager.add(new SoundBarTest());
	manager.add(new EncoderTest());
	manager.add(new DetectionTest());
	manager.add(new MotorTest());
	manager.add(new MoveTest());
	manager.add(new SupportTest());
	manager.add(new ServoTest());


/*
	char cInput;
	cout << "Press Enter key to continue ...\n" << endl;
	do
	{
		cInput = ConsoleKeyInput::mygetch();
		switch (cInput)
		{

		case 10:
			//printf("Enter key!\n");
			break;
		case 127:
			cout << "Exit !\n" << endl;
			//cout << default_console << endl;
			exit(0);
			break;
		}
		usleep(1000);
	} while (cInput != 10);
*/

	//start the Robot (functional tests or match)
	robot.start(manager, argc, argv);

	//sleep(1);
	return 0;
}
