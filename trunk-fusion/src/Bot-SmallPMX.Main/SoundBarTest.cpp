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

	SRobotExtended &robot = SRobotExtended::instance();

	robot.actions.soundBar().beep(5);
	robot.actions.soundBar().speakPMX(50);


	robot.actions.start();

	robot.actions.soundBar().startBeep(25);
	robot.actions.soundBar().startBeep(50);

	sleep(1);

	robot.actions.stop();

	logger().info() << this->name() << " - Happy End." << logs::end;
	robot.actions.soundBar().beep(5);

}

