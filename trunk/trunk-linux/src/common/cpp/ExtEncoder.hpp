/*!
 * \file
 * \brief Définition de la classe ExtEncoder.
 */

// ensure this library description is only included once
#ifndef PMX_EXTENCODER_HPP
#define PMX_EXTENCODER_HPP

#include "../../common/cpp/ARobotElement.hpp"
#include "../../common/cpp/LoggerFactory.hpp"
#include "../../common/cpp/Mutex.hpp"
#include "../../common/cpp/HostSpiBus.hpp"
#include "../../common/cpp/HostGpioPort.hpp"

// define some LS7366R Op-codes
#define CLEAR_COUNTER 32 //=0x20
#define CLEAR_STATUS 48 //=0x30
#define READ_COUNTER 96 //=0x60
#define READ_STATUS 112 //=0x70
#define WRITE_MODE0 136 //=0x88
#define WRITE_MODE1 144 //=0x90

typedef unsigned char BYTE; /* 8-bit data */

namespace pmx
{
/*!
 * \brief Implémentation des encoders externes associée au robot.
 */
class ExtEncoder: utils::Mutex, public ARobotElement
{
private:
	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ExtEncoder.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ExtEncoder");
		return instance;
	}

	char ss_port_;
	int ss_pin_; //slave select pin

	/*!
	 * \brief gpio à utiliser.
	 */
	utils::HostGpioPort * gpio_;

	unsigned char counterSize; //n-byte counter
	unsigned char prevStatus; //status register from previous read
	unsigned long prevCount; //count from previous read
	long prevDiff; //difference in count from previous read

public:
	/*!
	 * \brief Constructeur de la classe.
	 */
	ExtEncoder(pmx::Robot & robot, char slave_select_port_letter, int slave_select_pin);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~ExtEncoder()
	{
		try
		{
			gpio_->closeIoctl();
		} catch (utils::Exception * e)
		{
			logger().error() << "Exception : " << e->what() << utils::end;
		}
	}

	/*
	 * \brief Methods for initializing the encoder through the SPI.
	 */
	void initialize(int setup_mdr0, int setup_mdr1);

	/*
	 * \brief Method for getting number of counts.
	 */
	unsigned long readCounter(void);

	/*
	 * \brief Method for determining the status of the IC.
	 */
	unsigned char readStatus(void);

	/*
	 * \brief Method for clearing the counter.
	 */
	void clearCounter(void);

	/*
	 * \brief Method for clearing the status register.
	 */
	void clearStatus(void);

private:
	char spiTransfer(char data);
	void ss_pin_set(int value);

};
}

#endif

