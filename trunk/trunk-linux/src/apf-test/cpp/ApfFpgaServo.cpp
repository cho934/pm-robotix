/*!
 * \file
 * \brief Implémentation de la classe ApfFpgaServo utilisant le FPGA pour contôler les servomoteurs.
 */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

#include "ApfFpgaServo.hpp"

void test::ApfFpgaServo::run(int argc, char *argv[])
{
	std::cout << "APF : Use FPGA to control servomotors" << std::endl;

	int num;
	int initpos;

	std::cout << "USAGE: APF_TEST " << argv[1]
			<< "[NumServo:0-31] [PositionValue:0-4096] " << std::endl;

	if (argc > 2)
	{
		num = atoi(argv[2]);
		std::cout << "numero servo: " << atoi(argv[2]) << std::endl;
	}
	else
	{
		std::cout << "numero servo: " << std::endl;
		std::cin >> num;
	}
	if (argc > 3)
	{
		initpos = atoi(argv[3]);
		std::cout << "position value: " << atoi(argv[3]) << std::endl;
	}
	else
	{
		std::cout << "position value: " << std::endl;
		std::cin >> initpos;
	}

	if (initpos > 4096 || initpos < 0)
	{
		std::cout << "position overflow " << std::endl;
		exit(1);
	}

	setServoEnable(num, 1);
	setServoPosition(num, initpos);

	int currentPos = getServoCurrentPosition(num);
	while (currentPos == initpos)
	{
		currentPos = getServoCurrentPosition(num);
		usleep(1000);
	}

	std::cout << "Servo" << num << ": current:" << currentPos
			<< " to desired position: " << initpos << std::endl;

	std::cout
			<< "REGLAGE POSITION : choose UP ('p') or DOWN('m') or Quit ('q')"
			<< std::endl;

	int pos = initpos;
	char c;

	//boucle de reglage position
	while ((c = getchar()) != 'q')
	{
		if (c == 'p')
		{
			pos = pos + 50;
			std::cout << "Servo" << num << ": START: adjusted position="
					<< pos << " getServoCurrentPosition="
					<< getServoCurrentPosition(num) << std::endl;

			setServoPosition(num, pos);
			std::cout << "Servo" << num << ": END  : adjusted position="
					<< pos << " getServoCurrentPosition="
					<< getServoCurrentPosition(num) << std::endl;

		}
		else if (c == 'm')
		{
			pos = pos - 50;
			std::cout << "Servo" << num << ": START: adjusted position="
					<< pos << " getServoCurrentPosition="
					<< getServoCurrentPosition(num) << std::endl;

			setServoPosition(num, pos);
			std::cout << "Servo" << num << ": END  :adjusted position="
					<< pos << " getServoCurrentPosition="
					<< getServoCurrentPosition(num) << std::endl;

		}
		usleep(1000);
	}

	setServoEnable(num, 0);

	std::cout << "End Of APF-TEST" << std::endl;
}

char* getFilename(int servoId, std::string type)
{
	char* name = new char[1024];
	memset(name, 0, 1024);
	sprintf(name, "%s%s%d/%s", SERVO_DRIVER_SYSFS_BASE, SERVO_DRIVER_SERVO_FILE,
			servoId, type.c_str());
	return name;
}

void test::ApfFpgaServo::setServoEnable(int servoID, int value)
{
	if (servoID < 0)
	{
		std::cout<< "ERROR servoID<0 " << servoID << std::endl;
	}
	else if (servoID >= NbMaxServo)
	{
		std::cout << "ERROR servoID>NbMaxServo " << servoID << ">"
				<< NbMaxServo << std::endl;
	}
	else
	{
		this->lock();
		char* operationFileName = getFilename(servoID,
		SERVO_DRIVER_SERVO_ENABLE_FILE);
		char data[16];

		std::cout << "setServoEnable  servoID=" << servoID << " value=" << value
				<< " operationFileName=" << operationFileName << std::endl;

		int file = open(operationFileName, O_WRONLY);
		if (file == -1)
		{
			std::cout << "MotionServer setServoEnable: failed to open  "
					<< operationFileName << std::endl;
		}
		/* Keep the value */
		servoEnableBuffer[servoID] = value; //todo configuration file parser
		sprintf(data, "%d", value);
		int ret = write(file, data, strlen(data));
		if (ret == -1)
		{
			std::cout
					<< "MotionServer setServoEnable: failed to write in  "
					<< operationFileName << std::endl;
			printf("Error can't open servo %c\nHave you run modprobe servo ?\n", servoID);
						exit(1);
		}
		close(file);
		delete operationFileName;
		this->unlock();
	}
}

