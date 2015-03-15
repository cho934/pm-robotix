//drivers...SIMU

#include "LedDriver.hpp"

#include <bitset>
#include <cmath>

#include "../Common/LogAppender/Logger.hpp"

using namespace std;

ALedDriver * ALedDriver::create(int nb)
{
	return new LedDriver(nb);
}

LedDriver::LedDriver(int nb)
{
	hexa = 0;
	nb_ = nb;
	for (int i = 0; i < nb_; i++)
	{
		gpio[i] = 0;
	}
}

LedDriver::~LedDriver()
{
}

void LedDriver::setBit(int index, int color)
{
	gpio[index] = color;

	/*
	 Changing the nth bit to x

	 Setting the nth bit to either 1 or 0 can be achieved with the following:

	 number ^= (-x ^ number) & (1 << n);
	 Bit n will be set if x is 1, and cleared if x is 0.
	 */
	hexa ^= (-1 ^ hexa) & (1 << index);

	//logger().info() << "LED " << std::bitset<8>(hexa) << " (POS=" << index << ")" << logs::end;
	logger().info() << "LED " << logs::end;
	for (int i = 0; i < nb_; i++)
	{
		logger().info() << gpio[i] << logs::end;
	}
	/*
	 << gpio[0] << gpio[1]
	 << gpio[2] << gpio[3]
	 << gpio[4] << gpio[5]
	 << gpio[6] << gpio[7]*/
	logger().info() << " (POS=" << index << ")" << logs::end;

}

void LedDriver::setBytes(uint hex, int color)
{

	hexa = hex;

	for (int i = 0; i < nb_; i++)
	{
		if (((hex >> i) & 0x01) == 1)
		{
			gpio[i] = color;
		}
		else
		{
			gpio[i] = 0;
		}
	}
	logger().info() << "LED " << logs::end;
	for (int i = 0; i < nb_; i++)
	{
		logger().info() << gpio[i] << logs::end;
	}
	//<< gpio[0] << gpio[1]
	/*<< gpio[2] << gpio[3]
	 << gpio[4] << gpio[5]
	 << gpio[6] << gpio[7]*/
	//<< logs::end;
	//logger().info() << "LED " << std::bitset<8>(hexa) << logs::end;
}
