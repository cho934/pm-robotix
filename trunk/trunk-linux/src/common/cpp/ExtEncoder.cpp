/*!
 * \file
 * \brief Implémentation de la classe ExtEncoder.
 * Interface library for chip LS7366R that does quadrature decoding of rotary encoders.
 */

#include <iostream>
#include "ExtEncoder.hpp"
#include "HostGpioPort.hpp"

/*!
 * External Encoder constructor.
 */
pmx::ExtEncoder::ExtEncoder(pmx::Robot & robot, char slave_select_port_letter, int slave_select_pin)
		: ARobotElement(robot), ss_port_(slave_select_port_letter), ss_pin_(slave_select_pin)
{
	gpio_ = new utils::HostGpioPort();

	//lock();

	logger().debug() << "ss_port_=" << ss_port_<< " ss_pin_=" << ss_pin_ << utils::end;
	try
	{
		gpio_->openIoctl(ss_port_, ss_pin_);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception ExtEncoder::ExtEncoder: " << e->what() << utils::end;
	}

	try
	{
		gpio_->setDirIoctl(1);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception ExtEncoder::ExtEncoder: " << e->what() << utils::end;
	}

	this->counterSize = 4; //n-byte counter
	this->prevStatus = 0; //status register from previous read
	this->prevCount = 0; //count from previous read
	this->prevDiff = 0; //difference in coundt from previous read

	ss_pin_set(1);
	logger().debug() << "ss_pin_set(1); ok "  << utils::end;

	try
	{
		logger().debug() << "test0003 "  << utils::end;
		utils::HostSpiBus::instance().open();
		long speed = utils::HostSpiBus::instance().getSpeed();
		std::cout << " Encoder spi speed = " << speed << std::endl;
		logger().debug() << "test0004 "  << utils::end;
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception ExtEncoder::ExtEncoder: " << e->what() << utils::end;
	}
	//unlock();
	logger().debug() << "test0005 "  << utils::end;
	//init MDR0  and MDR1
	this->initialize(0x00, 0x00); //x4 and 4 bytes
	logger().debug() << "test0006 "  << utils::end;
	usleep(1000);

}

void pmx::ExtEncoder::ss_pin_set(int value)
{
	try
	{
		gpio_->setValueIoctl(value);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception ExtEncoder::ss_pin_set: " << e->what() << utils::end;
	}
}

/*!
 Initialize the encoder to the SPI with your own desired parameters
 */
void pmx::ExtEncoder::initialize(int setup_mdr0, int setup_mdr1)
{
	this->counterSize = (4 - (((BYTE) setup_mdr1) & 0x03)); //n-byte counter

	//Clear LS7366
	this->clearCounter(); //clear counter
	this->clearStatus(); //clear status

	lock();
	ss_pin_set(0);
	this->spiTransfer(WRITE_MODE0);
	this->spiTransfer((char) setup_mdr0);
	//ss_pin_set(1);
	//usleep(1000);
	//ss_pin_set(0);
	this->spiTransfer(WRITE_MODE1);
	this->spiTransfer((char) setup_mdr1);
	ss_pin_set(1);
	unlock();
}

/*!
 Used for transferring all data along the SPI
 */
unsigned long long pmx::ExtEncoder::spiTransfer(char data)
{
	unsigned long long result = utils::HostSpiBus::instance().spiTransfer(data);
	return result;
}

/*!
 Used for clearing the counter
 */
void pmx::ExtEncoder::clearCounter(void)
{
	lock();
	ss_pin_set(0); //enable device
	this->spiTransfer(CLEAR_COUNTER); //transmit clear opcode
	ss_pin_set(1); //release device
	unlock();
}

/*!
 Used for clearing the Status
 */
void pmx::ExtEncoder::clearStatus(void)
{
	lock();
	ss_pin_set(0); //enable device
	this->spiTransfer(CLEAR_STATUS); //transmit clear opcode
	ss_pin_set(1); //release device
	unlock();
}

/*!
 Used for reading the counter
 */
unsigned long long pmx::ExtEncoder::readCounter(void)
{
	readStatus(); //read status before read otherwise it doesn't work

	lock();
	unsigned long long data;
	unsigned long long returnVal = 0;
	ss_pin_set(0);
	this->spiTransfer(READ_COUNTER);

	for (char i = this->counterSize; i > 0; i--)
	{
		data = this->spiTransfer(0x00);
		returnVal = returnVal * 255 + data;
	}
	ss_pin_set(1); //release device
	unlock();
	return returnVal;
}

/*!
 Used for reading the status
 */
unsigned char pmx::ExtEncoder::readStatus(void)
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
