//drivers...EV3

#include "DetectionSensorDriver.hpp"


using namespace std;
using namespace ev3dev;

ADetectSensorDriver * ADetectSensorDriver::create()
{
	static DetectionSensorDriver *instance = new DetectionSensorDriver();
	return instance;
}

DetectionSensorDriver::DetectionSensorDriver()
{
	ir_ = infrared_sensor(INPUT_2);
}

DetectionSensorDriver::~DetectionSensorDriver()
{
}

int DetectionSensorDriver::getDistanceMM()
{
	int percent = ir_.value(); //100% is approximately 70cm/27in

	return percent * 7;
}
