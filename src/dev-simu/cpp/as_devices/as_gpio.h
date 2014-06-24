#ifdef SIMU
#ifndef AS_GPIO_H
#define AS_GPIO_H

#include <stdint.h>

extern "C"
{

struct as_gpio_device {
    int port_num;
    char port_letter;
    int pin_number;
    int fpin;       /* pin file for 2.6.29 interface*/
    int irq_mode;
};

    as_gpio_device* as_gpio_open(char, int);


    int32_t as_gpio_set_pin_direction(struct as_gpio_device *aDev,
                                      int aDirection);

    int32_t as_gpio_set_pin_value(struct as_gpio_device *aDev,
                                  int aValue);

    int32_t as_gpio_close(struct as_gpio_device *aDev);

    int32_t as_gpio_blocking_get_pin_value(struct as_gpio_device *aDev,
                                           int aDelay_s,
                                           int aDelay_us);

    int32_t as_gpio_get_pin_value(struct as_gpio_device *aDev);



}

#endif
#endif
