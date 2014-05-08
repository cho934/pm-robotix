#ifndef SIMULATED
long long timeOffset;
int lPower;
int rPower;
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <string.h>
#include "../robot.h"
#include "lms2012.h"
#include "d_lcd.h"
#include "../motion.h"

// Sensors
#define SENSOR_PORT_1 0
#define SENSOR_PORT_2 1
#define SENSOR_PORT_3 2
#define SENSOR_PORT_4 3

static LCD my_lcd;
// A = 0x01, B = 0x02, C = 0x04, D = 0x08
// AC = 0x05
static const char MOTOR_PORT_RIGHT = 0x04;
static const char MOTOR_PORT_LEFT = 0x02;

static int ui_file;
static int motor_file;
static int iic_device_file;
static int analog_file;
static int uart_file;
// Internal encode
static int encoder_file;
static long offsetTachoLeft;
static long offsetTachoRight;

static UI *pButtons;
static UART *pUART;
static ANALOG *pAnalog;
static IIC *pIic;
static MOTORDATA *pMotorData;
#define HTANGLE_MODE_CALIBRATE              0x43
#define HTANGLE_MODE_RESET                  0x52

// MOTORS
// puissance minimale applicable pour que les 2 moteurs soient en rotation
#define MINIMAL_MOTOR_POWER 10

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
	//printf("robot_resetSensors (return_code %d) status %d\n", r, IicDat.Result);

	//
	IicDat.Port = SENSOR_PORT_3;
	IicDat.Result = -1;
	while (IicDat.Result) {
		r = ioctl(iic_device_file, IIC_SETUP, &IicDat);

	}
	//printf("robot_resetSensors (return_code %d) status %d\n", r, IicDat.Result);

	offsetTachoLeft = 0;
	offsetTachoRight = 0;
	offsetTachoLeft = robot_getLeftInternalCounter();
	offsetTachoRight = robot_getRightInternalCounter();

}
long robot_getLeftExternalCounter();
long robot_getRightExternalCounter();
void robot_init() {
	struct timeval te;
	gettimeofday(&te, NULL); // get current time
	timeOffset = (te.tv_sec * 1000LL + te.tv_usec / 1000);

	// Internal counters
	//Open the device file asscoiated to the motor encoders
	if ((encoder_file = open(MOTOR_DEVICE_NAME, O_RDWR | O_SYNC)) == -1) {
		printf("robot_init : internal counter init error\n");
		exit(1);
	}

	pMotorData = (MOTORDATA*) mmap(0, sizeof(MOTORDATA) * vmOUTPUTS,
	PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, encoder_file, 0);
	if (pMotorData == MAP_FAILED) {
		printf("robot_init : internal counter map error\n");
		exit(1);
	}

	//
	// external step counter
	//

	if ((iic_device_file = open(IIC_DEVICE_NAME, O_RDWR | O_SYNC)) == -1) {
		printf("robot_init : failed to open IIC device\n");
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
	// IR
	//
	//Open the device file
	if ((uart_file = open(UART_DEVICE_NAME, O_RDWR | O_SYNC)) == -1) {
		printf("robot_init : failed to open uart device\n");
		exit(1);
	}
	//Map kernel device to be used at the user space level
	pUART = (UART*) mmap(0, sizeof(UART), PROT_READ | PROT_WRITE,
	MAP_FILE | MAP_SHARED, uart_file, 0);
	if (pUART == MAP_FAILED) {
		printf("robot_init : mapping uart device failed\n");
		exit(1);
	}

	//SPECIAL CONFIGURATION
	//Set IR as remote control
	char IR_SENSOR_TYPE = 33;
	int IR_PROX = 0;
	DEVCON DevCon; // Configuration parameters
	DevCon.Mode[SENSOR_PORT_4] = IR_PROX;
	DevCon.Connection[SENSOR_PORT_4] = CONN_INPUT_UART;
	DevCon.Type[SENSOR_PORT_4] = IR_SENSOR_TYPE; //This instruction has no effect in the code
	r = ioctl(uart_file, UART_SET_CONN, &DevCon);
	printf("robot_init : IR is ready (%d)\n", r);
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
	// ui (for buttons)
	//

	if ((ui_file = open(UI_DEVICE_NAME, O_RDWR | O_SYNC)) == -1) {
		printf("robot_init : failed to open ui device\n");
		exit(1);
	}
	pButtons = (UI*) mmap(0, sizeof(UI), PROT_READ | PROT_WRITE,
	MAP_FILE | MAP_SHARED, ui_file, 0);
	if (pButtons == MAP_FAILED) {
		printf("robot_init : failed to map ui device\n");
		exit(1);
	}
	printf("robot_init : buttons ready (%d)\n", ui_file);

	//
	// Open the device file associated to the motor controlers
	//
	if ((motor_file = open(PWM_DEVICE_NAME, O_RDWR | O_APPEND)) == -1) {
		printf("robot_init : error\n");
		exit(1);
	}

	printf("robot_init : motors ready (%d)\n", motor_file);
	usleep(100 * 1000);

	long left = robot_getLeftExternalCounter();
	long right = robot_getRightExternalCounter();
	while (left != 0 && right != 0) {
		printf("Reset sensors %ld %ld\n", left, right);
		robot_resetSensors();
		sleep(1);
		left = robot_getLeftExternalCounter();
		right = robot_getRightExternalCounter();
	}

	//Initialize and clear screen
	dLcdInit(my_lcd.Lcd);
	LCDClear(my_lcd.Lcd);
	robot_startMotors();

	//sleep(3);
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
	result = close(ui_file);
	if (result != 0) {
		printf("robot_init : error closing ui_file\n");
	}
	dLcdExit();
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
void robot_setMotorRightSpeed(int speed) {
	printf("robot_setMotorRightSpeed REAL %d\n", speed);
	if (speed > 0) {
		speed += MINIMAL_MOTOR_POWER;
	}
	if (speed > 100) {
		speed = 100;
	}

	// Adjusted speed because motors are not identical
	if (speed > 0)
		speed--;

	char motor_command[3];

	motor_command[0] = opOUTPUT_POWER;
	motor_command[1] = MOTOR_PORT_RIGHT;
	// Set the motor desired speed 0 to 100
	motor_command[2] = speed;
	write(motor_file, motor_command, 3);
//	printf(
//			"robot_setMotorRightSpeed command : [%d, %d, %d] written size: %d on file: %d\n",
//			motor_command[0], motor_command[1], motor_command[2], s,
//			motor_file);
	rPower = speed;
}
void robot_setMotorLeftSpeed(int speed) {
	printf("robot_setMotorLeftSpeed REAL %d\n", speed);
	if (speed > 0) {
		speed += MINIMAL_MOTOR_POWER;
	}
	if (speed > 100) {
		speed = 100;
	}
	//DEFINE VARIABLES
	char motor_command[3];
	//ACTUATE MOTORS
	// All motor operations use the first command byte to indicate the type of operation
	// and the second one to indicate the motor(s) port(s)
	motor_command[0] = opOUTPUT_POWER;
	motor_command[1] = MOTOR_PORT_LEFT;
	// Set the motor desired speed 0 to 100
	motor_command[2] = speed;
	write(motor_file, motor_command, 3);
//	printf(
//			"robot_setMotorLeftSpeed command : [%d, %d, %d] written size: %d on file: %d\n",
//			motor_command[0], motor_command[1], motor_command[2], s,
//			motor_file);
	lPower = speed;
}

long robot_getExternalCounter(int portCounter1) {

	DATA8 *respbuf = pIic->Raw[portCounter1][pIic->Actual[portCounter1]];
	respbuf = pIic->Raw[portCounter1][pIic->Actual[portCounter1]];
//	int d0 = respbuf[0];
//	int d1 = respbuf[1];
	int d2 = respbuf[2];
	int d3 = respbuf[3];
//	int d4 = respbuf[4];
//	int d5 = respbuf[5];
//	int d6 = respbuf[6];
//	int d7 = respbuf[7];

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

long robot_getLeftInternalCounter() {
	return pMotorData[1].TachoSensor - offsetTachoLeft;
}

long robot_getRightInternalCounter() {
	return pMotorData[2].TachoSensor - offsetTachoRight;
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

int robot_isEmergencyPressed() {
	int buttonPort = SENSOR_PORT_1;
	unsigned char v =
			(unsigned char) pAnalog->Pin1[buttonPort][pAnalog->Actual[buttonPort]];
	if (v < 225) {
		//printf("Pressed\n");
		return TRUE;
	}
	return FALSE;
}
void robot_waitStart() {
	while (robot_isEmergencyPressed()) {
		usleep(100);
	}
}
int robot_isDetectingObstacle() {
	int IR_REMOTE_CONTROL_CHANNEL = 0;
	int dist =
			(unsigned char) pUART->Raw[SENSOR_PORT_4][pUART->Actual[SENSOR_PORT_4]][IR_REMOTE_CONTROL_CHANNEL];

//	printf("IR Remote Button: %d\n", dist);

	return dist < 30;
}
void robot_displayText(int line, char* text) {
	dLcdDrawText(my_lcd.Lcd, FG_COLOR, 2, 20 * (line + 1), NORMAL_FONT,
			(signed char *) text);
	dLcdUpdate(&my_lcd);
}

int robot_isButtonPressed(int button) {
	if (button < 0) {
		button = 0;
	}
	if (button >= BUTTONS) {
		button = BUTTONS - 1;
	}
	return pButtons->Pressed[button];
}

void robot_setLedStatus(int status) {
	if (status < 0) {
		status = 0;
	}
	if (status >= LEDPATTERNS) {
		status = LEDPATTERNS - 1;
	}

	//The first byte determines the color or pattern as specified in  bytecodes.h -> LEDPATTERN
	//The second byte (LED number) is not currently being used by the device driver, but is needed
	char led_command[2] = { 0, 0 };
	//The kernel driver will subtract a '0' offset before using the Color/Pattern instruction (see d_ui.c)
	led_command[0] = '0' + status;
	write(ui_file, led_command, 2);
}
void robot_initPID() {
	motion_configureAlphaPID(0.0005f, 0.00001f, 0.000000f);
	motion_configureDeltaPID(0.00080f, 0.0f, 0.0f);
}
#endif
