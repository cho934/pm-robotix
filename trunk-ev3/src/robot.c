#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "lms2012.h"
#include <sys/time.h>
long long timeOffset;
// A = 0x01, B = 0x02, C = 0x04, D = 0x08
// AC = 0x05
const char MOTOR_PORT_RIGHT = 0x04;
const char MOTOR_PORT_LEFT = 0x02;

// Sensors
#define SENSOR_PORT_1 0
#define SENSOR_PORT_2 1
#define SENSOR_PORT_3 2
#define SENSOR_PORT_4 3

int motor_file;
int iic_device_file;
int analog_file;

ANALOG *pAnalog;
IIC *pIic;

int lPower;
int rPower;

int robot_getLeftPower() {
	return lPower;
}
int robot_getRightPower() {
	return rPower;
}

long currentTimeInMillis() {
	struct timeval te;
	gettimeofday(&te, NULL); // get current time
	long long milliseconds = (te.tv_sec * 1000LL + te.tv_usec / 1000); // caculate milliseconds
	return (long) (milliseconds - timeOffset);
}

#ifndef SIMULATED

#define HTANGLE_MODE_CALIBRATE              0x43
#define HTANGLE_MODE_RESET                  0x52
void robot_resetSensors() {

	IICDAT IicDat;

	IicDat.Repeat = 0;
	IicDat.Time = 0;
	// Message to write
	IicDat.WrLng = 3;
	IicDat.WrData[0] = 0x01;
	IicDat.WrData[1] = 0x41;
	IicDat.WrData[2] = HTANGLE_MODE_RESET;
	// Nothing to read
	IicDat.RdLng = 0;

	//
	IicDat.Port = SENSOR_PORT_2;
	IicDat.Result = -1;
	int r = 0;
	while (IicDat.Result) {
		r = ioctl(iic_device_file, IIC_SETUP, &IicDat);
	}
	printf("robot_resetSensors (return_code %d) status %d\n", r, IicDat.Result);

	//
	IicDat.Port = SENSOR_PORT_3;
	IicDat.Result = -1;
	while (IicDat.Result) {
		r = ioctl(iic_device_file, IIC_SETUP, &IicDat);

	}
	printf("robot_resetSensors (return_code %d) status %d\n", r, IicDat.Result);

}
void robot_init() {
	struct timeval te;
	gettimeofday(&te, NULL); // get current time
	timeOffset = (te.tv_sec * 1000LL + te.tv_usec / 1000);
	//
	// external step counter
	//

	if ((iic_device_file = open(IIC_DEVICE_NAME, O_RDWR | O_SYNC)) == -1) {
		printf("Failed to open IIC device\n");
		exit(1);
	}
	pIic = (IIC*) mmap(0, sizeof(IIC), PROT_READ | PROT_WRITE,
	MAP_FILE | MAP_SHARED, iic_device_file, 0);
	if (pIic == MAP_FAILED) {
		printf("robot_init : mapping IIC device failed\n");
		exit(1);
	}
	printf("robot_init : IIC Device is ready (%d)\n", iic_device_file);
	robot_resetSensors();
	IICDAT IicDat;
	//SPECIAL CONFIGURATION
	//Setup IIC to read 2 packets
	IicDat.Result = -1;

	IicDat.Repeat = 0;
	IicDat.Time = 0;

	IicDat.WrLng = 2;
	// Set the device I2C address
	IicDat.WrData[0] = 0x01;
	// Specify the register that will be read (0x42 = angle)
	IicDat.WrData[1] = 0x42;

	//
	IicDat.RdLng = 8;
	IicDat.RdData[0] = 0;
	IicDat.RdData[1] = 0;
	IicDat.RdData[2] = 0;
	IicDat.RdData[3] = 0;
	IicDat.RdData[4] = 0;
	IicDat.RdData[5] = 0;
	IicDat.RdData[6] = 0;
	IicDat.RdData[7] = 0;

	// Setup I2C comunication
	IicDat.Port = SENSOR_PORT_2;
	int r;
	while (IicDat.Result) {
		r = ioctl(iic_device_file, IIC_SETUP, &IicDat);

	}
	printf(
			"robot_init : IIC device is ready for left counter (return_code %d) %d\n",
			r, IicDat.Result);
	IicDat.Port = SENSOR_PORT_3;
	IicDat.Result = -1;
	while (IicDat.Result) {
		r = ioctl(iic_device_file, IIC_SETUP, &IicDat);

	}
	printf(
			"robot_init : IIC device is ready for right counter (return_code %d) %d\n",
			r, IicDat.Result);

	//
	// Contact sensors
	//

	if ((analog_file = open(ANALOG_DEVICE_NAME, O_RDWR | O_SYNC)) == -1) {
		printf("robot_init : failed to open analog device\n");
		exit(1);
	}
	pAnalog = (ANALOG*) mmap(0, sizeof(ANALOG), PROT_READ | PROT_WRITE,
	MAP_FILE | MAP_SHARED, analog_file, 0);
	if (pAnalog == MAP_FAILED) {
		printf("robot_init : mapping analog device failed\n");
		exit(1);
	}
	printf("robot_init : contact sensors ready (%d)\n", analog_file);
	printf("robot_init : done \n");
	usleep(100 * 1000);
	//
	// Open the device file associated to the motor controlers
	//
	if ((motor_file = open(PWM_DEVICE_NAME, O_RDWR | O_APPEND)) == -1) {
		printf("robot_init : error\n");
		exit(1);
	}

	printf("robot_init : motors ready (%d)\n", motor_file);
	usleep(100 * 1000);
}
void robot_dispose() {
	int result;
	result = close(motor_file);
	if (result != 0) {
		printf("robot_init : error closing motor_file\n");
	}
	result = close(iic_device_file);
	if (result != 0) {
		printf("robot_init : error closing iic_device_file\n");
	}
	result = close(analog_file);
	if (result != 0) {
		printf("robot_init : error closing analog_file\n");
	}
}

