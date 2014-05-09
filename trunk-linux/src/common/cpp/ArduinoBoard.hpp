/*!
 * \file
 * \brief Définition de la classe ArduinoBoard.
 */

#ifndef PMX_ARDUINOBOARD_HPP
#define PMX_ARDUINOBOARD_HPP

#include "ARobotElement.hpp"
#include "HostI2cBus.hpp"
#include "LoggerFactory.hpp"

//#define ARDUINOBOARD_ADDR	 0x2A  // (0x2A = 42)

namespace pmx
{
/*!
 * \brief Implementation to communicate with an arduino.
 */
class ArduinoBoard: public ARobotElement
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ArduinoBoard.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ArduinoBoard");
		return instance;
	}

	bool connected_;

	int addr_;

	utils::HostI2cBus ardui_i2c_;

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ArduinoBoard(pmx::Robot & robot, int addr);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~ArduinoBoard()
	{
	}

	void init();

	bool isConnected()
	{
		return connected_;
	}

	int launchCmd(const char command[3], const char identifier[5]);

private:

	void writeI2c_3Bytes(const char *buf);
	int readI2c_1Byte();

};
}

#endif
