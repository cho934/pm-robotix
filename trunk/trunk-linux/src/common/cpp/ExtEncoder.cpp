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
	try
	{
		gpio_ = new utils::HostGpioPort();

		logger().debug() << "ss_port_=" << ss_port_ << " ss_pin_=" << ss_pin_ << utils::end;

		gpio_->openIoctl(ss_port_, ss_pin_);
		gpio_->setDirIoctl(1);

		this->counterSize = 4; //n-byte counter
		this->prevStatus = 0; //status register from previous read
		this->prevCount = 0; //count from previous read
		this->prevDiff = 0; //difference in coundt from previous read

		ss_pin_set(1);

		utils::HostSpiBus::instance().open();
		long speed = utils::HostSpiBus::instance().getSpeed();
		std::cout << " Encoder spi speed = " << speed << std::endl;

		//singleByteWrite(WRITE_MDR0, QUADRX4|FREE_RUN|INDX_LOADC|SYNCH_INDX|FILTER_2);
		//singleByteWrite(WRITE_MDR1, IDX_FLAG|CMP_FLAG|BYTE_2|EN_CNTR);

		//init MDR0  and MDR1
		int mdr0 = QUADRX4 | FREE_RUN | DISABLE_INDX | ASYNCH_INDX | FILTER_1;
		int mdr1 = NO_FLAGS | EN_CNTR | BYTE_4;
		logger().debug() << "MDR0=" << reinterpret_cast<void*>(mdr0) << "\t MDR1=" << reinterpret_cast<void*>(mdr1)
				<< utils::end;
		this->setup(mdr0, mdr1);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception ExtEncoder::ExtEncoder: " << e->what() << utils::end;
	}
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
void pmx::ExtEncoder::setup(int setup_mdr0, int setup_mdr1)
{
	this->counterSize = (4 - (((BYTE) setup_mdr1) & 0x03)); //n-byte counter

	//Clear LS7366
	this->clearCounter(); //clear counter
	this->clearStatus(); //clear status

	lock();
	ss_pin_set(0);
	this->spiTransfer(WRITE_MODE0);
	this->spiTransfer((char) setup_mdr0);

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
long long pmx::ExtEncoder::readCounter(void)
{
	readStatus(); //read status before read otherwise it doesn't work
	long long counter = 0;
	unsigned long long data = 0;
	unsigned long long fulldata = 0;

	lock();
	ss_pin_set(0);
	this->spiTransfer(READ_COUNTER);

	for (char i = this->counterSize; i > 0; i--)
	{
		data = this->spiTransfer(0x00);
		fulldata = fulldata * 255 + data;
	}
	ss_pin_set(1); //release device
	unlock();

	//logger().debug() << "fulldata =  " << fulldata << utils::end;

	if (fulldata > 4244897280 / 2)
	{
		counter = -(((long long) 4244897280) - fulldata);
	}
	else
	{
		counter = fulldata;
	}
	return counter;
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
