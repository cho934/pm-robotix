/*
 Encoder.cpp - - Interface library for chip LS7366R that does quadrature decoding
 of rotary encoders.  Library for Wiring/Arduino - Version 0017

 Original library     (0.1) by Jeff Bingham.

 More information can be found here:
 http://pendulum.binghamsite.com/rotary-encoders
 */

#include <iostream>
#include "Encoder.hpp"

#include <as_devices/as_gpio.h>
#include <as_devices/as_spi.h>
//#include <linux/spi/spidev.h>

/*
 * Encoder constructor.
 */
Encoder::Encoder(char slave_select_port_letter, int slave_select_pin)
		: ss_port_(slave_select_port_letter), ss_pin_(slave_select_pin)
,gpio_dev_(0), spi_fd_(0)
{
    lock();
	int32_t ret;
	const char *aSpidev_name = "/dev/spidev1.1";
	unsigned char *d = (unsigned char*) aSpidev_name;

	this->counterSize = 4; //n-byte counter
	this->prevStatus = 0; //status register from previous read
	this->prevCount = 0; //count from previous read
	//this->prevTime = millis(); //time stamp of previous read
	this->prevDiff = 0; //difference in coundt from previous read
	//this->ss_pin = slave_select_pin; //slave select pin
	//this->ss_port = slave_select_port_letter;

	// setup the pins on the microcontroller
	gpio_dev_ = as_gpio_open(slave_select_port_letter, slave_select_pin);
	if (gpio_dev_ == NULL)
	{
		printf("Error can't open gpio %c\nHave you run loadgpio.sh ?\n",
				slave_select_port_letter);
		exit(1);
	}
	usleep(1000);
	ret = as_gpio_set_pin_direction(gpio_dev_, 1); //pin Direction (0:in, 1:out) => OUT
	if (ret < 0)
	{
		printf("Error, can't change direction\n");
		exit(1);
	}


	ss_pin_set(1);
	//usleep(1000);

	//setup spi
	spi_fd_ = as_spi_open(d);
	if (spi_fd_ < 0)
	{
		std::cout << "Error, can't open SPI \nHave you run modprobe spidev ?\n"
				<< std::endl;
		exit(0);
	}

	long speed = as_spi_get_speed(spi_fd_);
	std::cout << " Encoder spi speed = " << speed << std::endl;

	//pinMode(this->ss_pin, OUTPUT);
	//digitalWrite(this->ss_pin, HIGH); //delay(10); //disable device
	 unlock();
}

void Encoder::ss_pin_set(int value)
{
	//std::cout << " Encoder  ssp=" << ss_pin_<< " gpiodev="<< gpio_dev_->pin_number << " fd=" << spi_fd_<< std::endl;

	int32_t ret;
	ret = as_gpio_set_pin_value(gpio_dev_, value);
	if (ret < 0)
	{
		printf("Error, can't change pin value\n");
		exit(1);
	}
}

/*
 Initialize the encoder to the SPI with a default free-running 2-byte counter
 */

void Encoder::initialize(void)
{

	//Clear LS7366
	this->clearCounter(); //clear counter
	this->clearStatus(); //clear status

	//Setup LS7366
	/*
	 digitalWrite(this->ss_pin,LOW); //enable device
	 this->spiTransfer(WRITE_MODE0);     //filter divisor=1; async idx; idx off;
	 this->spiTransfer((char)B00000011); //free running cnt; 4x quad cnt
	 digitalWrite(this->ss_pin,HIGH); //release device
	 digitalWrite(this->ss_pin,LOW); //enable device
	 this->spiTransfer(WRITE_MODE1);
	 //  this->spiTransfer((char)B00000011); // 1-byte counter
	 this->spiTransfer((char)B00000010); // 2-byte counter
	 //  this->spiTransfer((char)B00000001); // 3-byte counter
	 //  this->spiTransfer((char)B00000000); // 4-byte counter
	 digitalWrite(this->ss_pin,HIGH); //release device
	 */

	ss_pin_set(0);
	lock();
	this->spiTransfer(WRITE_MODE0);     //filter divisor=1; async idx; idx off;
	this->spiTransfer((char) 0x03); //free running cnt; 4x quad cnt
	unlock();
	ss_pin_set(1);

	ss_pin_set(0);
	lock();
	this->spiTransfer(WRITE_MODE1);
	this->spiTransfer((char) 0x02); // 2-byte counter
	unlock();
	ss_pin_set(1);


}

