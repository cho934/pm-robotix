

#include "DetectionTest.hpp"

#include <string>

#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Log/Logger.hpp"


using namespace std;

void DetectionTest::run(int, char *[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	SRobotExtended &robot = SRobotExtended::instance();

	logger().info() << "Detection status" << logs::end;

	robot.actions().detectionSensor().monitor(10);


	logger().info() << "Happy End." << logs::end;
}

