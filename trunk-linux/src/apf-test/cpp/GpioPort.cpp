/*!
 * \file
 * \brief Implémentation de la classe GpioPort.
 */

#include <iostream>
#include <as_devices/as_gpio.h>

#include "GpioPort.hpp"

utils::GpioPort::GpioPort()
{
	gpio_dev=0;
}

utils::GpioPort::~GpioPort()
{
}

int utils::GpioPort::gpio_open(char portLetter, int pinNum)
{
	gpio_dev = as_gpio_open(portLetter, pinNum);
	if (gpio_dev == NULL)
	{
		printf("Error can't open gpio %c\nHave you run loadgpio.sh ?\n",
				portLetter);
		return -1;
	}
	return 0;
}

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

int utils::GpioPort::gpio_set_pin_direction(int aDirection)
{
	int ret = as_gpio_set_pin_direction(gpio_dev, aDirection);
	if(ret < 0)
	{
		printf("Error, can't change direction\n");
		return ret;
	}
	return 0;
}

int utils::GpioPort::gpio_set_pin_value(int aValue)
{
	int ret = as_gpio_set_pin_value(gpio_dev, aValue);
	if(ret < 0)
	{
	 printf("Error, can't change pin value\n");
	 return ret;
	}
	return 0;
}

