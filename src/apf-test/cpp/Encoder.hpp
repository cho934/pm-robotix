

// ensure this library description is only included once
#ifndef Encoder_h
#define Encoder_h

#include <as_devices/as_gpio.h>
#include <as_devices/as_spi.h>
#include <cstdio>
#include <cstdlib>

#include "../../common/cpp/Mutex.hpp"

// define some LS7366R Op-codes
#define CLEAR_COUNTER 32 //=0x20
#define CLEAR_STATUS 48 //=0x30
#define READ_COUNTER 96 //=0x60
#define READ_STATUS 112 //=0x70
#define WRITE_MODE0 136 //=0x88
#define WRITE_MODE1 144 //=0x90

typedef unsigned char BYTE; /* 8-bit data */

// library interface description
class Encoder : public utils::Mutex
{
private:

	char ss_port_;
	int ss_pin_; //slave select pin
	struct as_gpio_device *gpio_dev_;
	int spi_fd_;

	unsigned char counterSize; //n-byte counter
	unsigned char prevStatus; //status register from previous read
	unsigned long prevCount; //count from previous read
	//long prevTime; //time stamp of previous read
	long prevDiff; //difference in coundt from previous read

public:
	// constructors:
	Encoder(char slave_select_port_letter, int slave_select_pin);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~Encoder()
	{
		as_spi_close(spi_fd_);

		int ret = as_gpio_close(gpio_dev_);
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

	void ss_pin_set(int value);
private:
	// Method for talking to IC over SPI
	char spiTransfer( char data); //volatile





};

#endif

