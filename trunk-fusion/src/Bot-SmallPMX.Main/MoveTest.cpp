/*!
 * \file
 * \brief Implémentation de la classe MotorTest.
 */

#include "MoveTest.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "../Bot-SmallPMX/SAsservExtended.hpp"
#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/Asserv/MotorControl.hpp"
#include "../Log/Logger.hpp"

using namespace std;

void MoveTest::run(int argc, char *argv[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	int power = 0;
	int mm = 0;
	int timems = 1000;
	std::cout << "argc: " << argc << std::endl;
	if (argc == 1)
	{
		power = 300;
		mm = 100;
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
			mm = atoi(argv[4]);
			std::cout << "dist mm: " << atoi(argv[4]) << std::endl;
		}
		else
		{
			std::cout << "dist mm? " << std::flush;
			std::cin >> mm;
		}

		if (argc > 5)
		{
			timems = atoi(argv[5]);
			std::cout << "time ms: " << atoi(argv[5]) << std::endl;
		}
		else
		{
			std::cout << "time ms? " << std::flush;
			std::cin >> timems;
		}
	}

	SRobotExtended &robot = SRobotExtended::instance();

	logger().info() << "moveD " << mm << " mm, power max=" << power << logs::end;
	robot.actions.trackSystem().moveForward(power, 0);
	robot.asserv.motors().moveD(mm, power);


	//robot.asserv.motors().turn(mm, power);

	logger().info() << "Stop" << logs::end;
	robot.asserv.motors().stopMotors();
	robot.actions.trackSystem().stopMotor();

	logger().info() << this->name() << " - Happy End." << logs::end;
}
