
#include "TiretteTest.hpp"

#include <string>

#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Log/Logger.hpp"


using namespace std;

void TiretteTest::run(int, char *[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	SRobotExtended &robot = SRobotExtended::instance();

	logger().info() << "Please press TIRETTE" << logs::end;

	robot.actions.tirette().monitor(3);


	logger().info() << "Happy End." << logs::end;
}

