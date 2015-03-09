#include "LedDriver.hpp"
#include "ev3dev.h"

ALedDriver * ALedDriver::create(int nb)
{
	return new LedDriver(nb);
}

LedDriver::LedDriver(int nb)
{
	nb = 2; //Force number of leds.
	//drivers...EV3

	//open chaque GPIO

}

LedDriver::~LedDriver()
{
	//close chaque GPIO
}

void LedDriver::set(int position, int aValue)
{
	if (position == 0) //Right
	{
		switch (aValue)
		{
		case LD_OFF: //Off
			ev3dev::led::green_right.off();
			ev3dev::led::red_right.off();
			break;
		case LD_GREEN: //green
			ev3dev::led::green_right.on();
			ev3dev::led::red_right.off();
			break;
		case LD_RED: //red
			ev3dev::led::green_right.off();
			ev3dev::led::red_right.on();
			break;
		case LD_ORANGE: //orange
			ev3dev::led::green_right.on();
			ev3dev::led::red_right.on();
			break;
		default:
			ev3dev::led::green_right.off();
			ev3dev::led::red_right.off();
			break;
		}
	}

	if (position == 1) //Left
	{
		switch (aValue)
		{
		case 0: //Off
			ev3dev::led::green_left.off();
			ev3dev::led::red_left.off();
			break;
		case 1: //green
			ev3dev::led::green_left.on();
			ev3dev::led::red_left.off();
			break;
		case 2: //red
			ev3dev::led::green_left.off();
			ev3dev::led::red_left.on();
			break;
		case 3: //orange
			ev3dev::led::green_left.on();
			ev3dev::led::red_left.on();
			break;
		default:
			ev3dev::led::green_left.off();
			ev3dev::led::red_left.off();
			break;
		}
	}
}
