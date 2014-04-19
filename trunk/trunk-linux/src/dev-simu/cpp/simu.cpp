#ifdef SIMU

/*!
 * \file
 * \brief Implements all the fake methods in order to provide compatibility with
 * the armadeus system.
 */

#include <as_devices/as_max1027_3_3.h>
#include <as_devices/as_i2c.h>
#include <as_devices/as_spi.h>
#include <as_devices/as_gpio.h>
#include <as_devices/as_dac.h>
#include <as_devices/as_max5821.h>

as_max1027_device* as_max1027_open(int, int)
{
	return new as_max1027_device();
}

int32_t as_max1027_close(struct as_max1027_device *)
{
	return 0;
}

int32_t as_max1027_read_temperature_mC(struct as_max1027_device *,
		int *)
{
	return 0;
}

int32_t as_max1027_set_averaging_3_3(struct as_max1027_device *, uint8_t )
{
	return 0;
}
int32_t as_max1027_get_value_milliVolt(struct as_max1027_device *,
		int ,
		int *)
{
	return 0;
}

int readTemp(void)
{
	return 0;
}

void setAverage(int )
{
}

int readMillivolt(int )
{
	return 0;
}









//GPIO
struct as_gpio_device *as_gpio_open(char aPortChar, int aPinNum)
{

}

int32_t as_gpio_close(struct as_gpio_device *aDev)
{
	return 0;
}

int32_t as_gpio_set_pin_direction(struct as_gpio_device *aDev,
		int aDirection)
{
	return 0;
}

int32_t as_gpio_set_pin_value(struct as_gpio_device *aDev,
		int aValue)
{
	return 0;
}

int32_t as_gpio_blocking_get_pin_value(struct as_gpio_device *aDev,
                                       int aDelay_s,
                                       int aDelay_us)
{

}
int32_t as_gpio_get_pin_value(struct as_gpio_device *aDev)
{

}



//I2C
struct as_i2c_device *as_i2c_open(int aBusNumber)
{
}

int32_t as_i2c_close(struct as_i2c_device *aDev)
{
	return 0;
}

int32_t as_i2c_set_slave_addr(struct as_i2c_device *aDev, uint8_t aAddr)
{
	return 0;
}

int32_t as_i2c_read_reg(struct as_i2c_device *aDev,
		uint8_t aReg, uint8_t *aData, size_t n)
{
	return 0;
}
int32_t as_i2c_read(struct as_i2c_device *aDev,
		uint8_t *aData, size_t n)
{
	return 0;
}
int32_t as_i2c_write(struct as_i2c_device *aDev,
		uint8_t *aData, size_t n)
{
	return 0;
}
int32_t as_i2c_write_reg_byte(struct as_i2c_device *aDev,
		uint8_t aReg, uint8_t aVal)
{
	return 0;
}
int readRegisterbyte(struct as_i2c_device *aDev, unsigned char reg, unsigned char *data)
{

}



//SPI
int as_spi_open(const unsigned char *aSpidev_name)
{
	return 0;
}

void as_spi_close(int aFd)
{

}

uint32_t as_spi_get_speed(int aFd)
{
	return 0;
}

unsigned long long as_spi_msg(int aFd,
                              unsigned long long aMsg,
                              size_t aLen,
                              uint32_t aSpeed)
{

}


//DAC

struct as_dac_device *as_dac_open(const char *aDacType, int aBusNumber,
                                  int aAddress, int aVRef)
{

}

int32_t as_dac_max5821_power(struct as_dac_device *aDev,
                         char aChannel,
                         AS_max5821_power_mode aMode)
{
	return 0;
}

int32_t as_dac_set_value_in_millivolts(struct as_dac_device *aDev,
                                       int aChannel,
                                       int aValue)
{
}

int32_t as_dac_close(struct as_dac_device *aDev)
{
	return 0;
}




int32_t as_dac_set_value_max5821(struct as_dac_device *aDev,
                                 char aChannel,
                                 int aValue)
{

}





#endif
