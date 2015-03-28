/*!
 * \file
 * \brief Implémentation de la classe MotorTest.
 */

#include "MotorTest.hpp"

#include <iostream>
#include <string>

#include "../Bot-SmallPMX/SRobotExtended.hpp"

using namespace std;

void MotorTest::run(int, char *[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	SRobotExtended &robot = SRobotExtended::instance();

	//long left = robot.asserv.



	logger().info() << this->name() << " - Happy End." << logs::end;
}
