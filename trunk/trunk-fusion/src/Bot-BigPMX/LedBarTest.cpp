/*!
 * \file
 * \brief Implémentation de la classe LedBarTest.
 */

#include "../Action/LedBar.hpp"
#include "../Action/LedBarTest.hpp"

#include <iostream>
#include <string>


#include "BRobotExtended.hpp" //TODO remove this include

using namespace std;

void LedBarTest::run(int, char *[])
{
	cout << "Executing " << this->name() << endl;


	BRobotExtended robot;
	robot.actions.ledbar_.blink(1, 1000000);
	robot.actions.ledbar_.k2mil(5, 200000, 1);


	cout << "End of LedBarTest." << endl;
}

