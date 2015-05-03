//drivers...SIMU

#include "DetectionSensorDriver.hpp"

using namespace std;

ADetectSensorDriver * ADetectSensorDriver::create()
{
	static DetectionSensorDriver *instance = new DetectionSensorDriver();
	return instance;
}

DetectionSensorDriver::DetectionSensorDriver()
{

}

DetectionSensorDriver::~DetectionSensorDriver()
{
}

int DetectionSensorDriver::getDistanceMM()
{
	return 0;
}
