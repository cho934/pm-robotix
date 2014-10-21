#include <iostream>

#include "../Bot-BigPMX/BRobotExtended.hpp"

using namespace std;

int main()
{
	cout << "!!!TEst!!!" << endl; // TODO les faire directement sur l'exe principal ?

	BRobotExtended robot;

	robot.actions.ledbar_.blink(3, 100);

	return 0;
}
