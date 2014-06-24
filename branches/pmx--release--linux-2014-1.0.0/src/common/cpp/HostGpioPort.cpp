/*!
 * \file
 * \brief Implémentation de la classe GpioPort.
 */

#include <iostream>
#include <sstream>
#include <as_devices/as_gpio.h>
#include <stdlib.h>
#include <string.h>

#include "HostGpioPort.hpp"

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

//Definition de l'attribut de classe
int* utils::HostGpioPort::portA_opened_ = NULL;
int* utils::HostGpioPort::portB_opened_ = NULL;
int* utils::HostGpioPort::portC_opened_ = NULL;
int* utils::HostGpioPort::portD_opened_ = NULL;

utils::HostGpioPort::HostGpioPort()
		: device_(NULL), fd_gpio_(0), port_letter_(NULL), pin_number_(0)
{
	if (utils::HostGpioPort::portA_opened_ == NULL)
	{
		utils::HostGpioPort::portA_opened_ = (int *) malloc(32 * sizeof(int));
		memset(utils::HostGpioPort::portA_opened_, 0, 32 * sizeof(int));
	}
	if (utils::HostGpioPort::portB_opened_ == NULL)
	{
		utils::HostGpioPort::portB_opened_ = (int *) malloc(32 * sizeof(int));
		memset(utils::HostGpioPort::portB_opened_, 0, 32 * sizeof(int));
	}
	if (utils::HostGpioPort::portC_opened_ == NULL)
	{
		utils::HostGpioPort::portC_opened_ = (int *) malloc(32 * sizeof(int));
		memset(utils::HostGpioPort::portC_opened_, 0, 32 * sizeof(int));
	}
	if (utils::HostGpioPort::portD_opened_ == NULL)
	{
		utils::HostGpioPort::portD_opened_ = (int *) malloc(32 * sizeof(int));
		memset(utils::HostGpioPort::portD_opened_, 0, 32 * sizeof(int));
	}
}

utils::HostGpioPort::~HostGpioPort()
{
}

void utils::HostGpioPort::openAs(char portLetter, int pinNum)
{
	port_letter_ = portLetter;
	pin_number_ = pinNum;

	checkIf(1); //check if gpio is not opened

	device_ = as_gpio_open(portLetter, pinNum);
	if (device_ == NULL)
	{
		throw new HostGpioException("Error gpio openAs, can't open gpio port. Have you run loadgpio.sh ?");
	}
	else
	{
		setData(1);
	}
}

void utils::HostGpioPort::closeAs(void)
{
	checkIf(0); //check if gpio is opened

	int ret = as_gpio_close(device_);
	if (ret < 0)
	{
		throw new HostGpioException("Error gpio closeAs, can't close gpio");
	}
	setData(0);
}

void utils::HostGpioPort::setDirectionAs(int aDirection)
{
	checkIf(0); //check if gpio is opened

	int ret = as_gpio_set_pin_direction(device_, aDirection);
	if (ret < 0)
	{
		std::ostringstream msg;
		msg << "Error gpio setDirectionAs, can't change direction on " << port_letter_ << pin_number_ << " !";
		throw new HostGpioException(msg.str());
	}
}

void utils::HostGpioPort::setValueAs(int aValue)
{
	checkIf(0); //check if gpio is opened

	int ret = as_gpio_set_pin_value(device_, aValue);
	if (ret < 0)
	{
		throw new HostGpioException("Error gpio setValueAs, can't change pin value");
	}
}

void utils::HostGpioPort::checkIf(int value)
{
	std::ostringstream msg;
	int err = 0;
	switch (port_letter_)
	{
	case 'A':
		if (utils::HostGpioPort::portA_opened_[pin_number_] == value)
		{
			err = 1;
		}
		break;
	case 'B':
		if (utils::HostGpioPort::portB_opened_[pin_number_] == value)
		{
			err = 1;
		}
		break;
	case 'C':
		if (utils::HostGpioPort::portC_opened_[pin_number_] == value)
		{
			err = 1;
		}
		break;
	case 'D':
		if (utils::HostGpioPort::portD_opened_[pin_number_] == value)
		{
			err = 1;
		}
		break;
	default:
		throw new HostGpioException("--Error gpio check, port not yet defined");
	}
	if (err == 1)
	{
		if (value == 0)
			msg << "Error gpio " << port_letter_ << pin_number_ << " not opened !";
		else
			msg << "Error gpio " << port_letter_ << pin_number_ << " already opened !";
		throw new HostGpioException(msg.str());
	}
}

void utils::HostGpioPort::setData(int value)
{
	switch (port_letter_)
	{
	case 'A':
		utils::HostGpioPort::portA_opened_[pin_number_] = value;
		break;
	case 'B':
		utils::HostGpioPort::portB_opened_[pin_number_] = value;
		break;
	case 'C':
		utils::HostGpioPort::portC_opened_[pin_number_] = value;
		break;
	case 'D':
		utils::HostGpioPort::portD_opened_[pin_number_] = value;
		break;
	default:
		throw new HostGpioException("---Error gpio setData, port not yet defined");
	}
}

void utils::HostGpioPort::openIoctl(char portLetter, int pinNum)
{
	port_letter_ = portLetter;
	pin_number_ = pinNum;
	checkIf(1); //check if gpio is not opened
	std::ostringstream oss;
	oss << "/dev/gpio/P" << portLetter << pinNum;
	std::string result = oss.str();
	const char* cchar = result.c_str();
	if ((fd_gpio_ = open(cchar, O_RDWR)) < 0)
	{
		throw new HostGpioException("ERROR gpio openIoctl, can't open gpio port. Have you run loadgpio.sh ?");
	}
	//Set LED PIN as GPIO mode;
	int portval = 1;
	int err = ioctl(fd_gpio_, GPIOWRMODE, &portval);
	if (err < 0)
	{
		throw new HostGpioException("ERROR gpio openIoctl, unable to set gpio mode !");
	}
	setData(1); //gpio opened
}

void utils::HostGpioPort::closeIoctl(void)
{
	checkIf(0); //check if gpio is opened
	close(fd_gpio_);
	setData(0); //close gpio
}

void utils::HostGpioPort::setDirIoctl(int aDirection)
{
	checkIf(0); //check if gpio is opened

	if (aDirection != 0 and aDirection != 1)
	{
		throw new HostGpioException("Error gpio setDirIoctl, bad aDirection !");
	}
	int err = ioctl(fd_gpio_, GPIOWRDIRECTION, &aDirection); //OUT => 1 IN =>0
	if (err < 0)
	{
		throw new HostGpioException("ERROR setDirIoctl, unable to set gpio direction !");
	}
}

void utils::HostGpioPort::setValueIoctl(bool aValue)
{
	checkIf(0); //check if gpio is opened

	int portval = 1;
	if (aValue == false)
		portval = 0;
	else
		portval = 1;
	int err = ioctl(fd_gpio_, GPIOWRDATA, &portval);
	if (err < 0)
	{
		throw new HostGpioException("ERROR gpio setValueIoctl, unable to set gpio value !");
	}
}
