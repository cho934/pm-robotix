/*!
 * \file
 * \brief Implémentation de la classe ApfI2cWithArduino, concernant la communication par I2C avec une carte Arduino.
 * \brief basé sur http://binerry.de/post/27128825416/raspberry-pi-with-i2c-arduino-slave
 */
#include <iostream>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdio.h>
#include <unistd.h>

#include <as_devices/as_i2c.h>
#include "ApfI2cWithArduino.hpp"

void test::ApfI2cWithArduino::run(int, char*[])
{
	std::cout
			<< "APF : Use I2C on devLightV2 (As_devices) with Grove Color Sensor"
			<< std::endl;
	std::cout << "==========================================" << std::endl;

	// initialize buffer
	buffer[0] = 0x00;
	int ret;
	int initialized = 0;

	i2c_bus = 0;
	int i2c_id = 0; //Bus I2C sur la carte APF9328

	// address of i2c Arduino device
	int deviceI2CAddress = 0x2A;  // (0x2A = 42)

	printf("Open i2c bus\n");
	i2c_bus = as_i2c_open(i2c_id);
	if (i2c_bus < 0)
	{
		printf("Error can't open i2c bus\n");
	}
	else
	{
		printf("Bus %d opened\n", i2c_id);
		initialized = 1;
	}

	ret = as_i2c_set_slave_addr(i2c_bus, deviceI2CAddress);
	if (ret < 0)
	{
		printf(" Error, can't close i2c bus num %d\n", i2c_id);
	}
	usleep(5000); //fréq i2c à 100kHz : attente de l'application complète de la trame

	buffer[0] = 0x00;
	// begin transmission and request acknowledgement
	ret = writeI2CSize(i2c_bus, buffer, 1);
	if (ret < 0)
	{
		printf(" Error writeI2CSize");
	}

	for (int i = 0; i < 20000; i++)
	{
		// drive some tests

		testCommand("L11", "LED1 on");
		usleep(500000);
		testCommand("L10", "LED1 off");
		usleep(500000);
		testCommand("L21", "LED2 on");
		usleep(500000);
		testCommand("L20", "LED2 off");
		usleep(500000);
	}

	printf("Close i2c bus\n");
	ret = as_i2c_close(i2c_bus);
	if (ret < 0)
	{
		printf(" Error, can't close i2c bus num %d\n", i2c_id);
	}
	else
	{
		initialized = 0;
	}

	std::cout << "End Of APF-TEST" << std::endl;
}

// function for testing command
void test::ApfI2cWithArduino::testCommand(const char command[3],
		const char action[10])
{
	std::cout << "Switching" << action << std::endl;
	int ret = 0;
	ret = writeI2CSize(i2c_bus, command, 3);
	if (ret < 0)
	{
		std::cout << "Error writeI2C" << std::endl;
	}

	// give arduino some reaction time
	usleep(1000);

	ret = readI2CSize(i2c_bus, buffer, 1);
	if (ret < 0)
	{
		std::cout << "Error readI2CSize" << std::endl;
	}
	else
	{
		// check response: 0 = error / 1 = success
		if (buffer[0] == 1)
		{
			std::cout << "success!" << std::endl;
		}else
		{
			std::cout << "error arduino!" << std::endl;
		}
	}
}

int test::ApfI2cWithArduino::readI2CSize(struct as_i2c_device *aDev, char *buf,
		size_t size)
{
	lock();
	int ret = 0;

	ret = as_i2c_read(aDev, (unsigned char*) buf, size);
	if (ret < 0)
	{
		std::cout << "ERROR as_i2c_read!" << std::endl;
	}
	unlock();
	return ret;
}

int test::ApfI2cWithArduino::writeI2CSize(struct as_i2c_device *aDev,
		const char *buf, size_t size)
{
	lock();
	int result = 0;
	result = as_i2c_write(aDev, (unsigned char*) buf, size);
	if (result < 0)
	{
		std::cout << "write : as_i2c_write" << std::endl;
	}
	unlock();
	return result;
}

