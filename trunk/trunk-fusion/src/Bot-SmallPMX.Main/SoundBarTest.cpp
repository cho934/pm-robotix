/*!
 * \file
 * \brief Implémentation de la classe SoundBarTest.
 */

#include "SoundBarTest.hpp"

#include <iostream>
#include <string>

#include "../Bot-SmallPMX/SRobotExtended.hpp"

using namespace std;

void SoundBarTest::run(int, char *[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	SRobotExtended robot;

	logger().info() << this->name() << " - Happy End." << logs::end;

}

