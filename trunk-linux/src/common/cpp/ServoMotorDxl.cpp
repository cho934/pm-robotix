/*!
 * \file
 * \brief Implémentation de la classe ServoMotorDxl.
 */

#include "stdio.h"
#include <string.h>

#include "ServoMotorDxl.hpp"
#include "Exception.hpp"
#include "Chronometer.hpp"
#include "HostSerialBus.hpp"
#include "HostGpioPort.hpp"
#include "Utils.hpp"


pmx::ServoMotorDxl::ServoMotorDxl()
{
	cleanBuffers();
	gpio_halfduplex_.openIoctl('C', 3);
	gpio_halfduplex_.setDirIoctl(1);

	if (serial_.connect() <= 0)
	{
		printf("Can't open serial port\n");
		//TODO ERROR exception
	}
	else
	{
		printf("Serial port opened\n");
	}
	setRX();
	usleep(2000);
}

pmx::ServoMotorDxl::~ServoMotorDxl()
{
	//TODO create dxl close function
	serial_.disconnect();
	gpio_halfduplex_.closeIoctl();
}

void pmx::ServoMotorDxl::cleanBuffers()
{
	memset(buffer, 0, BufferSize_);
	memset(bufferIn, 0, BufferSize_);
}

/** helper functions to switch direction of comms */
void pmx::ServoMotorDxl::setTX()
{
	gpio_halfduplex_.setValueIoctl(Tx_MODE);
}

void pmx::ServoMotorDxl::setRX()
{
	gpio_halfduplex_.setValueIoctl(Rx_MODE);
}
//return 0 if ok , TODO -1 otherwise
void pmx::ServoMotorDxl::setCommand(int id, int regstart, int data, int nb2Write)
{
	//int error = -1;
	int statuserror = 0;
	utils::Chronometer chrono;
	lock();

	cleanBuffers();

	int n = createWriteDataBuffer(id, regstart, data, nb2Write);
	chrono.start();
	setTX(); //No log until setRX !!
	int err = serial_.sendArray(buffer, n);

	if (err < 0 || err != n)
	{
		std::cout << "ERROR setInfo serial_.sendArray()" << err << std::endl;
		logBf(buffer, n); //Log
	}
	else
	{

		//Wait the command to be sent
		while (chrono.getElapsedTimeInMicroSec() < ((1000000 / 115200 * 12 * n))) //waitTimeForResponseUs
		{
			//pas de usleep : cela va décaler le setTX de 200us
		}
		setRX();
		err = serial_.getArray(bufferIn, 6); //status=6

		//logBf(buffer, n); //Log
		//logBf(bufferIn, 6); //Log

		//reading header of status packet
		if (bufferIn[0] != 0xFF || bufferIn[1] != 0xFF)
		{
			std::cout << "ERROR Received data without header bytes" << std::endl;
			logBf(bufferIn, 6); //Log
		}
		else if (bufferIn[2] != id)
		{
			std::cout << "ERROR Received status from wrong device : expected=" << id << std::endl;
			logBf(bufferIn, 6); //Log
		}
		else
		{
			// Now that we know a well formed packet is arriving, read remaining bytes
			int length = bufferIn[3];
			if (length == 2)
				statuserror = bufferIn[length + 4];
			else
				std::cout << "ERROR length status = " << reinterpret_cast<void*>(length) << " != 2" << std::endl;

			//verif du checksum
			utils::byte checksum = Utils::checkSumatory(bufferIn, length + 3);
			if (bufferIn[length + 3] != checksum)
			{
				std::cout << "ERROR Received data with wrong checksum " << reinterpret_cast<void*>(checksum) << " != "
						<< reinterpret_cast<void*>(bufferIn[length + 3]) << std::endl;
			}

			//check error status
			if (statuserror != 0)
			{
				std::cout << "ERROR Received status error = " << reinterpret_cast<void*>(statuserror) << std::endl;
				logBf(bufferIn, 6); //Log
			}
		}
	}

	usleep(2000);
	unlock();
	//return data;
}