// Motors commands

void robot_startMotorLeft() {
	printf("robot_startMotorLeft %d\n", MOTOR_PORT_LEFT);
	char motor_command[2];
	// Start the motor
	motor_command[0] = opOUTPUT_START;
	motor_command[1] = MOTOR_PORT_LEFT;

	int s = write(motor_file, motor_command, 2);
	printf(
			"robot_startMotorLeft command : [%d, %d] written size: %d on file: %d\n",
			motor_command[0], motor_command[1], s, motor_file);
}
void robot_startMotors() {
	printf("robot_startMotors\n");

	char motor_command[2];
	motor_command[0] = opOUTPUT_RESET;
	motor_command[1] = MOTOR_PORT_RIGHT | MOTOR_PORT_LEFT;
	int s = write(motor_file, motor_command, 2);
	printf(
			"robot_startMotors command : [%d, %d] written size: %d on file: %d\n",
			motor_command[0], motor_command[1], s, motor_file);
	// Start the motor
	motor_command[0] = opOUTPUT_START;
	motor_command[1] = MOTOR_PORT_RIGHT | MOTOR_PORT_LEFT;

	s = write(motor_file, motor_command, 2);
	printf(
			"robot_startMotors command : [%d, %d] written size: %d on file: %d\n",
			motor_command[0], motor_command[1], s, motor_file);

	usleep(100 * 1000);
}

void robot_stopMotorRight() {
	printf("robot_stopMotorRight\n");
	char motor_command[2];
	// Stop the motor
	motor_command[0] = opOUTPUT_STOP;
	motor_command[1] = MOTOR_PORT_RIGHT;
	int s = write(motor_file, motor_command, 2);
	printf(
			"robot_stopMotorRight command : [%d, %d] written size: %d on file: %d\n",
			motor_command[0], motor_command[1], s, motor_file);
	rPower = 0;
}
void robot_stopMotorLeft() {
	printf("robot_stopMotorLeft\n");
	char motor_command[2];
	// Stop the motor
	motor_command[0] = opOUTPUT_STOP;
	motor_command[1] = MOTOR_PORT_LEFT;
	int s = write(motor_file, motor_command, 2);
	printf(
			"robot_stopMotorLeft command : [%d, %d] written size: %d on file: %d\n",
			motor_command[0], motor_command[1], s, motor_file);
	lPower = 0;
}
void robot_setMotorRightSpeed(char speed) {
	printf("robot_setMotorRightSpeed %d\n", speed);

	//DEFINE VARIABLES
	char motor_command[3];
	//ACTUATE MOTORS
	// All motor operations use the first command byte to indicate the type of operation
	// and the second one to indicate the motor(s) port(s)
	motor_command[0] = opOUTPUT_POWER;
	motor_command[1] = MOTOR_PORT_RIGHT;
	// Set the motor desired speed 0 to 100
	motor_command[2] = speed;
	int s = write(motor_file, motor_command, 3);
//	printf(
//			"robot_setMotorRightSpeed command : [%d, %d, %d] written size: %d on file: %d\n",
//			motor_command[0], motor_command[1], motor_command[2], s,
//			motor_file);
	rPower = speed;
}
void robot_setMotorLeftSpeed(char speed) {
	printf("robot_setMotorLeftSpeed %d\n", speed);

	//DEFINE VARIABLES
	char motor_command[3];
	//ACTUATE MOTORS
	// All motor operations use the first command byte to indicate the type of operation
	// and the second one to indicate the motor(s) port(s)
	motor_command[0] = opOUTPUT_POWER;
	motor_command[1] = MOTOR_PORT_LEFT;
	// Set the motor desired speed 0 to 100
	motor_command[2] = speed;
	int s = write(motor_file, motor_command, 3);
//	printf(
//			"robot_setMotorLeftSpeed command : [%d, %d, %d] written size: %d on file: %d\n",
//			motor_command[0], motor_command[1], motor_command[2], s,
//			motor_file);
	lPower = speed;
}

