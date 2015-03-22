//drivers...SIMULAUNCHER

#include "LedDriver.hpp"

ALedDriver * ALedDriver::create(int nb)
{
	return new LedDriver(nb);
}

LedDriver::LedDriver(int nb)
{
	//drivers...SIMU

}

LedDriver::~LedDriver()
{

}

void LedDriver::setBit(int index, int color)
{

}

void LedDriver::setBytes(uint hex, int color)
{

}
