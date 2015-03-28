/*!
 * \file
 * \brief Implémentation de la classe EncoderTest.
 */

#include "EncoderTest.hpp"

#include <iostream>
#include <string>

#include "../Bot-SmallPMX/SRobotExtended.hpp"

using namespace std;

void EncoderTest::run(int, char *[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	SRobotExtended &robot = SRobotExtended::instance();
	int nb = 10;
	int timeSpan = 1000;

	//TODO if connected_

	long left = robot.asserv.encoders().getLeftEncoder();
	long right = robot.asserv.encoders().getLeftEncoder();


	for (int i = 0; i < nb; i++)
		{
			usleep(timeSpan * 1000);

			left = robot.asserv.encoders().getLeftEncoder();
			right = robot.asserv.encoders().getRightEncoder();

			std::cout << "counterL = " << left << "\t\t counterR = " << right << std::endl;
		}

	logger().info() << this->name() << " - Happy End." << logs::end;
}