long robot_getExternalCounter(int portCounter1) {

	DATA8 *respbuf = pIic->Raw[portCounter1][pIic->Actual[portCounter1]];
	respbuf = pIic->Raw[portCounter1][pIic->Actual[portCounter1]];
	int d0 = respbuf[0];
	int d1 = respbuf[1];
	int d2 = respbuf[2];
	int d3 = respbuf[3];
	int d4 = respbuf[4];
	int d5 = respbuf[5];
	int d6 = respbuf[6];
	int d7 = respbuf[7];

//	printf("EV3: port %d : %d %d %d %d %d %d %d %d    \n", portCounter1, d0, d1,
//			d2, d3, d4, d5, d6, d7);
	int angle = d2;
	int nbTour = d3;
	if (angle < 0) {
		angle = (256 + angle);
	}
	long count = nbTour * 256 + angle;
	//printf("E: port %d : %ld\n", portCounter1, count);
	return -count;
}

// Odometry

long robot_getLeftExternalCounter() {
	return robot_getExternalCounter(SENSOR_PORT_3);
}

long robot_getRightExternalCounter() {
	return -robot_getExternalCounter(SENSOR_PORT_2);
}

// Contact sensors

int robot_isButton1Pressed() {
	int buttonPort = SENSOR_PORT_1;
	unsigned char v =
			(unsigned char) pAnalog->Pin1[buttonPort][pAnalog->Actual[buttonPort]];
	if (v < 225) {
		printf("Pressed\n");
		return TRUE;
	}
	return FALSE;
}
#else
/**
 *
 * SIMULATION
 *
 **/

long tLeft;

long tRight;

long rightCounter;
long leftCounter;

void robot_init() {
	tLeft=0;
	tRight=0;
	lPower=0;
	rPower=0;

	rightCounter=0;
	leftCounter=0;
	//
	struct timeval te;
	gettimeofday(&te, NULL);// get current time
	timeOffset =( te.tv_sec*1000LL + te.tv_usec/1000);

	printf("Init time %ld\n",currentTimeInMillis());
}
void robot_dispose() {
}
void robot_startMotorLeft() {
}
void robot_startMotors() {
}

void robot_stopMotorRight() {
}
void robot_stopMotorLeft() {
}
void computeCounterL() {
	long deltaT= currentTimeInMillis()- tLeft;
	leftCounter+= (deltaT*lPower )/100;

}
void computeCounter() {
	long deltaT= currentTimeInMillis()- tRight;
	rightCounter+= (deltaT*rPower )/100;
}

void robot_setMotorRightSpeed(int speed) {
	computeCounter();
	rPower=speed;
	tRight=currentTimeInMillis();
}

void robot_setMotorLeftSpeed(int speed) {
	computeCounterL();
	lPower=speed;
	tLeft=currentTimeInMillis();
}

long robot_getLeftExternalCounter() {
	computeCounterL();
	return leftCounter;
}
long robot_getRightExternalCounter() {
	computeCounter();
	return rightCounter;
}

int robot_isButton1Pressed() {
	return 0;
}

#endif
