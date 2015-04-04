/*!
 * \file
 * \brief Implémentation de la classe GpioPort.
 */

#include "GpioPort.hpp"

#include <as_devices/as_gpio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iostream>

//IOCTL
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/ppdev.h>

#define GPIORDDIRECTION	_IOR(PP_IOCTL, 0xF0, int)
#define GPIOWRDIRECTION	_IOW(PP_IOCTL, 0xF1, int)
#define GPIORDDATA	_IOR(PP_IOCTL, 0xF2, int)
#define GPIOWRDATA	_IOW(PP_IOCTL, 0xF3, int)
#define GPIORDMODE	_IOR(PP_IOCTL, 0xF4, int)
#define GPIOWRMODE	_IOW(PP_IOCTL, 0xF5, int)

utils::GpioPort::GpioPort()
		: device_(NULL), opened_(0), fd_(0)
{
}
/*
 utils::GpioPort::GpioPort(char portLetter, int pinNum)
 : device_(NULL), opened_(0), fd_(0)
 {
 //TODO
 }*/

utils::GpioPort::~GpioPort()
{
	if (opened_ == 1)
	{
		throw new GpioException("Error gpio not closed");
	}
}

void utils::GpioPort::openAs(char portLetter, int pinNum)
{
	//lock();
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
	//unlock();
}

void utils::GpioPort::closeAs(void)
{
	int ret = as_gpio_close(device_);
	if (ret < 0)
	{
		//printf("Error, can't close gpio\n");
		throw new GpioException("Error, can't close gpio");

	}
	opened_ = 0;
}

void utils::GpioPort::setDirectionAs(int aDirection)
{
	int ret = as_gpio_set_pin_direction(device_, aDirection);
	if (ret < 0)
	{
		//printf("Error, can't change direction\n");
		throw new GpioException("Error, can't change direction");
	}
}

void utils::GpioPort::setValueAs(int aValue)
{
	//std::cout << "setValueAs " << std::endl;
	int ret = as_gpio_set_pin_value(device_, aValue);
	if (ret < 0)
	{
		//printf("Error, can't change pin value\n");
		throw new GpioException("Error, can't change pin value");
	}
}

void utils::GpioPort::openIoctl(char portLetter, int pinNum)
{
	std::ostringstream oss;
	oss << "/dev/gpio/P" << portLetter << pinNum;
	std::string result = oss.str();
	const char* cchar = result.c_str();

	if ((fd_ = open(cchar, O_RDWR)) < 0)
	{
		throw new GpioException(
				"Error can't open gpio port. Have you run loadgpio.sh ?");
	}

	//Set LED PIN as GPIO mode;
	int portval = 1;
	ioctl(fd_, GPIOWRMODE, &portval);

}

void utils::GpioPort::closeIoctl(void)
{
	close(fd_);
}

void utils::GpioPort::setDirIoctl(int aDirection)
{
	if (aDirection != 0 and aDirection != 1)
	{
		throw new GpioException("Error setDirIoctl, bad aDirection !");
	}
	ioctl(fd_, GPIOWRDIRECTION, &aDirection); //OUT => 1 IN =>0
}

void utils::GpioPort::setValueIoctl(bool aValue)
{
	int portval = 1;
	if (aValue == false)
		portval = 0;
	else
		portval = 1;
	ioctl(fd_, GPIOWRDATA, &portval);
}