/*
 Initialize the encoder to the SPI with your own desired parameters
 */

void Encoder::initialize(int setup_mdr0, int setup_mdr1)
{

	//this->counterSize = (4 - (((byte)setup_mdr1) & 0x03)); //n-byte counter
	this->counterSize = (4 - (((BYTE) setup_mdr1) & 0x03)); //n-byte counter

	//Clear LS7366
	this->clearCounter(); //clear counter
	this->clearStatus(); //clear status
	/*
	 //Setup LS7366
	 digitalWrite(this->ss_pin,LOW); //enable device
	 this->spiTransfer(WRITE_MODE0);
	 this->spiTransfer((char)setup_mdr0);
	 digitalWrite(this->ss_pin,HIGH); //release device
	 digitalWrite(this->ss_pin,LOW); //enable device
	 this->spiTransfer(WRITE_MODE1);
	 this->spiTransfer((char)setup_mdr1);
	 digitalWrite(this->ss_pin,HIGH); //release device*/
	lock();
	ss_pin_set(0);
	this->spiTransfer(WRITE_MODE0);
	this->spiTransfer((char) setup_mdr0);
	ss_pin_set(1);

	ss_pin_set(0);
	this->spiTransfer(WRITE_MODE1);
	this->spiTransfer((char) setup_mdr1);
	ss_pin_set(1);
	unlock();
}

/*
 Used for transferring all data along the SPI
 */
char Encoder::spiTransfer(char data) //volatile
{

	/*
	 SPDR = data;                    // Start the transmission
	 //  delayMicroseconds(10);        // Might be required for IC timing
	 while (!(SPSR & (1<<SPIF)))     // Wait for end of the transmission
	 {
	 };
	 return SPDR;                    // return the received byte*/

	unsigned long long result = as_spi_msg(spi_fd_, (unsigned long long) data, 8,
			6000000);

	return result;

}

/*
 Used for clearing the counter
 */
void Encoder::clearCounter(void)
{
	lock();
	ss_pin_set(0); //enable device
	this->spiTransfer(CLEAR_COUNTER); //transmit clear opcode
	ss_pin_set(1); //release device
	unlock();
}

/*
 Used for clearing the Status
 */
void Encoder::clearStatus(void)
{
	lock();
	ss_pin_set(0); //enable device
	this->spiTransfer(CLEAR_STATUS); //transmit clear opcode
	ss_pin_set(1); //release device
	unlock();
}

/*
 Used for reading the counter
 */
unsigned long Encoder::readCounter(void)
{
	lock();
	unsigned char data;
	unsigned long returnVal = 0;
	ss_pin_set(0);
	this->spiTransfer(READ_COUNTER);
	for (char i = this->counterSize; i > 0; i--)
	{
		data = this->spiTransfer(0x00);
		returnVal = returnVal * 255 + data;
	}
	unlock();
	return returnVal;
}

/*
 Used for reading the status
 */
unsigned char Encoder::readStatus(void)
{
	lock();
	unsigned char data;
	ss_pin_set(0); //enable device
	this->spiTransfer(READ_STATUS); //transmit read opcode
	data = this->spiTransfer(0xFF); //get data byte
	ss_pin_set(1); //release device
	unlock();
	return data;
}

/*
 unsigned long long as_spi_read4byte(int aFd,
 unsigned long long aMsg,
 size_t aLen,
 uint32_t aSpeed)
 {
 struct spi_ioc_transfer xfer;
 memset(&xfer, 0, sizeof(xfer));
 char dataBuffer[3];
 char rxBuffer[3];
 dataBuffer[0] = 0x0B;
 dataBuffer[1] = 0x02;
 dataBuffer[2] = 0x00;
 xfer.tx_buf = (unsigned long)dataBuffer;
 xfer.rx_buf = (unsigned long)rxBuffer;
 xfer.len = 3;
 xfer.speed_hz = 500000;
 xfer.cs_change = 1;
 xfer.bits_per_word = 8;
 res = ioctl(spiDev, SPI_IOC_MESSAGE(1), &xfer);
 printf("SPI result: %d\n", res);
 printf("Device ID: %d - %d - %d\n", rxBuffer[2], rxBuffer[1], rxBuffer[0]);
 }
 */
