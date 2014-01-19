#ifdef SIMU
#ifndef AS_MAX5821_H
#define	AS_MAX5821_H

extern "C"
{
#define MAX5821_POWER_UP 0

    struct as_max5821_device
    {
    };

    as_max5821_device* as_max5821_open(int, int);

    int as_max5821_close(as_max5821_device* device);

    int as_max5821_power(as_max5821_device*, char, int);

    int as_max5821_set_one_value(as_max5821_device*, char, int);
}

#endif
#endif
