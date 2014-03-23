#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "lms2012.h"
#include "robot.h"
#include "test.h"
#include "mcontrol/motion.h"
#include "mcontrol/encoder.h"
#include "log.h"
#include "mcontrol/global.h"
#include "mcontrol/path_manager.h"

void a(char motorPort) {

	//DEFINE VARIABLES
	char motor_command[3];
	int motor_file;

	//INITIALIZE DEVICE
	//Open the device file asscoiated to the motor controlers
	if ((motor_file = open(PWM_DEVICE_NAME, O_WRONLY)) == -1)
		return; //Failed to open device

	//ACTUATE MOTORS
	// All motor operations use the first command byte to indicate the type of operation
	// and the second one to indicate the motor(s) port(s)
	motor_command[0] = opOUTPUT_SPEED;
	motor_command[1] = motorPort;
	// Set the motor desired speed 0 to 100
	motor_command[2] = 100;
	//printf("moteur a 100 \n");
	write(motor_file, motor_command, 3);
	// Start the motor
	motor_command[0] = opOUTPUT_START;
	write(motor_file, motor_command, 2);
	// Run the motor for a couple of seconds
	sleep(2);
	// Stop the motor
	motor_command[0] = opOUTPUT_STOP;
	write(motor_file, motor_command, 2);

	//CLOSE DEVICE
	close(motor_file);

}
void test() {

	robot_init();

	robot_startMotors();

	printf("SET SPEED TO 100\n");

	robot_setMotorRightSpeed(100);
	robot_setMotorLeftSpeed(100);

	sleep(5);
	printf("SET SPEED TO 0\n");
	robot_setMotorRightSpeed(0);
	robot_setMotorLeftSpeed(0);

	sleep(5);
	printf("SLEEP STOP\n");
	robot_stopMotorLeft();
	robot_stopMotorRight();
	robot_dispose();

	sleep(2);

}

//=====================================================================
// ReadSensorHTAngle(port, Angle, AccAngle, RPM)
// Reads the HiTechnic Angle Sensor and returns the current:
//   Angle              degrees (0-359)
//   Accumulated Angle  degrees (-2147483648 to 2147483647)
//   RPM                rotations per minute (-1000 to 1000)
//typedef int bool;
//typedef char byte;
//
//
// void ReadSensorHTAngle(int port, int *Angle, long *AccAngle, int *RPM)
//{
//	int count;
//	byte cmndbuf[] = {0x02, 0x42};  // I2C device, register address
//	byte respbuf[60];// Response Buffer
//	bool fSuccess;
//	count=8;// 8 bytes to read
//	fSuccess = I2CBytes(port, cmndbuf, count, respbuf);
//	if (fSuccess) {
//		*Angle = respbuf[0]*2 + respbuf[1];
//		*AccAngle = respbuf[2]*0x1000000 + respbuf[3]*0x10000+
//		respbuf[4]*0x100 + respbuf[5];
//		*RPM = respbuf[6]*0x100 + respbuf[7];
//	} else {
//		// No data from sensor
//		Angle = 0; AccAngle = 0; RPM = 0;
//	}
//}
//
//// ReserSensorHTAnalog(port, resetmode)
//// resetmode:
////   HTANGLE_MODE_CALIBRATE  Calibrate the zero position of angle.
////                           Zero position is saved in EEPROM on sensor.
////   HTANGLE_MODE_RESET      Reset the rotation count of accumulated.
////                           angle to zero.  Not saved in EEPORM.
//#define HTANGLE_MODE_CALIBRATE              0x43
//#define HTANGLE_MODE_RESET                  0x52
//void ResetSensorHTAngle(int port, int resetmode) {
//	int count;
//	char cmndbuf[] = { 0x02, 0x41, 0 }; // I2C device, register address
//	char respbuf[60];                   // buffer for inbound I2C response
//	cmndbuf[2] = resetmode;           // Set reset code
//	count = 0;                          // 0 bytes to read
//	I2CBytes(port, cmndbuf, count, respbuf);
//	if (resetmode == HTANGLE_MODE_CALIBRATE)
//		sleep(1);  // Time to allow burning EEPROM
//}

