#pragma config(Sensor, S1,     HTANG_LEFT,     sensorI2CCustom)
#pragma config(Sensor, S4,     HTANG_RIGHT,    sensorI2CCustom)
#pragma config(Sensor, S2,     TOUCH_SENSOR,    sensorTouch)
#pragma config(Sensor, S3,     SONAR,          sensorSONAR)
#pragma config(Motor,  motorA,          MOTOR_LEFT,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          MOTOR_RIGHT,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          MOTOR_PUSH,   tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma platform(NXT)



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "pmMain.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES
// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: EXTERNAL SOURCES
#include "crobotTrajWrappers.c"
#include "pmInit.c"
#include "iaMain.c"
#include "pmSensors.c"

// END OF:  EXTERNAL SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES
// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES

#if(PROJECT_MAIN_FILE == "pmMain.c")

task main()
{

	//waits for the initialisation
	pmInitWaitForStart();

	//init motion and StartTask
	motion_Init();

	//init Sensors
	sensors_Init();

	//init IA
	ia_Init();

	// Starts the IA
	ia_start();



	//GO 90s
	Sleep(90000);

	// Stop all motors

	//Stop tasks and Robot
	StopAllTasks();
}


// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif
