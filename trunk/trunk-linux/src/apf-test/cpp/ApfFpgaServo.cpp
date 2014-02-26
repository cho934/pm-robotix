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

	logger().info() << "USAGE: APF_TEST " << argv[1]
			<< "[NumServo:0-31] [PositionValue:0-4096] " << utils::end;

	if (argc > 2)
	{
		num = atoi(argv[2]);
		logger().info() << "numero servo: " << atoi(argv[2]) << utils::end;
	}
	else
	{
		logger().info() << "numero servo: " << utils::end;
		std::cin >> num;
	}
	if (argc > 3)
	{
		initpos = atoi(argv[3]);
		logger().info() << "position value: " << atoi(argv[3]) << utils::end;
	}
	else
	{
		logger().info() << "position value: " << utils::end;
		std::cin >> initpos;
	}

	if (initpos > 4096 || initpos < 0)
	{
		logger().error() << "position overflow " << utils::end;
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

	logger().info() << "Servo" << num << ": current:" << currentPos
			<< " to desired position: " << initpos << utils::end;

	logger().info()
			<< "REGLAGE POSITION : choose UP ('p') or DOWN('m') or Quit ('q')"
			<< utils::end;

	int pos = initpos;
	char c;

	//boucle de reglage position
	while ((c = getchar()) != 'q')
	{
		if (c == 'p')
		{
			pos = pos + 50;
			logger().info() << "Servo" << num << ": START: adjusted position="
					<< pos << " getServoCurrentPosition="
					<< getServoCurrentPosition(num) << utils::end;

			setServoPosition(num, pos);
			logger().debug() << "Servo" << num << ": END  : adjusted position="
					<< pos << " getServoCurrentPosition="
					<< getServoCurrentPosition(num) << utils::end;

		}
		else if (c == 'm')
		{
			pos = pos - 50;
			logger().info() << "Servo" << num << ": START: adjusted position="
					<< pos << " getServoCurrentPosition="
					<< getServoCurrentPosition(num) << utils::end;

			setServoPosition(num, pos);
			logger().debug() << "Servo" << num << ": END  :adjusted position="
					<< pos << " getServoCurrentPosition="
					<< getServoCurrentPosition(num) << utils::end;

		}
		usleep(1000);
	}

	setServoEnable(num, 0);

	logger().info() << "End Of APF-TEST" << utils::end;
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
		logger().error() << "ERROR servoID<0 " << servoID << utils::end;
	}
	else if (servoID >= NbMaxServo)
	{
		logger().error() << "ERROR servoID>NbMaxServo " << servoID << ">"
				<< NbMaxServo << utils::end;
	}
	else
	{
		this->lock();
		char* operationFileName = getFilename(servoID,
		SERVO_DRIVER_SERVO_ENABLE_FILE);
		char data[16];

		logger().info() << "setServoEnable  servoID=" << " value=" << value
				<< " operationFileName=" << operationFileName << utils::end;

		int file = open(operationFileName, O_WRONLY);
		if (file == -1)
		{
			logger().error() << "MotionServer setServoEnable: failed to open  "
					<< operationFileName << utils::end;
		}
		/* Keep the value */
		servoEnableBuffer[servoID] = value; //todo configuration file parser
		sprintf(data, "%d", value);
		int ret = write(file, data, strlen(data));
		if (ret == -1)
		{
			logger().error()
					<< "MotionServer setServoEnable: failed to write in  "
					<< operationFileName << utils::end;
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
		logger().error() << "ERROR servoID<0 " << servoID << utils::end;
	}
	else if (servoID >= NbMaxServo)
	{
		logger().error() << "ERROR servoID>NbMaxServo " << servoID << ">"
				<< NbMaxServo << utils::end;
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
			logger().error() << "MotionServer setServoOffset: failed to open  "
					<< operationFileName << utils::end;
		}
		/* Keep the value */
		servoOffsetBuffer[servoID] = value;
		sprintf(data, "%d", value);
		int ret = write(file, data, strlen(data));
		if (ret == -1)
		{
			logger().error()
					<< "MotionServer setServoOffset: failed to write in "
					<< operationFileName << utils::end;
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
		logger().error() << "ERROR servoID<0 " << servoID << utils::end;
	}
	else if (servoID >= NbMaxServo)
	{
		logger().error() << "ERROR servoID>NbMaxServo " << servoID << ">"
				<< NbMaxServo << utils::end;
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
			logger().error() << "MotionServer setServoPosition: failed to open "
					<< operationFileName << utils::end;
		}
		else
		{

			/* Keep the value */
			servoPositionBuffer[servoID] = value;
			sprintf(data, "%d", value);
			ret = write(file, data, strlen(data));
			if (ret == -1)
			{
				logger().error()
						<< "MotionServer setServoPosition: failed to write in "
						<< operationFileName << utils::end;
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
		logger().error() << "ERROR servoID<0 " << servoID << utils::end;
	}
	else if (servoID >= NbMaxServo)
	{
		logger().error() << "ERROR servoID>NbMaxServo " << servoID << ">"
				<< NbMaxServo << utils::end;
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
		logger().error() << "ERROR servoID<0 " << servoID << utils::end;
	}
	else if (servoID >= NbMaxServo)
	{
		logger().error() << "ERROR servoID>NbMaxServo " << servoID << ">"
				<< NbMaxServo << utils::end;
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
				logger().debug() << "OK getServoCurrentPosition : ok "
						<< utils::end;
			}
			else
			{
				logger().error()
						<< "ERROR getServoCurrentPosition : file not good "
						<< utils::end;
			}
			file.close();

		}
		else
		{
			logger().error() << "ERROR getServoCurrentPosition : No file found "
					<< utils::end;
		}
		delete operationFileName;
		this->unlock();

		result = intValue;
	}
	return result;
}