int calibrate() {
	int portCounter1 = 2;
	//DEFINE VARIABLES
	int iic_device_file;
	IIC *pIic;
	int i;

	//INITIALIZE DEVICE
	//Open the device file
	if ((iic_device_file = open(IIC_DEVICE_NAME, O_RDWR | O_SYNC)) == -1) {
		printf("Failed to open IIC device\n");
		return -1;
	}
	pIic = (IIC*) mmap(0, sizeof(IIC), PROT_READ | PROT_WRITE,
	MAP_FILE | MAP_SHARED, iic_device_file, 0);
	if (pIic == MAP_FAILED) {
		printf("Mapping IIC device failed\n");
		return -1;
	}
	printf("IIC Device is ready\n");

	IICDAT IicDat;
	//SPECIAL CONFIGURATION
	//Setup IIC to read 2 packets
	IicDat.Result = OK;
	IicDat.Port = portCounter1;
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
	int r = ioctl(iic_device_file, IIC_SETUP, &IicDat);
	printf("Device is ready %d \n", r);

	long angleCounter = 0;
	int lastAngle = 0;
	DATA8 *respbuf = pIic->Raw[portCounter1][pIic->Actual[portCounter1]];
	lastAngle = respbuf[0];
	//PROCESS SENSOR DATA
	//Read IIC device state
	long startCounter = 0;

	for (i = 0; i < 10000; i++) {

		respbuf = pIic->Raw[portCounter1][pIic->Actual[portCounter1]];
		int d0 = respbuf[0];
		int d1 = respbuf[1];
		int d2 = respbuf[2];
		int d3 = respbuf[3];
		int d4 = respbuf[4];
		int d5 = respbuf[5];
		int d6 = respbuf[6];
		int d7 = respbuf[7];

		//printf("E:%d\n", d1 + d6);
		printf("EV3: %d %d %d %d %d %d %d %d    \n", d0, d1, d2, d3, d4, d5, d6,
				d7);
		int angle = d1;
		int nbTour = d2;
		if (angle < 0) {
			angle = (256 + angle);

		}
		//printf("E: d3 corrige %d\n", d3);
		angleCounter = nbTour * 256 + angle;

		if (i == 0) {
			startCounter = angleCounter;
		}

		//printf("Last:%d d:%d \n", lastAngle, delta);
		printf("EV3: nbTour:%d angle:%d  t:%ld\n", nbTour, angle, angleCounter);
		//	uc =
		//			(unsigned char) (pIic->Raw[portCounter1][pIic->Actual[portCounter1]][0]);
		//printf("Value: %d \n", uc);
		//printf("Angle:%d last: %d Total: %ld delta:%d\n", angle, lastAngle,
		//	angleCounter, delta);

		usleep(500 * 1000);
		//sleep(1);
	}

	//CLOSE DEVICE
	printf("Clossing device\n");
	close(iic_device_file);

	return 0;
}

