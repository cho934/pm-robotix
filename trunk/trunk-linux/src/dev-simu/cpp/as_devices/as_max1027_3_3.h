#ifdef SIMU
#ifndef AS_MAX1027_H
#define	AS_MAX1027_H

#define AS_max1027_mode int

#include <stdint.h>
#include <sys/types.h>

extern "C"
{
#define AS_MAX1027_SLOW 0

    struct as_max1027_device
    {
    };

    /** @brief Open max1027
     *
     * @param aSpiNum spi bus number used
     * @param aMode enum to set mode (fast or slow)
     *
     * @return as_max1027_device structure pointer, NULL if error
     */
    struct as_max1027_device *as_max1027_open(int aSpiNum,
                                              AS_max1027_mode aMode);

    /** @brief set averaging measurement
     *
     * @param as_max1027_device structure pointer.
     * @param aNbConv number of conversions to do for the averaging (4, 8, 16, 32). Set to 1 for disabling averaging.
     *
     * @return negative value on error and aNbConv on success
     */
    int32_t as_max1027_set_averaging_3_3(struct as_max1027_device *aDev, uint8_t aNbConv);

    /** @brief read temperature in milidegree ⁰C
     *
     * @param as_max1027_device structure pointer.
     * @param aTemperature pointer for temperature result.
     *
     * @return negative value on error
     *
     * @note Only slow mode can read temperature value.
     */
    int32_t as_max1027_read_temperature_mC(struct as_max1027_device *aDev,
                                           int *aTemperature);

    /** @brief read milivoltage value
     *
     * @param as_max1027_device structure pointer.
     * @param aChannelNum channel number to read.
     * @param *aValue pointer to returned value.
     *
     * @return negative value on error
     */
    int32_t as_max1027_get_value_milliVolt(struct as_max1027_device *aDev,
                                           int aChannelNum,
                                           int *aValue);

    /** @brief Close max1027
     *
     * @param aDev structure device pointer
     *
     * @return negative value on error
     */
    int32_t as_max1027_close(struct as_max1027_device *aDev);


}
#endif
#endif
