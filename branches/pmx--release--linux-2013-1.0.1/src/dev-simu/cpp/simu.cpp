#ifdef SIMU

/*!
 * \file
 * \brief Implements all the fake methods in order to provide compatibility with
 * the armadeus system.
 */

#include <as_devices/as_gpio.h>
#include <as_devices/as_i2c.h>
#include <as_devices/as_max1027.h>
#include <as_devices/as_max5821.h>
#include <native/intr.h>
#include <native/task.h>

as_gpio_device* as_gpio_open(char, int)
{
    return new as_gpio_device();
}

void as_gpio_close(as_gpio_device* device)
{
    delete device;
}

void as_gpio_set_pin_value(as_gpio_device*, int)
{
}

int as_gpio_get_pin_value(as_gpio_device*)
{
    return 0;
}

void as_gpio_set_irq_mode(as_gpio_device*, int)
{
}

int as_gpio_blocking_get_pin_value(as_gpio_device*, int, int)
{
    return 0;
}

int as_i2c_read_reg(int, uint8_t, int, uint8_t* buffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        buffer[i] = 0;
    }

    return 0;
}

int as_i2c_close(int)
{
    return 0;
}

int as_i2c_open(int)
{
    return 0;
}

int as_i2c_set_slave(int, uint8_t)
{
    return 0;
}

int as_i2c_read_reg_byte(int, uint8_t, uint8_t)
{
    return 0;
}

int as_i2c_write_reg_byte(int, uint8_t, uint8_t, uint8_t)
{
    return 0;
}

as_max1027_device* as_max1027_open(int, int)
{
    return new as_max1027_device();
}

int as_max1027_close(as_max1027_device* device)
{
    delete device;
    return 0;
}

int as_max1027_set_averaging(as_max1027_device*, int)
{
    return 0;
}

int as_max1027_get_value_milliVolt(as_max1027_device*, int, int*)
{
    return 0;
}

int as_max1027_read_temperature_mC(as_max1027_device *, int*)
{
    return 0;
}

as_max5821_device* as_max5821_open(int, int)
{
    return new as_max5821_device();
}

int as_max5821_close(as_max5821_device* device)
{
    delete device;
    return 0;
}

int as_max5821_power(as_max5821_device*, char, int)
{
    return 0;
}

int as_max5821_set_one_value(as_max5821_device*, char, int)
{
    return 0;
}

int rt_intr_enable(int*)
{
    return 0;
}

int rt_intr_wait(int*, int)
{
    return 0;
}

int rt_intr_create(int*, const char*, int, int)
{
    return 0;
}

void rt_intr_delete(int*)
{
}

int rt_task_create(int*, const char*, int, int, int)
{
    return 0;
}

void rt_task_start(int*, void(*)(void*), void*)
{
}

void rt_task_delete(int*)
{
}

#endif
