#ifdef SIMU
#ifndef AS_MAX5821_H
#define	AS_MAX5821_H

extern "C"
{
//#define MAX5821_POWER_UP 0

struct as_max5821_device {
    //struct as_i2c_device *i2c_dev;
};


typedef enum {
    MAX5821_POWER_UP         = 0,
    MAX5821_POWER_DOWN_MODE0,
    MAX5821_POWER_DOWN_MODE1,
    MAX5821_POWER_DOWN_MODE2
} AS_max5821_power_mode;

/** @brief Open max5821
 *
 * @param aI2cBus i2c bus number
 * @param aI2cAddress i2c chip address
 * @param aVRef reference voltage
 * @param aVDefault voltage required when device opened
 *
 * @return as_max5821_device structure on success, NULL on error
 */
struct as_dac_device *as_dac_open_max5821(int aI2cBus,
                                          int aI2cAddress,
                                          int aVRef);
/** @brief Power a channel
 *
 * @param aDev pointer to device structure
 * @param aChannel caracter to channel
 * @param aPowerCmd power command
 *
 * @return negative value on header.
 */
int32_t as_dac_max5821_power(struct as_dac_device *aDev,
                         char aChannel,
                         AS_max5821_power_mode aMode);

/** @brief set output value
 *
 * @param aDev pointer to device structure
 * @param aChannel caracter to channel
 * @param aValue value between 0 and 1023
 *
 * @return negative value on error.
 */
int32_t as_dac_set_value_max5821(struct as_dac_device *aDev,
                                 char aChannel,
                                 int aValue);

/** @brief set both output value
 *
 * @param aDev pointer to device structure
 * @param aValue value between 0 and 1023
 *
 * @return negative value on error
 */
int32_t as_max5821_set_both_value(struct as_dac_device *aDev,
                                  int aValue);

/** @brief Close max5821
 *
 * @param aDev structure device pointer
 *
 * @return negative value on error
 */
int32_t as_dac_close_max5821(struct as_dac_device *aDev);
}

#endif
#endif
