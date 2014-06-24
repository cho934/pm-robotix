#ifdef SIMU
#ifndef AS_I2C_H
#define AS_I2C_H


#include <stdint.h>
#include <sys/types.h>

extern "C"
{


struct as_i2c_device {

};

/** @brief Open an I2C bus.
 */
struct as_i2c_device *as_i2c_open(int aBusNumber);

/** @brief Close an I2C device.
 */
int32_t as_i2c_close(struct as_i2c_device *aDev);

/** @brief Set chip's I2C slave address
 */
int32_t as_i2c_set_slave_addr(struct as_i2c_device *aDev, uint8_t aAddr);

/** @brief Set chip's I2C slave address
 */
int32_t as_i2c_get_slave_addr(struct as_i2c_device *aDev);

/** @brief Read several bytes (ioctl() method) from given chip.
 */
int32_t as_i2c_read(struct as_i2c_device *aDev,
                    uint8_t *aData, size_t n);

/** @brief Write several bytes (ioctl() method) to given chip.
 */
int32_t as_i2c_write(struct as_i2c_device *aDev,
                     uint8_t *aData, size_t n);

/** @brief Read from given chip at a given register address (ioctl() method).
 */


int32_t as_i2c_read_reg(struct as_i2c_device *aDev,
                        uint8_t aReg, uint8_t *aData, size_t n);

/** @brief Write to given chip at a given register address (ioctl() method).
 */
int32_t as_i2c_write_reg(struct as_i2c_device *aDev,
                         uint8_t aReg, const uint8_t *aData, size_t n);

/** @brief forge a read message like this:
 * S Addr[W] wdata0 [A] wdata1 [A] ... RS Addr R [rdata0] A [rdata1] A ... P
 */
int32_t as_i2c_read_msg(struct as_i2c_device *aDev,
                          uint8_t *aWData, uint8_t aWriteSize,
                          uint8_t *aRData, size_t aReadSize);

/** @brief Read a byte from the given register.
 */
int32_t as_i2c_read_reg_byte(struct as_i2c_device *aDev, uint8_t aReg);

/** @brief Write a byte to the given register.
 */
int32_t as_i2c_write_reg_byte(struct as_i2c_device *aDev,
                              uint8_t aReg, uint8_t aVal);


}
#endif
#endif


