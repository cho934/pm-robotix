/*!
 * \file
 * \brief Implémentation de la classe ServoMotorDxl.
 */

#include "ServoMotorDxl.hpp"

#include <string.h>
#include <unistd.h>
#include <iostream>
#include "Chronometer.hpp"
#include "Exception.hpp"
#include "Logger.hpp"
#include "ServoMotorDxlConstant.hpp"

pmx::ServoMotorDxl::ServoMotorDxl()
{
	cleanBuffers();
	try
	{
		gpio_halfduplex_.openIoctl('C', 3);
		gpio_halfduplex_.setDirIoctl(1);

	} catch (utils::Exception * e)
	{
		logger().error() << "Exception on gpio: " << e->what() << utils::end;
	}

	try
	{
		serial_.connect();
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception on serial: " << e->what() << utils::end;
	}
	setTX();

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
	try
	{
		gpio_halfduplex_.setValueIoctl(Tx_MODE);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception on setTX: " << e->what() << utils::end;
	}
}

void pmx::ServoMotorDxl::setRX()
{
	try
	{
		gpio_halfduplex_.setValueIoctl(Rx_MODE);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception on setRX: " << e->what() << utils::end;
	}
}
//return 0 if ok , TODO -1 otherwise
void pmx::ServoMotorDxl::setCommand(int id, int regstart, int data, int nb2Write)
{
	int statuserror = 0;
	int err = 0;
	utils::Chronometer chrono;

	lock();

	cleanBuffers();

	int n = createWriteDataBuffer(id, regstart, data, nb2Write);
	chrono.start();
	setTX(); //No display log until setRX !!
	try
	{
		err = serial_.sendArray(buffer, n);
		//Wait the command to be sent
		//while (chrono.getElapsedTimeInMicroSec() < ((1000000 / 115200 * 12 * n))) //waitTimeForResponseUs
		while (chrono.getElapsedTimeInMicroSec() < ((1000000  * 12 * n) / 115200)) //waitTimeForResponseUs
		{
			//pas de usleep : cela va décaler le setTX de 200us
		}
		setRX();
		err = serial_.getArray(bufferIn, 6); //status=6
	} catch (utils::Exception * e)
	{
		//setRX();
		logBf(buffer, n);
		logger().debug() << "Exception on setCommand, data not send : " << e->what() << utils::end;
	}

	//logBf(buffer, n); //Log
	//logBf(bufferIn, 6); //Log

	//reading header of status packet
	if (bufferIn[0] != 0xFF || bufferIn[1] != 0xFF)
	{
		//std::cout << "ERROR Received data without header bytes" << std::endl;
		logger().debug() << "ERROR Received data without header bytes" << utils::end;
		logBf(bufferIn, 6); //Log
	}
	else if (bufferIn[2] != id)
	{
		logger().debug() << "ERROR Received status from wrong device : expected=" << id << utils::end;
		//std::cout << "ERROR Received status from wrong device : expected=" << id << std::endl;
		logBf(bufferIn, 6); //Log
	}
	else
	{
		// Now that we know a well formed packet is arriving, read remaining bytes
		int length = bufferIn[3];
		if (length == 2)
			statuserror = bufferIn[length + 4];
		else
			logger().debug() << "ERROR length status = " << reinterpret_cast<void*>(length) << " != 2" << utils::end;
		//std::cout << "ERROR length status = " << reinterpret_cast<void*>(length) << " != 2" << std::endl;

		//verif du checksum
		utils::byte checksum = Utils::checkSumatory(bufferIn, length + 3);
		if (bufferIn[length + 3] != checksum)
		{
			logger().debug() << "ERROR Received data with wrong checksum " << reinterpret_cast<void*>(checksum)
					<< " != " << reinterpret_cast<void*>(bufferIn[length + 3]) << utils::end;
			//std::cout << "ERROR Received data with wrong checksum " << reinterpret_cast<void*>(checksum) << " != "
			//		<< reinterpret_cast<void*>(bufferIn[length + 3]) << std::endl;
		}

		//check error status
		if (statuserror != 0)
		{
			logger().debug() << "ERROR Received status error = " << reinterpret_cast<void*>(statuserror) << utils::end;
			//std::cout << "ERROR Received status error = " << reinterpret_cast<void*>(statuserror) << std::endl;
			logBf(bufferIn, 6); //Log
		}
	}

	//usleep(4000);
	setTX();
	unlock();
}