long pmx::ServoMotorDxl::getCommand(int id, int regstart, int readLength)
{
	utils::Chronometer chrono;
	int err = 0;
	lock();
	cleanBuffers();
	int n = createReadDataBuffer(id, regstart, readLength);
	chrono.start();
	setTX(); //halfduplex transmit //No log until setRX !!
	err = serial_.sendArray(buffer, n);

	if (err < 0 || err != n)
	{
		std::cout << "ERROR serial_.sendArray()  don't send " << n << "bytes err=" << err << std::endl;
		unlock();
		return err;
	}
	else
	{
		//Wait the command to be sent
		while (chrono.getElapsedTimeInMicroSec() < ((1000000 / 115200 * 12 * n) + 20)) //waitTimeForResponseUs
		{
		} //pas de usleep : cela va décaler le setTX de 200us
		setRX(); //halfduplex receive
		err = serial_.getArray(bufferIn, readLength + 6);
		if (err < 0 || err != readLength + 6)
		{
			std::cout << "ERROR serial_.getArray() err=" << err << std::endl;
		}

		//logBf(buffer, n); //log
		//logBf(bufferIn, readLength + 6); //Log

		long receiveddata = -1;
		int statuserror = -1;
		//reading header of status packet
		if (bufferIn[0] != 0xFF || bufferIn[1] != 0xFF)
		{
			std::cout << "ERROR Received data without header bytes" << std::endl;
		}
		else if (bufferIn[2] != id)
		{
			std::cout << "ERROR Received status from wrong device (expected %d):" << id << std::endl;
		}
		else
		{
			// Now that we know a well formed packet is arriving, read remaining bytes
			int length = bufferIn[3];

			if (length == readLength + 2)
			{
				statuserror = bufferIn[4];
				if (statuserror != 0)
				{
					std::cout << "ERROR Received statuserror =  " << reinterpret_cast<void*>(statuserror) << std::endl;
				}

				if (readLength == 2)
				{
					receiveddata = Hex::fromHexHLConversion(bufferIn[5], bufferIn[6]);
				}
				else if (readLength == 1)
				{
					receiveddata = bufferIn[5];

				}
				else
				{
					std::cout << "ERROR NOT DEFINED, more 3 bytes received" << std::endl;
				}
			}

			//verif du checksum
			byte checksum = Utils::checkSumatory(bufferIn, length + 3);
			if (bufferIn[length + 3] != checksum)
			{
				std::cout << "ERROR Received data with wrong checksum " << reinterpret_cast<void*>(checksum) << " != "
						<< reinterpret_cast<void*>(bufferIn[length + 3]) << std::endl;
			}

		}
		usleep(2000);
		unlock();
		return receiveddata;
	}

}

//create buffer for read
int pmx::ServoMotorDxl::createReadDataBuffer(int id, int regstart, int readLength)
{
	//0XFF 0XFF ID LENGTH INSTRUCTION PARAMETER_1 ...PARAMETER_N CHECK SUM
	int pos = 0;
	byte numberOfParameters = 1;
	buffer[pos++] = 0xff;
	buffer[pos++] = 0xff;
	buffer[pos++] = id;
	buffer[pos++] = (byte) ((numberOfParameters + 3)); // length = 4
	buffer[pos++] = AX_READ_DATA; //the instruction, read => 2
	buffer[pos++] = regstart; // pos registers
	buffer[pos++] = readLength; //bytes to read
	byte checksum = Utils::checkSumatory(buffer, pos);
	buffer[pos++] = checksum;
	return pos;
}

//create buffer for write 1 or 2 bytes
int pmx::ServoMotorDxl::createWriteDataBuffer(int id, int regstart, int data, int numberOfParameters)
{
	//0XFF 0XFF ID LENGTH INSTRUCTION PARAMETER_1 ...PARAMETER_N CHECK SUM
	int pos = 0;
	//byte numberOfParameters = 1;
	buffer[pos++] = 0xff;
	buffer[pos++] = 0xff;
	buffer[pos++] = id;
	buffer[pos++] = (byte) ((numberOfParameters + 3)); // length = 4 // bodyLength = (Numbers of parameters) + 3
	buffer[pos++] = AX_WRITE_DATA; //the instruction, write => 3
	buffer[pos++] = regstart; // pos registers
	buffer[pos++] = (data & 0xff); //data bytes to write
	if (numberOfParameters == 2)
	{
		buffer[pos++] = ((data & 0xff00) >> 8);
	}
	byte checksum = Utils::checkSumatory(buffer, pos);
	buffer[pos++] = checksum;
	return pos;
}

void pmx::ServoMotorDxl::logBf(utils::byte *buffer, int n)
{
	for (int i = 0; i < n + 1; i++)
	{
		std::cout << " " << reinterpret_cast<void*>(buffer[i]) << std::flush;
	}
	std::cout << std::endl;
}


long pmx::ServoMotorDxl::dxlGetTemperature(int id)
{
	return this->getCommand(id, AX_PRESENT_TEMP , 1);
}

long pmx::ServoMotorDxl::dxlGetVoltage(int id)
{
	return getCommand(id, AX_PRESENT_VOLTAGE, 1);
}

long pmx::ServoMotorDxl::dxlGetPos(int id)
{
	return getCommand(id, AX_PRESENT_POSITION_L, 2);
}

long pmx::ServoMotorDxl::dxlGetBaud(int id)
{
	return getCommand(id, AX_BAUD_RATE, 1);
}

long pmx::ServoMotorDxl::dxlGetMaxTorqueLimit(int id)
{
	return getCommand(id, AX_TORQUE_LIMIT_L, 2);
}

long pmx::ServoMotorDxl::dxlGetEnableTorque(int id)
{
	return getCommand(id, AX_TORQUE_ENABLE, 1);
}

long pmx::ServoMotorDxl::dxlGetReturnDelay(int id)
{
	return getCommand(id, AX_RETURN_DELAY_TIME, 1);
}

long pmx::ServoMotorDxl::dxlGetAcMoving(int id)
{
	return getCommand(id, AX_MOVING, 1);
}

long pmx::ServoMotorDxl::dxlGetAxLed(int id)
{
	return getCommand(id, AX_LED, 1);
}


void pmx::ServoMotorDxl::dxlSetPos(int id, int pos)
{
	setCommand(id, AX_GOAL_POSITION_L, pos, 2);
}
void pmx::ServoMotorDxl::dxlSetAxLedOn(int id)
{
	setCommand(id, AX_LED, 1, 1);
}
void pmx::ServoMotorDxl::dxlSetAxLedOff(int id)
{
	setCommand(id, AX_LED, 0, 1);
}


