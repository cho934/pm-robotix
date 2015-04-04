/*!
 * \file
 * \brief Implémentation de la classe MotorTest.
 */

#include "MotorTest.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "../Bot-SmallPMX/SAsservExtended.hpp"
#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/Asserv/MotorControl.hpp"
#include "../Log/Logger.hpp"

using namespace std;

void MotorTest::run(int argc, char *argv[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	int power = 0;
	int timems = 1000;
	std::cout << "argc: " << argc << std::endl;
	if (argc == 1)
	{
		power= 300;
		timems = 5000;
	}
	else
	{
		if (argc > 3)
		{
			power = atoi(argv[3]);
			std::cout << "power: " << atoi(argv[3]) << std::endl;
		}
		else
		{
			std::cout << "power(-900/+900)? " << std::flush;
			std::cin >> power;
		}

		if (argc > 4)
		{
			timems = atoi(argv[4]);
			std::cout << "time ms: " << atoi(argv[4]) << std::endl;
		}
		else
		{
			std::cout << "time ms? " << std::flush;
			std::cin >> timems;
		}
	}

	SRobotExtended &robot = SRobotExtended::instance();

	robot.asserv.motors().turnRight(400, 1000);


	robot.asserv.motors().moveForward(power, 0);
	robot.actions.trackSystem().moveForward(power+200, 0);

	usleep(timems * 1000);

	robot.asserv.motors().stopMotors();
	robot.actions.trackSystem().stopMotor();

	logger().info() << this->name() << " - Happy End." << logs::end;
}
