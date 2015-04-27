/*!
 * \file
 * \brief Implémentation de la classe EncoderTest.
 */

#include "ServoTest.hpp"

#include <iostream>
#include <string>

#include "../Bot-SmallPMX/SRobotExtended.hpp"

using namespace std;

void ServoTest::run(int, char *[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	SRobotExtended &robot = SRobotExtended::instance();

	robot.actions.redcarpetSystem().leftDeploy();
	robot.actions.redcarpetSystem().rightDeploy();



	logger().info() << this->name() << " - Happy End." << logs::end;
}
