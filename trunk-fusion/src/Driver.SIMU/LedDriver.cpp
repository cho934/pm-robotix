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

void LedDriver::set(int position, int color)
{
	gpio[position] = color;

	//cout << "LED" << position << "=" << color << endl;
	for (int i = 0; i < nb_; i++)
	{
		cout << gpio[i] ;
	}
	cout << endl;
}
