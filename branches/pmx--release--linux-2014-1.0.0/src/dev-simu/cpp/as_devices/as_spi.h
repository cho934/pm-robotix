#ifdef SIMU
#ifndef AS_SPI_H
#define AS_SPI_H


extern "C"
{



#include <inttypes.h>
#include <sys/types.h>

/** @brief Open a SPI bus.
 *
 * @param aSpidev_name path name
 *
 * @return the file descriptor of the opened device, -1 on error
 */
int as_spi_open(const unsigned char *aSpidev_name);

/** @brief Set bits order
 *
 * @param aFd spidev file handler
 * @param aLsb if 1 lsb first, else msb first
 *
 * @return lsb first if positive, msb first if 0, negative value on error
 * TODO : test it
 */
int as_spi_set_lsb(int aFd, uint8_t aLsb);

/** @brief Get bits order
 *
 * @param aFd spidev file handler
 *
 * @return lsb first if positive, msb first if 0, negative value on error
 * TODO : test it
 */
int as_spi_get_lsb(int aFd);

/** @brief Set spi bus mode
 *
 * @param aFd spidev file handler
 * @param aMode
 *
 * @return mode if positive value, negative value on error
 * TODO: test it
 */
int as_spi_set_mode(int aFd, uint8_t aMode);

/** @brief Get spi bus mode
 *
 * @param aFd spidev file handler
 *
 * @return mode if positive value, negative value on error
 * TODO: test it
 */
int as_spi_get_mode(int aFd);

/** @brief Set clock bus speed
 *
 * @param aFd spidev file handler
 * @param aSpeed clock speed
 *
 * @return speed in Hz, negative value on error
 */
int as_spi_set_speed(int aFd, uint32_t aSpeed);

/** @brief Get clock bus speed
 *
 * @param aFd spidev file handler
 *
 * @return speed in Hz
 */
uint32_t as_spi_get_speed(int aFd);

/** @brief Get bits per word
 *
 * @param aFd spidev file handler
 *
 * @return bit per word if positive value, negative value on error
 */
int as_spi_get_bits_per_word(int aFd);

/** @brief Set bits per word
 *
 * @param aFd spidev file handler
 * @param aBits number of bits per word
 *
 * @return bit per word if positive value, negative value on error
 * TODO : test it
 */
int as_spi_set_bits_per_word(int aFd, uint8_t aBits);

/** @brief Forge arbitrary length message (31bits max) and send it
 *
 * @param aFd spidev file handler
 * @param aMsg right adjusted message
 * @param aLen lenght of the message
 * @param aSpeed clock speed in Hz
 *
 * @return message read
 */
unsigned long long as_spi_msg(int aFd,
                              unsigned long long aMsg,
                              size_t aLen,
                              uint32_t aSpeed);

/** @brief Close a SPI bus.
 *
 * @param aFd file descriptor of SPI bus used
 *
 */
void as_spi_close(int aFd);

}
#endif
#endif


