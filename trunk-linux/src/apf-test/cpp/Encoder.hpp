

// ensure this library description is only included once
#ifndef Encoder_h
#define Encoder_h

#include <as_devices/as_gpio.h>
#include <as_devices/as_spi.h>

// define some LS7366R Op-codes
#define CLEAR_COUNTER 32
#define CLEAR_STATUS 48
#define READ_COUNTER 96
#define READ_STATUS 112
#define WRITE_MODE0 136
#define WRITE_MODE1 144

typedef unsigned char BYTE; /* 8-bit data */

// library interface description
class Encoder
{
public:
	// constructors:
	Encoder(char slave_select_port_letter, int slave_select_pin);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~Encoder()
	{
		as_spi_close(spi_fd);

		int ret = as_gpio_close(gpio_dev);
		if(ret < 0)
		{
			printf("Error, can't close gpio\n");
			exit(1);
		}
	}

	// Methods for initializing the encoder through the SPI
	void initialize(void);
	void initialize(int setup_mdr0, int setup_mdr1);

	// Method for getting number of counts
	unsigned long readCounter(void);

	// Method for determining the status of the IC
	unsigned char readStatus(void);

	// Method for clearing the counter
	void clearCounter(void);

	// Method for clearing the status register
	void clearStatus(void);

private:
	// Method for talking to IC over SPI
	char spiTransfer(volatile char data);
	void ss_pin_set(int value);

	char ss_port;
	int ss_pin; //slave select pin

	unsigned char counterSize; //n-byte counter
	unsigned char prevStatus; //status register from previous read
	unsigned long prevCount; //count from previous read
	//long prevTime; //time stamp of previous read
	long prevDiff; //difference in coundt from previous read


	struct as_gpio_device *gpio_dev;
	int spi_fd;
};

#endif

