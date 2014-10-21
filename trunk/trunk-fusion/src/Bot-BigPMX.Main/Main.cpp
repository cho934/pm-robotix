#include <iostream>

#include "../Action/LedBar.hpp"

#include "../Bot-BigPMX/BRobotExtended.hpp"

#include "../Common/ConsoleUnitTestManager.hpp"
#include "../Action/LedBarTest.hpp"

using namespace std;

int main(int argc, char** argv)
{
	cout << "!!! Hello BigPMX !!!" << endl;

	BRobotExtended robot;
	ConsoleUnitTestManager manager;

	//add test managers for this robot
	manager.add(new LedBarTest());

	if (argc <= 1)
	{
		//print USAGE
		cout << "USAGE" << endl;
		cout << argv[0]
				<< " [M] [IAStrategy name] [encoder:Ext/Int] [setup:setup/nosetup] [color:yellow/green]"
				<< endl;
		cout << argv[0] << " [T] [Test name] [params..." << endl;

		return 0;
	}

	robot.start(manager, argc, argv);

	return 0;
}