void test::ApfFpgaServo::setServoOffset(int servoID, int value)
{
	if (servoID < 0)
	{
		std::cout << "ERROR servoID<0 " << servoID << std::endl;
	}
	else if (servoID >= NbMaxServo)
	{
		std::cout << "ERROR servoID>NbMaxServo " << servoID << ">"
				<< NbMaxServo << std::endl;
	}
	else
	{
		this->lock();
		char* operationFileName = getFilename(servoID,
		SERVO_DRIVER_SERVO_OFFSET_FILE);
		char data[16];

		int file = open(operationFileName, O_WRONLY);
		if (file == -1)
		{
			std::cout << "MotionServer setServoOffset: failed to open  "
					<< operationFileName << std::endl;
		}
		/* Keep the value */
		servoOffsetBuffer[servoID] = value;
		sprintf(data, "%d", value);
		int ret = write(file, data, strlen(data));
		if (ret == -1)
		{
			std::cout
					<< "MotionServer setServoOffset: failed to write in "
					<< operationFileName << std::endl;
		}
		close(file);
		delete operationFileName;
		this->unlock();
	}
}

void test::ApfFpgaServo::setServoPosition(int servoID, int value)
{
	if (servoID < 0)
	{
		std::cout << "ERROR servoID<0 " << servoID << std::endl;
	}
	else if (servoID >= NbMaxServo)
	{
		std::cout << "ERROR servoID>NbMaxServo " << servoID << ">"
				<< NbMaxServo << std::endl;
	}
	else
	{
		this->lock();
		char* operationFileName = getFilename(servoID,
		SERVO_DRIVER_SERVO_POSITION_FILE);
		char data[16];
		int file;
		int ret;

		file = open(operationFileName, O_WRONLY);
		if (file == -1)
		{
			std::cout << "MotionServer setServoPosition: failed to open "
					<< operationFileName << std::endl;
		}
		else
		{

			/* Keep the value */
			servoPositionBuffer[servoID] = value;
			sprintf(data, "%d", value);
			ret = write(file, data, strlen(data));
			if (ret == -1)
			{
				std::cout
						<< "MotionServer setServoPosition: failed to write in "
						<< operationFileName << std::endl;
			}
			close(file);
		}
		delete operationFileName;
		this->unlock();
	}
}

int test::ApfFpgaServo::getServoId(int servoID)
{
	int result = -1;
	if (servoID < 0)
	{
		std::cout << "ERROR servoID<0 " << servoID << std::endl;
	}
	else if (servoID >= NbMaxServo)
	{
		std::cout << "ERROR servoID>NbMaxServo " << servoID << ">"
				<< NbMaxServo << std::endl;
	}
	else
	{
		result = servoPositionBuffer[servoID];
	}
	return result;
}

int test::ApfFpgaServo::getServoCurrentPosition(int servoID)
{
	//cat /sys/class/servo/servo0/current_position
	int result = -1;
	if (servoID < 0)
	{
		std::cout  << "ERROR servoID<0 " << servoID << std::endl;
	}
	else if (servoID >= NbMaxServo)
	{
		std::cout  << "ERROR servoID>NbMaxServo " << servoID << ">"
				<< NbMaxServo << std::endl;
	}
	else
	{
		this->lock();
		char* operationFileName = getFilename(servoID,
		SERVO_DRIVER_SERVO_CURRENT_POS);
		int intValue = 0;

		std::ifstream file(operationFileName);
		if (file.is_open()) // ce test échoue si le fichier n'est pas ouvert
		{
			if (file.good())
			{
				std::string line;
				std::getline(file, line);
				intValue = atoi(line.c_str());

			}
			else
			{
				std::cout
						<< "ERROR getServoCurrentPosition : file not good "
						<< std::endl;
			}
			file.close();

		}
		else
		{
			std::cout  << "ERROR getServoCurrentPosition : No file found "
					<< std::endl;
		}
		delete operationFileName;
		this->unlock();

		result = intValue;
	}
	return result;
}
