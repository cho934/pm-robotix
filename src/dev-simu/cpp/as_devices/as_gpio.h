#ifdef SIMU
#ifndef AS_GPIO_H
#define AS_GPIO_H

extern "C"
{
#define GPIO_IRQ_MODE_RISING 0
#define GPIO_IRQ_MODE_FALLING  0

    struct as_gpio_device
    {
    };

    as_gpio_device* as_gpio_open(char, int);

    void as_gpio_close(as_gpio_device* device);

    void as_gpio_set_pin_value(as_gpio_device*, int);

    int as_gpio_get_pin_value(as_gpio_device*);

    void as_gpio_set_irq_mode(as_gpio_device*, int);

    int as_gpio_blocking_get_pin_value(as_gpio_device*, int, int);
}

#endif
#endif
