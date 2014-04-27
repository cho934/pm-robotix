#pragma config(Sensor, S1,     HTANG_RIGHT,    sensorI2CCustom)
#pragma config(Sensor, S4,     HTANG_LEFT,     sensorI2CCustom)
#pragma config(Sensor, S2,     TOUCH_SENSOR,    sensorTouch)
#pragma config(Sensor, S3,     SONAR,          sensorSONAR)
#pragma config(Motor,  motorA,          MOTOR_RIGHT,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          MOTOR_LEFT,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          MOTOR_PUSH,   tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(NXT)


#ifndef _PMINIT__
#define _PMINIT__ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "pmInit.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#include "pmInit.h"
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES

PM_INIT_COLOR pmInitColor = PM_INIT_COLOR_BLUE;
PM_INIT_IA pmInitIA = PM_INIT_IA_HOMOLOG;


// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: EXTERNAL SOURCES
// END OF:  EXTERNAL SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES

int PM_INIT_TIME_BUTTON = 10;

// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES

// Main method
void pmInitWaitForStart()
{

	// Returns only when the game is launched

	// 0 |	  PMX - 2013
	// 1 |
	// 2 |  Initialisation
	// 3 |			 ---
	// 4 |
	// 5 |		<Function>
	// 6 |		 <choice>
	// 7 |

	// nxtDisplayCenteredBigTextLine: MAX 8 chars
	// nxtDisplayCenteredTextLine: MAX 16 chars

	// Gray button to change the function
	// Left and right buttons to change the value of the function
	// Pull to launch the robot

	// Displays interface
	nxtDisplayCenteredBigTextLine(0, "PMX-2013");
	nxtDisplayCenteredTextLine(2, "initialisation");
	nxtDisplayCenteredTextLine(3, "---");
	writeDebugStreamLine("PMX > Init > Initialisation of the robot");

	// Change the parameters of the IA
	int choice;
	int canrun = 0;
	// current choice
	//  0: Color
	//  1: IA
	int currentChoiceInit = 0;

	while (canrun	 == 0) {
		pmInitDisplayOption(currentChoiceInit);
		choice = pmInitGetInteraction();
		if (choice == 0) {
			// Gray
			//writeDebugStreamLine("PMX > Init > Click on Gray > KILL");
			// This button automatically kills the program.
		}
		if (choice == 1) {
			// Right
			//writeDebugStreamLine("PMX > Init > Click on Right");
			pmInitChangeChoice(1, currentChoiceInit);
		}
		if (choice == 2) {
			// Left
			//writeDebugStreamLine("PMX > Init > Click on Left");
			pmInitChangeChoice(0, currentChoiceInit);
		}
		if (choice == 3) {
			// Orange
			//writeDebugStreamLine("PMX > Init > Click on Orange");
			currentChoiceInit = pmInitChangeOption(currentChoiceInit);
		}
		if (choice == 4) {
			// Pull
			//writeDebugStreamLine("PMX > Init > START");
			nxtDisplayClearTextLine(6);
			nxtDisplayCenteredTextLine(6, "GO !");
			canrun = 1;
		}
	}

}

// This methods returns only if a button was pressed, or launching the robot.
//		Gray		0
//		Left		1
//		Right		2
//		Orange	3
//		Pull		4
// No modification of the constants here.
int pmInitGetInteraction() {

	int currentChoice = -1;

	while (currentChoice == -1) {
		if (nNxtButtonPressed != -1) {
			currentChoice = nNxtButtonPressed;
			// This is to avoid "short press" of a button
			int durationLeft = PM_INIT_TIME_BUTTON;
			while (durationLeft > 0 && currentChoice == nNxtButtonPressed) {
				durationLeft--;
			}
			if (durationLeft == 0) {
				while (nNxtButtonPressed != -1) {}
			} else {
				// False detection
				currentChoice = -1;
			}
		}
		if(SensorValue(SONAR)<10)
    {
    	nVolume = 4;
    	writeDebugStreamLine("wally !");
      PlaySoundFile("wally.rso");
      while(SensorValue(sonar)<20){}
      while (bSoundActive){}
      nVolume = 1;
    }
		if (SensorValue(TOUCH_SENSOR) == 0) {
			return 4;
		}
	}

	return currentChoice;
}

