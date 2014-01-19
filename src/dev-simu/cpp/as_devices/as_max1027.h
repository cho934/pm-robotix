#ifdef SIMU
#ifndef AS_MAX1027_H
#define	AS_MAX1027_H

#define AS_max1027_mode int

extern "C"
{
#define AS_MAX1027_SLOW 0

    struct as_max1027_device
    {
    };

    as_max1027_device* as_max1027_open(int, int);

    int as_max1027_close(as_max1027_device* device);

    int as_max1027_set_averaging(as_max1027_device*, int);

    int as_max1027_get_value_milliVolt(as_max1027_device*, int, int*);

    int as_max1027_read_temperature_mC(as_max1027_device *, int*);
}
#endif
#endif
