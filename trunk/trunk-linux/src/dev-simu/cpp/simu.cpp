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
struct as_gpio_device *as_gpio_open(char , int )
{
}

int32_t as_gpio_close(struct as_gpio_device *)
{
	return 0;
}

int32_t as_gpio_set_pin_direction(struct as_gpio_device *,
		int )
{
	return 0;
}

int32_t as_gpio_set_pin_value(struct as_gpio_device *,
		int )
{
	return 0;
}

int32_t as_gpio_blocking_get_pin_value(struct as_gpio_device *,
                                       int ,
                                       int )
{
	return 0;
}
int32_t as_gpio_get_pin_value(struct as_gpio_device *)
{
	return 0;
}



//I2C
struct as_i2c_device *as_i2c_open(int )
{
}

int32_t as_i2c_close(struct as_i2c_device *)
{
	return 0;
}

int32_t as_i2c_set_slave_addr(struct as_i2c_device *, uint8_t )
{
	return 0;
}

int32_t as_i2c_read_reg(struct as_i2c_device *,
		uint8_t , uint8_t *, size_t )
{
	return 0;
}
int32_t as_i2c_read(struct as_i2c_device *,
		uint8_t *, size_t )
{
	return 0;
}
int32_t as_i2c_write(struct as_i2c_device *,
		uint8_t *, size_t )
{
	return 0;
}
int32_t as_i2c_write_reg_byte(struct as_i2c_device *,
		uint8_t , uint8_t )
{
	return 0;
}
int readRegisterbyte(struct as_i2c_device *, unsigned char , unsigned char *)
{
	return 0;
}



//SPI
int as_spi_open(const unsigned char *)
{
	return 0;
}

void as_spi_close(int )
{
}

uint32_t as_spi_get_speed(int )
{
	return 0;
}

unsigned long long as_spi_msg(int ,
                              unsigned long long ,
                              size_t ,
                              uint32_t )
{
	return 0;
}


//DAC

struct as_dac_device *as_dac_open(const char *, int ,
                                  int , int )
{

}

int32_t as_dac_max5821_power(struct as_dac_device *,
                         char ,
                         AS_max5821_power_mode )
{
	return 0;
}

int32_t as_dac_set_value_in_millivolts(struct as_dac_device *,
                                       int ,
                                       int )
{
	return 0;
}

int32_t as_dac_close(struct as_dac_device *)
{
	return 0;
}




int32_t as_dac_set_value_max5821(struct as_dac_device *,
                                 char ,
                                 int )
{
	return 0;
}





#endif
