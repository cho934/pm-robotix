/*!
 * \file
 * \brief Implémentation de la classe GpioPort.
 */

#include <iostream>
#include <as_devices/as_gpio.h>

#include "GpioPort.hpp"

utils::GpioPort::GpioPort()
		: device_(NULL), opened_(0)
{
}

utils::GpioPort::GpioPort(char portLetter, int pinNum)
		: device_(NULL), opened_(0)
{
	lock();
	device_ = as_gpio_open(portLetter, pinNum);
	if (device_ == NULL)
	{

		//printf("Error can't open gpio %c\nHave you run loadgpio.sh ?\n", portLetter);
		throw new GpioException(
				"Error can't open gpio port. Have you run loadgpio.sh ?");
	}
	else
		opened_ = 1;
	unlock();
}

utils::GpioPort::~GpioPort()
{
	if (opened_ == 1)
	{
		throw new GpioException("Error gpio not closed");
	}
}

void utils::GpioPort::open(char portLetter, int pinNum)
{
	lock();
	device_ = as_gpio_open(portLetter, pinNum);
	std::cout << "as_gpio_open " << device_->fpin << std::endl;

	if (device_ == NULL)
	{
		//printf("Error can't open gpio %c\nHave you run loadgpio.sh ?\n", portLetter);
		throw new GpioException(
				"Error can't open gpio port. Have you run loadgpio.sh ?");
	}
	else
		opened_ = 1;
	unlock();
}

void utils::GpioPort::close(void)
{
	int ret = as_gpio_close(device_);
	if (ret < 0)
	{
		//printf("Error, can't close gpio\n");
		throw new GpioException("Error, can't close gpio");

	}
	opened_ = 0;
}

void utils::GpioPort::setDirection(int aDirection)
{
	int ret = as_gpio_set_pin_direction(device_, aDirection);
	if (ret < 0)
	{
		//printf("Error, can't change direction\n");
		throw new GpioException("Error, can't change direction");
	}
}

void utils::GpioPort::setValue(int aValue)
{
	int ret = as_gpio_set_pin_value(device_, aValue);
	if (ret < 0)
	{
		printf("Error, can't change pin value\n");
		throw new GpioException("Error, can't change pin value");
	}
}