void testUart() {
	int buttonPort = 0;

	//DEFINE VARIABLES
	int file;
	UART *pUart; //UART porte user level handler
	int i;

	//INITIALIZE DEVICE
	//Open the device uart device file
	if ((file = open(UART_DEVICE_NAME, O_RDWR | O_SYNC)) == -1) {
		printf("Failed to open device\n");
		return;
	}
	//Map kernel device to be used at the user space level
	pUart = (UART*) mmap(0, sizeof(UART), PROT_READ | PROT_WRITE,
	MAP_FILE | MAP_SHARED, file, 0);
	if (pUart == MAP_FAILED) {
		printf("Failed to map device\n");
		return;
	}

	//PROCESS SENSOR DATA
	printf("Device is ready\n");
	for (i = 0; i < 100; i++) {
		printf("UART Value: %d\n",
				(unsigned char) pUart->Raw[buttonPort][pUart->Actual[buttonPort]][0]);
		sleep(1);
	}

	//CLOSE DEVICE
	printf("Clossing device\n");
	close(file);

}
void testExternalCounters(int seconds, int enableMotors) {

	robot_init();
	if (enableMotors > 0) {
		robot_startMotors();
	}
	int speed = 20;
	//PROCESS SENSOR DATA
	long lStart = robot_getLeftExternalCounter();
	long rStart = robot_getRightExternalCounter();

	// Boucle principale
	int i;
	for (i = 0; i < seconds; i++) {
		if (enableMotors > 0) {
			// Update la vitesse
			robot_setMotorRightSpeed(speed);
			robot_setMotorLeftSpeed(speed);
			if (speed < 100 && i % 20) {
				speed++;
			}
		}
		printf("Current speed: %d , counters: left: %ld right: %ld\n", speed,
				robot_getLeftExternalCounter(),
				robot_getRightExternalCounter());
		printf("Counters from start : left: %ld  right: %ld\n",
				lStart - robot_getLeftExternalCounter(),
				rStart - robot_getRightExternalCounter());
		usleep(1000 * 1000);
	}
	if (enableMotors > 0) {
		printf("Motors stopped\n");
		robot_setMotorRightSpeed(0);
		robot_setMotorLeftSpeed(0);
	}
	printf("Waiting 1s\n");
	sleep(1);
	printf("Current speed: %d , counters: left: %ld right: %ld\n", speed,
			robot_getLeftExternalCounter(), robot_getRightExternalCounter());
	printf("Counters from start : left: %ld  right: %ld\n",
			lStart - robot_getLeftExternalCounter(),
			rStart - robot_getRightExternalCounter());

	robot_dispose();
	printf("END\n");

}
void testButton2() {
	// Bouton poussoir : ANALOG, Pin1, Pressed if value < 225
	int buttonPort = 0;
//DEFINE VARIABLES
	int file;
	ANALOG *pAnalog;
	int i;

	//INITIALIZE DEVICE
	//Open the device file
	if ((file = open(ANALOG_DEVICE_NAME, O_RDWR | O_SYNC)) == -1) {
		printf("Failed to open device\n");
		return;
	}
	pAnalog = (ANALOG*) mmap(0, sizeof(ANALOG), PROT_READ | PROT_WRITE,
	MAP_FILE | MAP_SHARED, file, 0);
	if (pAnalog == MAP_FAILED) {
		printf("Mapping device failed\n");
		return;
	}
	printf("Device ready for Analog\n");

	//PROCESS SENSOR DATA
	//Read samples
	unsigned char v;
	for (i = 0; i < 100; i++) {
		v =
				(unsigned char) pAnalog->Pin1[buttonPort][pAnalog->Actual[buttonPort]];
		printf("Analog Value =  %d \n", v);
		if (v < 225) {
			printf("Pressed\n");
		} else {
			printf("Not Pressed\n");
		}
		sleep(1);
	}

	//CLOSE DEVICE
	printf("Closing device\n");
	close(file);
}

void init(int lResolution, int rResolution, float dist, int startAsserv) {
	robot_init();
	encoder_SetDist(dist);
	encoder_SetResolution(lResolution, rResolution);
	initLog(lResolution, rResolution, dist);
	printf("Encoders resolution: %d %d , distance: %f\n", lResolution,
			rResolution, dist);
	if (startAsserv > 0) {
		motion_Init();
	}
}
void motionLine(int mm) {

	RobotCommand* cmd = malloc(sizeof(RobotCommand));
	float meters = mm / 1000.0f;
	motion_Line(cmd, meters);
	printf("Loading line command for %d mm (%f meters)\n", mm, meters);
	motion_SetCurrentCommand(cmd);
	int i = 0;
	int nbSec = 10;
	for (i = 0; i < 200 * nbSec; i++) {
		// loop because timer with kill
		sleep(1);
	}
	free(cmd);
	closeLog();
	printf("test motion end\n");
}

