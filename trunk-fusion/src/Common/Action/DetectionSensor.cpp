#include "DetectionSensor.hpp"

#include <unistd.h>

using namespace std;

DetectionSensor::DetectionSensor(Actions & actions) :
		AActionsElement(actions)

{
	detectsensordriver = ADetectSensorDriver::create();
}

DetectionSensor::~DetectionSensor()
{
}

int DetectionSensor::getDistanceMM()
{
	int temp = detectsensordriver->getDistanceMM();
	return temp;
}

void DetectionSensor::monitor(int nb)
{
	logger().info() << "monitor" << logs::end;
	int n = 0;
	int dist = 0;
	bool detect;
	while (n <= nb)
	{
		dist = getDistanceMM();
		detect = isAdversaryDetected();

		logger().info() << "dist = " << dist << " isAdversaryDetected = " << detect << logs::end;
		usleep(1000000);
		n++;
	}
}

bool DetectionSensor::isAdversaryDetected()
{
	if (getDistanceMM() < 300)
	{
		return true;
	}else
	{
		return false;
	}
}
