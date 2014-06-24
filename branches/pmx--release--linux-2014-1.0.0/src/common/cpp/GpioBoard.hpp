/*!
 * \file
 * \brief Définition de la classe GpioBoard.
 * Program for the 12C PCA9555 Board part number DFR0013 IIC TO GPIO module from dfrobot.com
 * 16 outputs that I used to drive this relay board made in Bulgaria
 * http://www.denkovi.com/product/21/16-relay-board-for-your-pic-avr-project-12v.html
 */

#ifndef PMX_GPIOBOARD_HPP
#define PMX_GPIOBOARD_HPP

#include "ARobotElement.hpp"
#include "HostI2cBus.hpp"
#include "LoggerFactory.hpp"
#include "Macro.hpp"

//  with no jumpers the full address is   1 0 0 1 1 1    1 0 0 A2 A1 A0  0x27 is the default address for the DFR0013 board with no jumpers.
// 0x27 is default address for the DFR0013 board with no jumpers.
// 0x20 is address for the DFR0013 board with all jumpers.
#define GPIOBOARD_PCA9555		 0x24


// COMMAND BYTE TO REGISTER RELATIONSHIP FROM PCA9555 DATA SHEET
// At reset, the device's ports are inputs with a high value resistor pull-ups to VDD
// If relays turning on during power up are a problem. Add a pull down resistor to each relay transistor base.
#define IN_P0 			0x00 // Read Input port0
#define IN_P1 			0x01 // Read Input port1
#define OUT_P0 		0x02 // Write Output port0
#define OUT_P1 		0x03 // Write Output port1
#define INV_P0 			0x04 // Input Port Polarity Inversion port0 if B11111111 is written input polarity is inverted
#define INV_P1 			0x05 // Input Port Polarity Inversion port1 if B11111111 is written input polarity is inverted
#define CONFIG_P0 	0x06 // Configuration port0 configures the direction of the I/O pins 0 is output 1 is input
#define CONFIG_P1 	0x07 // Configuration port1 configures the direction of the I/O pins 0 is output 1 is input

#define PAUSE 200000 //us

namespace pmx
{
/*!
 * \brief Implementation for the 12C PCA9555 Board part number DFR0013 IIC TO GPIO module from dfrobot.com.
 */
class GpioBoard: public ARobotElement
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref GpioBoard.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::GpioBoard");
		return instance;
	}

	bool connected_;

	utils::HostI2cBus i2cGB_;

	int port0Value_;
	int port1Value_;

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	GpioBoard(pmx::Robot & robot);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~GpioBoard()
	{
	}

	void begin();

	bool isConnected()
	{
		return connected_;
	}

	int getValueP1(int pin);
	void setValueP0(int port, int pin, int value);
	void setOnP0(int pin);
	void setOffP0(int pin);
	void setup();
private:

	void write_i2c(uchar command, uchar value);
	uchar read_i2c(uchar command);

};
}

#endif
