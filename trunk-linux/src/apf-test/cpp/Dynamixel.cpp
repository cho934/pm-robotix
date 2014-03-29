/*------------------------------------------------------------------------------*\
 * This source file is subject to the GPLv3 license that is bundled with this   *
 * package in the file COPYING.                                                 *
 * It is also available through the world-wide-web at this URL:                 *
 * http://www.gnu.org/licenses/gpl-3.0.txt                                      *
 * If you did not receive a copy of the license and are unable to obtain it     *
 * through the world-wide-web, please send an email to                          *
 * siempre.aprendiendo@gmail.com so we can send you a copy immediately.         *
 *                                                                              *
 * @category  Robotics                                                          *
 * @copyright Copyright (c) 2011 Jose Cortes (http://www.siempreaprendiendo.es) *
 * @license   http://www.gnu.org/licenses/gpl-3.0.txt GNU v3 Licence            *
 *                                                                              *
 \*------------------------------------------------------------------------------*/

#include "stdio.h"
#include <string.h>

#include "Dynamixel.hpp"
#include "Exception.hpp"
#include "../../common/cpp/Chronometer.hpp"

Dynamixel::Dynamixel()
{
	cleanBuffers();
	gpio_.openIoctl('C', 3); //TODO SETinit gpio and openDxl
	gpio_.setDirIoctl(1);

	if (serial_.connect("//dev//ttySMX1") <= 0)
	{
		printf("Can't open serial port\n");
		//TODO ERROR exception
	}
	else
	{
		printf("Serial port opened\n");
	}
	setRX();
	usleep(1000);

}

Dynamixel::~Dynamixel()
{
	//TODO create dxl close function
	serial_.disconnect();
	gpio_.closeIoctl();
}

void Dynamixel::cleanBuffers()
{
	memset(buffer, 0, BufferSize);
	memset(bufferIn, 0, BufferSize);
}

/** helper functions to switch direction of comms */
void Dynamixel::setTX()
{
	gpio_.setValueIoctl(Tx_MODE);
}

void Dynamixel::setRX()
{
	gpio_.setValueIoctl(Rx_MODE);
}
//return 0 if ok , TODO -1 otherwise
void Dynamixel::setCommand(int idAX12, int regstart, int data, int nb2Write)
{
	//int error = -1;
	int statuserror = 0;
	utils::Chronometer chrono;
	lock();

	cleanBuffers();

	int n = createWriteDataBuffer(idAX12, regstart, data, nb2Write);
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
			std::cout << "ERROR Received data without header bytes"
					<< std::endl;
			logBf(bufferIn, 6); //Log
		}
		else if (bufferIn[2] != idAX12)
		{
			std::cout << "ERROR Received status from wrong device : expected="
					<< idAX12 << std::endl;
			logBf(bufferIn, 6); //Log
		}
		else
		{
			// Now that we know a well formed packet is arriving, read remaining bytes
			int length = bufferIn[3];
			if (length == 2)
				statuserror = bufferIn[length + 4];
			else
				std::cout << "ERROR length status = "
						<< reinterpret_cast<void*>(length) << " != 2"
						<< std::endl;

			//verif du checksum
			byte checksum = Utils::checkSumatory(bufferIn, length + 3);
			if (bufferIn[length + 3] != checksum)
			{
				std::cout << "ERROR Received data with wrong checksum "
						<< reinterpret_cast<void*>(checksum) << " != "
						<< reinterpret_cast<void*>(bufferIn[length + 3])
						<< std::endl;
			}

			//check error status
			if (statuserror != 0)
			{
				std::cout << "ERROR Received status error = "
						<< reinterpret_cast<void*>(statuserror) << std::endl;
				logBf(bufferIn, 6); //Log
			}
		}
	}

	unlock();
	usleep(1000);
	//return data;
}

long Dynamixel::getCommand(int idAX12, int regstart, int readLength)
{
	utils::Chronometer chrono;
	int err = 0;
	lock();
	cleanBuffers();
	int n = createReadDataBuffer(idAX12, regstart, readLength);
	chrono.start();
	setTX(); //halfduplex transmit //No log until setRX !!
	err = serial_.sendArray(buffer, n);

	if (err < 0 || err != n)
	{
		std::cout << "ERROR serial_.sendArray()  don't send " << n
				<< "bytes err=" << err << std::endl;
		unlock();
		return err;
	}
	else
	{
		//Wait the command to be sent
		while (chrono.getElapsedTimeInMicroSec()
				< ((1000000 / 115200 * 12 * n) + 20)) //waitTimeForResponseUs
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
			std::cout << "ERROR Received data without header bytes"
					<< std::endl;
		}
		else if (bufferIn[2] != idAX12)
		{
			std::cout
					<< "ERROR Received status from wrong device (expected %d):"
					<< idAX12 << std::endl;
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
					std::cout << "ERROR Received statuserror =  "
							<< reinterpret_cast<void*>(statuserror)
							<< std::endl;
				}

				if (readLength == 2)
				{
					receiveddata = Hex::fromHexHLConversion(bufferIn[5],
							bufferIn[6]);
				}
				else if (readLength == 1)
				{
					receiveddata = bufferIn[5];

				}
				else
				{
					std::cout << "ERROR NOT DEFINED, more 3 bytes received"
							<< std::endl;
				}
			}

			//verif du checksum
			byte checksum = Utils::checkSumatory(bufferIn, length + 3);
			if (bufferIn[length + 3] != checksum)
			{
				std::cout << "ERROR Received data with wrong checksum "
						<< reinterpret_cast<void*>(checksum) << " != "
						<< reinterpret_cast<void*>(bufferIn[length + 3])
						<< std::endl;
			}

		}
		usleep(1000);
		unlock();
		return receiveddata;
	}

}

//create buffer for read
int Dynamixel::createReadDataBuffer(int id, int regstart, int readLength)
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

//create buffer for write 1 byte
int Dynamixel::createWriteDataBuffer(int id, int regstart, int data, int numberOfParameters)
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
	if (numberOfParameters==2)
	{
		buffer[pos++] = ((data & 0xff00) >> 8);
	}
	byte checksum = Utils::checkSumatory(buffer, pos);
	buffer[pos++] = checksum;
	return pos;
}
/*
//create buffer for write 2 bytes
int Dynamixel::createWriteDataBuffer2bytes(int id, int regstart, short data)
{
	//0XFF 0XFF ID LENGTH INSTRUCTION PARAMETER_1 ...PARAMETER_N CHECK SUM
	int pos = 0;
	byte numberOfParameters = 2;
	buffer[pos++] = 0xff;
	buffer[pos++] = 0xff;
	buffer[pos++] = id;
	buffer[pos++] = (byte) ((numberOfParameters + 3)); // length = 4 // bodyLength = (Numbers of parameters) + 3
	buffer[pos++] = AX_WRITE_DATA; //the instruction, write => 3
	buffer[pos++] = regstart; // pos registers
	buffer[pos++] = (data & 0xff); //data with 2 bytes to write //TODO Hex::toHexHLConversion
	buffer[pos++] = ((data & 0xff00) >> 8);
	byte checksum = Utils::checkSumatory(buffer, pos);
	buffer[pos++] = checksum;
	return pos;
}
*/
void Dynamixel::logBf(byte *buffer, int n)
{
	for (int i = 0; i < n + 1; i++)
	{
		std::cout << " " << reinterpret_cast<void*>(buffer[i]) << std::flush;
	}
	std::cout << std::endl;
}