// Displays the current option in line 5, the current choice in line 6
void pmInitDisplayOption(int currentChoice)
{
	nxtDisplayClearTextLine(5);
	nxtDisplayClearTextLine(6);
	switch (currentChoice)
	{
		case 0:
			// COLOR
			nxtDisplayCenteredTextLine(5, "COLOR");
			switch (pmInitColor)
			{
				case PM_INIT_COLOR_RED:
					nxtDisplayCenteredTextLine(6, "RED");
					break;
				case PM_INIT_COLOR_BLUE:
					nxtDisplayCenteredTextLine(6, "BLUE");
					break;
				default:
					nxtDisplayCenteredTextLine(6, "Error");
					break;
			}
			break;
		case 1:
			// IA
			nxtDisplayCenteredTextLine(5, "IA type");
			switch (pmInitIA)
			{
				case PM_INIT_IA_TEST:
					nxtDisplayCenteredTextLine(6, "TEST");
					break;
				case PM_INIT_IA_TABLE_TEST:
					nxtDisplayCenteredTextLine(6, "TABLE TEST");
					break;
				case PM_INIT_IA_HOMOLOG:
					nxtDisplayCenteredTextLine(6, "HOMOLOGATION");
					break;
				case PM_INIT_IA_MATCH:
					nxtDisplayCenteredTextLine(6, "MATCH");
					break;
				default:
					nxtDisplayCenteredTextLine(6, "Error");
					break;
			}
			break;
		default:
			// error - NIY
			nxtDisplayCenteredTextLine(5, "Error - Choice = %i", currentChoice);
			break;
	}
}

// Changes the option
int pmInitChangeOption(int currentChoice)
{
	int nextChoice = -1;
	switch (currentChoice)
	{
		case 0:
			nextChoice = 1;
			break;
		case 1:
			nextChoice = 0;
			break;
	}
	return nextChoice;
}

// Change the choice
void pmInitChangeChoice(int sens, int currentChoice)
{
	switch (currentChoice)
	{
		case 0:
			switch (pmInitColor)
			{
				case PM_INIT_COLOR_BLUE:
					pmInitColor = PM_INIT_COLOR_RED;
					break;
				case PM_INIT_COLOR_RED:
					pmInitColor = PM_INIT_COLOR_BLUE;
					break;
			}
			writeDebugStreamLine("PMX > Init > color changed");
			break;
		case 1:
			switch (pmInitIA)
			{
				case PM_INIT_IA_TEST:
					if (sens == 1)
					{
						pmInitIA = PM_INIT_IA_MATCH;
					} else {
						pmInitIA = PM_INIT_IA_TABLE_TEST;
					}
					break;
				case PM_INIT_IA_TABLE_TEST:
					if (sens == 1)
					{
						pmInitIA = PM_INIT_IA_TEST;
					} else {
						pmInitIA = PM_INIT_IA_HOMOLOG;
					}
					break;
				case PM_INIT_IA_HOMOLOG:
					if (sens == 1)
					{
						pmInitIA = PM_INIT_IA_TABLE_TEST;
					} else {
						pmInitIA = PM_INIT_IA_MATCH;
					}
					break;
				case PM_INIT_IA_MATCH:
					if (sens == 1)
					{
						pmInitIA = PM_INIT_IA_HOMOLOG;
					} else {
						pmInitIA = PM_INIT_IA_TEST;
					}
					break;
			}
			writeDebugStreamLine("PMX > Init > IA changed");
			break;
	}
}

// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: TESTS
#if(PROJECT_MAIN_FILE == "pmInit.c")
	//-----------------------------------------------------------------------------------------------------------------------------
	//! @brief     this task tests the interface
	//! @return    none
	//! @author    trip
	//! @note
	//! @todo
	//-----------------------------------------------------------------------------------------------------------------------------
	task main()
	{
		pmInitWaitForStart();
	}
#endif // (PROJECT_MAIN_FILE)

// END OF:  TESTS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif