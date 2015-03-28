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

	//SRobotExtended robot; //todo une seule instance
	SRobotExtended &robot = SRobotExtended::instance();

	robot.actions.soundbar().beep(5);
	robot.actions.soundbar().speakPMX(50);


	robot.actions.start();

	robot.actions.soundbar().startBeep(25);
	robot.actions.soundbar().startBeep(50);

	sleep(1);

	robot.actions.stop();

	logger().info() << this->name() << " - Happy End." << logs::end;
	robot.actions.soundbar().beep(5);

}

