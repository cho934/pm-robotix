/*!
 * \file
 * \brief Implémentation de la classe SupportTest.
 */

#include "SupportTest.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "../Bot-SmallPMX/SAsservExtended.hpp"
#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/Asserv/MotorControl.hpp"
#include "../Log/Logger.hpp"

using namespace std;

void SupportTest::run(int argc, char *argv[])
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
			std::cout << "power? " << std::flush;
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

	//todo setposition
	robot.actions.supportSystem().setPosition(10);

	logger().info() << "straighten..." << logs::end;
	robot.actions.supportSystem().straighten(power, timems);
	sleep(2);

	logger().info() << "incline..." << logs::end;
	robot.actions.supportSystem().incline(power, timems);
	sleep(2);

	logger().info() << "straighten..." << logs::end;
	robot.actions.supportSystem().straighten(power, timems);
	sleep(1);

	logger().info() << "stopMotor..." << logs::end;
	robot.actions.supportSystem().stopMotor();

	logger().info() << this->name() << " - Happy End." << logs::end;
}
