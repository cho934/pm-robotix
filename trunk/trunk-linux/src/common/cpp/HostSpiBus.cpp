/*!
 * \file
 * \brief Implémentation de la classe HostSpiBus.
 */

#include <iostream>
#include <sstream>

#include "HostSpiBus.hpp"

utils::HostSpiBus::HostSpiBus()
		: fd_(0), opened_(0)
{
}

void utils::HostSpiBus::open(void)
{
	const char *aSpidev_name = APF9328_SPI;
	unsigned char *d = (unsigned char*) aSpidev_name;
	fd_ = as_spi_open(d);
	if (fd_ < 0)

	{
		throw new HostSpiException("Error HostI2cBus::open, can't open SPI \nHave you run modprobe spidev ?");
	}
}

void utils::HostSpiBus::close(void)
{
	as_spi_close(fd_);
}

long utils::HostSpiBus::getSpeed(void)
{
	long speed = as_spi_get_speed(fd_);
	return speed;
}

char utils::HostSpiBus::spiTransfer(char data)
{
	unsigned long long result = as_spi_msg(fd_, (unsigned long long) data, 8, CLOCKSPEED);
	return result;
}
