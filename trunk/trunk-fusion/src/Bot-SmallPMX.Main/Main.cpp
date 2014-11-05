#include <iostream>

#include "../Bot-SmallPMX/SRobotExtended.hpp"

using namespace std;

int main()
{
	cout << "!!!Hello SmallPMX EV3!!!" << endl; // prints !!!Hello World!!!

	SRobotExtended robot;

	robot.actions.ledbar_.blink(1, 1, LD_ORANGE);

	robot.actions.ledbar_.k2mil(5,200000,1);

	return 0;
}
