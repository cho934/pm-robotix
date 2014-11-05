//drivers...SIMU

#include "LedDriver.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;

ALedDriver * ALedDriver::create(int nb)
{
	return new LedDriver(nb);
}

LedDriver::LedDriver(int nb)
{
	nb_ = nb;
	for (int i = 0; i < nb_; i++)
	{
		gpio[i] = 0;
	}
}

LedDriver::~LedDriver()
{
}

void LedDriver::set(int position, int aValue)
{
	gpio[position] = aValue;

	cout << "LED" << position << "=" << aValue << endl;

}
