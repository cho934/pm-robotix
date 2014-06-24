/*!
 * \file
 * \brief Définition de la classe ServoMotorDxl, gestion des servomotors AX-12.
 */

#ifndef PMX_SERVOMOTORDXL_HPP
#define PMX_SERVOMOTORDXL_HPP

#include "HostGpioPort.hpp"
#include "HostSerialBus.hpp"
#include "LoggerFactory.hpp"
#include "Mutex.hpp"
#include "Utils.hpp"


using namespace utils;

namespace pmx
{
class ServoMotorDxl: public utils::Mutex
{
public:

	/*!
	 * \brief Cette méthode statique retourne l'instance unique de la classe ServoMotorDxl.
	 * \return L'instance unique de la classe.
	 *
	 */
	static ServoMotorDxl & instance()
	{
		static ServoMotorDxl instance;
		return instance;
	}

private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorDxl.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotorDxl");
		return instance;
	}

	utils::HostGpioPort gpio_halfduplex_;

	utils::HostSerialBus serial_;

	static const int BufferSize_ = 1024;

	utils::byte buffer[BufferSize_];

	utils::byte bufferIn[BufferSize_];

	int createReadDataBuffer(int id, int regstart, int readLength);

	//create buffer for write 1 or 2 bytes
	int createWriteDataBuffer(int id, int regstart, int data, int numberOfParameters);

	void setTX();

	void setRX();

	void cleanBuffers();

	ServoMotorDxl();

	~ServoMotorDxl();

	void setCommand(int id, int regstart, int data, int nb2Write);

	long getCommand(int id, int regstart, int readLength);

public:

	long dxlGetTemperature(int id);

	long dxlGetVoltage(int id);

	long dxlGetPos(int id);

	long dxlGetBaud(int id);

	long dxlGetMaxTorqueLimit(int id);

	long dxlGetMaxTorque(int id);

	long dxlGetEnableTorque(int id);

	long dxlGetReturnDelay(int id);

	long dxlGetAcMoving(int id);

	long dxlGetAxLed(int id);

	void dxlSetPos(int id, int pos);

	void dxlSetAxLedOn(int id);

	void dxlSetAxLedOff(int id);

	void dxlSetEnableTorque(int id, int tor);

	void logBf(utils::byte *buffer, int n);
};
}
#endif
