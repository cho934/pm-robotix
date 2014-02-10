/*
 * test.c
 *
 *  Created on: Dec 1, 2013
 *      Author: maillard
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include  <sys/mman.h>
#include <sys/ioctl.h>
#include "lms2012.h"



// A = 0x01, B = 0x02, C = 0x04, D = 0x08

int test_motor_encoder()
{
	int motorSpeed=19;
	int motorLeft= 0x02;
	int motorRight= 0x04;

	MOTORDATA *pMotorData;

	char motor_command[4];
	int motor_file;
	int encoder_file;
	int i;
	//Open the device file asscoiated to the motor controlers
	if((motor_file = open(PWM_DEVICE_NAME, O_WRONLY)) == -1)
	{
		printf("Failed to open device\n");
		return -1; //Failed to open device
	}
	//Open the device file asscoiated to the motor encoders
	if((encoder_file = open(MOTOR_DEVICE_NAME, O_RDWR | O_SYNC)) == -1)
		return -1; //Failed to open device
	pMotorData  =  (MOTORDATA*)mmap(0, sizeof(MOTORDATA)*vmOUTPUTS, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, encoder_file, 0);
	if (pMotorData == MAP_FAILED)
	{
		printf("Map failed\n");
		return -1;
	}
	// All motor operations use the first command byte to indicate the type of operation
	// and the second one to indicate the motor(s) port(s)
	motor_command[0] = opOUTPUT_SPEED;
	motor_command[1] = motorLeft;
	motor_command[2] = motorSpeed;
	write(motor_file,motor_command,3);
	motor_command[0] = opOUTPUT_SPEED;
	motor_command[1] = motorRight;
	motor_command[2] = motorSpeed;
	write(motor_file,motor_command,3);
	// Start the motor
	motor_command[0] = opOUTPUT_START;
	motor_command[1] = motorLeft | motorRight;
	write(motor_file,motor_command,2);
	// Read encoders while running the motor
	int startLeft=pMotorData[1].TachoSensor;
	int startRight=pMotorData[2].TachoSensor;

	for(i=1;i<6;i++){
		printf("Spd/Cnt/Snr: L=%d/%d/%d R=%d/%d/%d\n",\
				pMotorData[1].Speed,pMotorData[1].TachoCounts,pMotorData[1].TachoSensor,\
				pMotorData[2].Speed,pMotorData[2].TachoCounts,pMotorData[2].TachoSensor);
		printf("Left:%d Right:%d\n",pMotorData[1].TachoSensor-startLeft, pMotorData[2].TachoSensor-startRight);
		sleep(1);
	}
		// Stop the motor
	motor_command[0] = opOUTPUT_STOP;
	write(motor_file,motor_command,2);
	// Close device files

	printf("Left:%d Right:%d\n",pMotorData[1].TachoSensor-startLeft, pMotorData[2].TachoSensor-startRight);

	close(encoder_file);
	close(motor_file);
	return 0;
}
