/*!
 * \file
 * \brief Implémentation de la classe GpioPort.
 */

#include <iostream>
#include <as_devices/as_gpio.h>

#include "GpioPort.hpp"

utils::GpioPort::GpioPort()
{
}

utils::GpioPort::~GpioPort()
{
}
/*
int utils::GpioPort::gpio_close(void)
{
	int ret = as_gpio_close(gpio_dev);
	if(ret < 0)
	{
		printf("Error, can't close gpio\n");
		return ret;
	}
	return 0;
}

int utils::GpioPort::gpio_set_pin_direction(int pinNum, int aDirection)
{
	int ret = as_gpio_set_pin_direction(gpio_dev, aDirection);
	if(ret < 0)
	{
		printf("Error, can't change direction\n");
		return ret;
	}
	return 0;
}

int utils::GpioPort::gpio_set_pin_value(int pinNum, int aValue)
{
	int ret = as_gpio_set_pin_value(gpio_dev, aValue);
	if(ret < 0)
	{
	 printf("Error, can't change pin value\n");
	 return ret;
	}
	return 0;
}*/

