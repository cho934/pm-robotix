/*!
 * \file
 * \brief Implémentation de la classe ApfUartWithAX12, concernant l'utilisation de la carte de motorisation MD25.
 */

#include "ApfI2cWithMd25.hpp"

#include <as_devices/as_i2c.h>
#include <unistd.h>
//#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>

void ApfI2cWithMd25::run(int, char*[])
{
	std::cout << "APF : Use I2C on devLightV2 (As_devices) with MD25" << std::endl;

	struct as_i2c_device *i2c_bus = 0;
	int value = 0;

	printf("Open i2c bus\n");
	i2c_bus = as_i2c_open(MD25_I2C_BUS);
	if (i2c_bus < 0)
	{
		printf("Error can't open i2c bus\n");
	}
	else
	{
		printf("Bus %d opened\n", MD25_I2C_BUS);
	}

	value = as_i2c_set_slave_addr(i2c_bus, MD25_DEFAULT_ADDRESS);
	if (value < 0)
	{
		printf(" Error, can't as_i2c_set_slave_addr i2c bus num %d\n", MD25_I2C_BUS);
	}
	usleep(5000); //fréq i2c à 100kHz : attente de l'application complète de la trame

	int ver = getSoftwareVersion(i2c_bus);
	std::cout << "getSoftwareVersion" << ver << std::endl;

	float bat = getBatteryVolts(i2c_bus);
	std::cout << "getBatteryVolts" << bat << std::endl;

	printf("Close i2c bus\n");
	value = as_i2c_close(i2c_bus);
	if (value < 0)
	{
		printf(" Error, can't close i2c bus num %d\n", MD25_I2C_BUS);
	}

	std::cout << "End Of APF-TEST" << std::endl;
}

/*
 * Private Methods
 */

int ApfI2cWithMd25::readRegisterbyte(struct as_i2c_device *aDev, unsigned char reg, unsigned char *data)
{
	lock();
	int ret = 0;
	//ret = as_i2c_read_reg(fd_, adr, reg, data, 1); //return 0 on success, -1 on write error (\e reg byte), -2 on read error.


	ret = as_i2c_read_reg(aDev, reg, data, 1);
	if (ret < 0)
	{
		//errorCount_++;
		if (ret == -1)
			std::cout << "as_i2c_read_reg_byte: reg " << (int) reg << " WRITE error!" << std::endl;
		if (ret == -2)
			std::cout << "as_i2c_read_reg_byte: reg " << (int) reg << " READ error!" << std::endl;
		exit(1);
	}
	else
	{
		//errorCount_ = 0;
	}
	unlock();
	return ret;
}

int ApfI2cWithMd25::writeRegisterbyte(struct as_i2c_device *aDev, unsigned char reg, unsigned char value)
{
	//logger().error() << "as_i2c_write_reg_byte: adr=" << (int) adr << utils::end;
	lock();
	int result = 0;
	//result = as_i2c_write_reg_byte(fd_, adr, reg, value);
	result = as_i2c_write_reg_byte(aDev, reg, value);

	if (result < 0)
	{
		//errorCount_++;
		std::cout << "as_i2c_write_reg_byte: reg=" << (int) reg << " val=" << (int) value << " !" << std::endl;
		exit(1);
	}
	else
	{
		//errorCount_ = 0;
	}
	//usleep(1000); //fréq i2c à 100kHz : attente de l'application complète de la trame

	unlock();
	return result;
}

int ApfI2cWithMd25::getSoftwareVersion(struct as_i2c_device *aDev)
{
	uint8_t val;
	int ret = 0;
	ret = readRegisterbyte(aDev, MD25_SOFTWAREVER_REG, &val);
	return val;
}

float ApfI2cWithMd25::getBatteryVolts(struct as_i2c_device *aDev)
{
	uint8_t val;
	int ret = 0;
	ret = readRegisterbyte(aDev, MD25_VOLTAGE_REG, &val);
	return (float) val / 10.0;
}
