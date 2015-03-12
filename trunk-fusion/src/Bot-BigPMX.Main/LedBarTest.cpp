/*!
 * \file
 * \brief Implémentation de la classe LedBarTest.
 */

#include "../Common/Action/LedBar.hpp"
#include "LedBarTest.hpp"

#include <iostream>
#include <string>

#include "../Bot-BigPMX/BActionsExtended.hpp"
#include "../Bot-BigPMX/BRobotExtended.hpp"

using namespace std;

void LedBarTest::run(int, char *[])
{
	cout << "Executing " << this->name() << endl;

	BRobotExtended robot;

	robot.actions.ledbar().blink(1, 1000000);
	robot.actions.ledbar().k2mil(2, 500000, 1);

	cout << "End of LedBarTest." << endl;
}

