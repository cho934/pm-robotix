#include <iostream>

#include "../Bot-SmallPMX/SRobotExtended.hpp"

using namespace std;

int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	SRobotExtended robot;

	robot.actions.ledbar_.blink(1, 1, LD_ORANGE);

	return 0;
}