long pmx::ServoMotorDxl::getCommand(int id, int regstart, int readLength)
{
	utils::Chronometer chrono;
	int err = 0;
	int error = 0;
	lock();
	cleanBuffers();
	int n = createReadDataBuffer(id, regstart, readLength);
	chrono.start();
	//logger().error() << "avec="<< ((1000000* 12 * n) / 115200 ) -60 << utils::end;
	//logger().error() << "sans="<< ((1000000 / 115200 * 12 * n) + 20) << utils::end;

	//setTX(); //halfduplex transmit //No log until setRX !!
	try
	{
		err = serial_.sendArray(buffer, n);
		//Wait the command to be sent
		while (chrono.getElapsedTimeInMicroSec() < ((1000000 * 12 * n) / 115200)) //waitTimeForResponseUs
		{
		} //pas de usleep : cela va décaler le setTX de 200us
		setRX(); //halfduplex receive
	} catch (utils::Exception * e)
	{
		//setRX(); //halfduplex receive
		logBf(buffer, n);
		logger().debug() << "Exception on setCommand, data not send : " << e->what() << utils::end;
		unlock();
		return err;
	}

	err = serial_.getArray(bufferIn, readLength + 6);
	if (err < 0)
	{
		logger().debug() << "ERROR getCommand, serial_.getArray() < 0 : " << err << utils::end;
		//logBf(bufferIn, readLength + 6);
		//std::cout << "ERROR serial_.getArray() err=" << err << std::endl;
		error = -1;
	}
	if (err != readLength + 6)
	{
		logger().debug() << "ERROR getCommand, serial_.getArray() bytetoRead=" << err
				<< " different de readLength + 6 =" << readLength + 6 << utils::end;
		//logBf(bufferIn, readLength + 6);
		//std::cout << "ERROR serial_.getArray() err=" << err << std::endl;
		error = -1;
	}

	long receiveddata = -1;
	int statuserror = -1;
	//reading header of status packet
	if (bufferIn[0] != 0xFF || bufferIn[1] != 0xFF)
	{
		logger().debug() << "ERROR getCommand, Received data without header bytes" << utils::end;
		//logBf(bufferIn, readLength + 6);
		//std::cout << "ERROR Received data without header bytes" << std::endl;
		error = -1;
	}
	else if (bufferIn[2] != id)
	{
		logger().debug() << "ERROR getCommand, Received status from wrong device (expected %d):" << id << utils::end;
		//std::cout << "ERROR Received status from wrong device (expected %d):" << id << std::endl;
		//logBf(bufferIn, readLength + 6);
		error = -1;
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
				logger().debug() << "ERROR getCommand, Received statuserror =  " << reinterpret_cast<void*>(statuserror)
						<< utils::end;
				//logBf(bufferIn, readLength + 6);
				//std::cout << "ERROR Received statuserror =  " << reinterpret_cast<void*>(statuserror) << std::endl;
				error = -1;
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
				logger().debug() << "ERROR getCommand, NOT DEFINED, more 3 bytes received" << utils::end;
				//std::cout << "ERROR NOT DEFINED, more 3 bytes received" << std::endl;
				//logBf(bufferIn, readLength + 6);
				error = -1;
			}
		}

		//verif du checksum
		byte checksum = Utils::checkSumatory(bufferIn, length + 3);
		if (bufferIn[length + 3] != checksum)
		{
			logger().debug() << "ERROR getCommand,Received data with wrong checksum "
					<< reinterpret_cast<void*>(checksum) << " != " << reinterpret_cast<void*>(bufferIn[length + 3])
					<< utils::end;
			//std::cout << "ERROR Received data with wrong checksum " << reinterpret_cast<void*>(checksum) << " != "
			//		<< reinterpret_cast<void*>(bufferIn[length + 3]) << std::endl;
			//logBf(bufferIn, readLength + 6);
			error = -1;
		}
	}
	if (error < 0)
	{
		logBf(buffer, n); //Log
		logBf(bufferIn, 6); //Log
		logger().error() << utils::end;
		//	exit(0);
	}

	//usleep(4000); //minimum time to wait before new transaction
	setTX();
	unlock();

	return receiveddata;
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

//log
void pmx::ServoMotorDxl::logBf(utils::byte *buffer, int n)
{
	std::ostringstream msg;

	for (int i = 0; i < n; i++)
	{
		msg << " " << reinterpret_cast<void*>(buffer[i]);
	}
	logger().error() << "logBuf: " << msg.str() << utils::end;

}

long pmx::ServoMotorDxl::dxlGetTemperature(int id)
{
	return this->getCommand(id, AX_PRESENT_TEMP, 1);
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
	int err = 0;
	long mov = -1;
	while (err < 10)
	{
		mov = getCommand(id, AX_MOVING, 1);
		if (mov < 0)
		{
			err++;
			usleep(2000);
		}
		else
			break;
	}
	if (err > 0)
		logger().error() << "ERROR nb=" << err << utils::end;
	return mov;
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

void pmx::ServoMotorDxl::dxlSetEnableTorque(int id, int tor)
{
	setCommand(id, AX_TORQUE_ENABLE, tor, 1);
}

