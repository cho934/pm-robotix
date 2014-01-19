#ifdef SIMU
#ifndef AS_I2C_H
#define AS_I2C_H

#define uint8_t unsigned int

extern "C"
{
    int as_i2c_read_reg(int, uint8_t, int, uint8_t*, int);

    int as_i2c_close(int);

    int as_i2c_open(int);

    int as_i2c_set_slave(int, uint8_t);

    int as_i2c_read_reg_byte(int, uint8_t, uint8_t);

    int as_i2c_write_reg_byte(int, uint8_t, uint8_t, uint8_t);
}
#endif
#endif


