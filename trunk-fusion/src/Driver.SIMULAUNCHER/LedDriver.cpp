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

void LedDriver::set(int position, int aValue)
{

}
