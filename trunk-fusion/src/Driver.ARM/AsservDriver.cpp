//drivers...ARMADEUS

#include "AsservDriver.hpp"

using namespace std;

AAsservDriver * AAsservDriver::create()
{
	return new AsservDriver();
}

AsservDriver::AsservDriver()
{

}

AsservDriver::~AsservDriver()
{
}

void AsservDriver::setMotorLeftPower(int power, int timems)
{

}
void AsservDriver::setMotorRightPower(int power, int timems)
{

}

long AsservDriver::getLeftExternalEncoder()
{
	return 0; //TODO getLeftExternalEncoder
}
long AsservDriver::getRightExternalEncoder()
{
	return 0; //TODO getRightExternalEncoder
}

long AsservDriver::getLeftInternalEncoder()
{
	//+/- 2,147,483,648
	return 0;

}
long AsservDriver::getRightInternalEncoder()
{
	return 0;
}

void AsservDriver::stopMotorLeft()
{

}
void AsservDriver::stopMotorRight()
{

}

int AsservDriver::getMotorLeftCurrent()
{
	return 0;
}
int AsservDriver::getMotorRightCurrent()
{
	return 0;
}

void AsservDriver::enableHardRegulation(bool enable)
{

}
