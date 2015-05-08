/*!
 * \file
 * \brief Implémentation de la classe RedCarpetTest.
 */

#include "RedCarpetTest.hpp"

#include <iostream>
#include <string>

#include "../Bot-SmallPMX/SRobotExtended.hpp"

using namespace std;

void RedCarpetTest::run(int argc, char *argv[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;
	int debug = 0;
	ostringstream out;
	if (argc <= 2)
	{
		debug = 0;
	}
	else
	{
		out << " debug(0-1):";
		if (argc > 3)
		{
			debug = atoi(argv[3]);
			out << atoi(argv[3]);
		}
	}
	logger().info() << out.str() << logs::end;

	SRobotExtended &robot = SRobotExtended::instance();


	robot.actions().redcarpetSystem().rightDeploy(debug);

	robot.actions().redcarpetSystem().leftDeploy(debug);

	logger().info() << this->name() << " - Happy End." << logs::end;
}