void motionRotate(int degres) {

	RobotCommand* cmd = malloc(sizeof(RobotCommand));
	float rad = (degres * M_PI) / 180.0;
	// 90 cms
	motion_Rotate(cmd, rad);
	//motion_Line(cmd, .90f);
	printf("Loading rotate command %d degres (%f rad)\n", degres, rad);
	motion_SetCurrentCommand(cmd);

	int i = 0;
	int nbSec = 10;
	for (i = 0; i < 200 * nbSec; i++) {
		// loop because timer with kill
		sleep(1);
	}
	free(cmd);
	closeLog();
	printf("test motion end\n");
}

void testEncoders() {
	robot_init();
	int i;
	printf("Reading encoder during 20s\n");
	for (i = 0; i < 20; i++) {
		printf("testInit : left: %ld right: %ld \n",
				robot_getLeftExternalCounter(),
				robot_getRightExternalCounter());
		sleep(1);
	}
}
int main(int argc, const char* argv[]) {
#ifdef SIMULATED
	printf("Simulation mode enabled\n");
#endif

	// Prints each argument on the command line.
	int i;
	for (i = 0; i < argc; i++) {
		printf("arg %d: %s\n", i, argv[i]);
	}
	if (argc != 3) {
		printf("Utilisation : EV3 commande parametre\n");
		printf("Examples:\n");
		printf(
				"- rotation sur la droite de 90 degres :        EV3 rotate 90\n");
		printf(
				"- avance de 500mm en ligne droite :            EV3 line  500\n");
		printf(
				"- mise à 100 des moteurs pendant 5s :          EV3 test0 null\n");
		printf(
				"- affiche les codeurs externes 30s :           EV3 test1  30\n");
		printf(
				"- avance et affiche les codeurs externes 5s :  EV3 test2   5\n");
		printf(
				"- avance pour reglage PID sur 300mm :          EV3 pidAD 300\n");
		return 0;
	}
	if (strcmp(argv[1], "test0") == 0) {
		test();
	} else {
		int lRes = 3800;
		int rRes = 3800;
		float dist = 0.128f;

		if (strcmp(argv[1], "line") == 0) {
			init(lRes, rRes, dist, 1);
			int mm = atoi(argv[2]);
			motionLine(mm);
		} else if (strcmp(argv[1], "rotate") == 0) {
			init(lRes, rRes, dist, 1);
			int degres = atoi(argv[2]);
			motionRotate(degres);
		} else if (strcmp(argv[1], "test0") == 0) {
			init(lRes, rRes, dist, 0);
			test();
		} else if (strcmp(argv[1], "test1") == 0) {
			init(lRes, rRes, dist, 0);
			int secs = atoi(argv[2]);
			testExternalCounters(secs, 0);
		} else if (strcmp(argv[1], "test2") == 0) {
			init(lRes, rRes, dist, 0);
			int secs = atoi(argv[2]);
			testExternalCounters(secs, 1);
		} else if (strcmp(argv[1], "pidAD") == 0) {
			int mm = atoi(argv[2]);
			init(lRes, rRes, dist, 1);
			RobotCommand* cmd = malloc(sizeof(RobotCommand));
			float meters = mm / 1000.0f;

			motion_StepOrderAD(cmd, 0.0f, meters / valueVTops);
			printf("Check cmd\n");
			checkRobotCommand(cmd);
			printf("Loading StepOrderAD command for %d mm (%f meters)\n", mm,
					meters);

			path_LaunchTrajectory(cmd);
			printf("path_WaitEndOfTrajectory\n");
			//int result = path_WaitEndOfTrajectory();

			//	printf("path_WaitEndOfTrajectory returned : %d : %d\n", result,
			//			TRAJ_OK);

			sleep(5);

			robot_setMotorLeftSpeed(0);
			robot_setMotorRightSpeed(0);
			free(cmd);
			closeLog();

		} else {
			printf("Commande %s inconnue\n", argv[1]);
		}
	}

//testEncoders();
//test();
//testExternalCounters();
//test_motor_encoder();
//calibrate();
//testMotionLine();
//testMotionRotate90();
//motion_DoRotate(M_PI*1.0f);
	printf("Bye\n");
	return 0;
}
