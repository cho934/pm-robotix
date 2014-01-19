#pragma platform(NXT)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! @file      pmusic.c
//! @brief     This file manages music on the NXT.
//! @author    CHO
//! @copyright You may use this code as you wish, provided you give credit where its due.
//! @date      2012/03/05
//! @version   1.01
//! @par       LOG:
//! @code
//! WHO  WHEN        VERSION WHAT
//! ---------------------------------------------------------------------------------------------------------------------------
//! CHO  2012/03/05  1.01    Add: unit Tests
//!                          Chg: organization of sections.
//!
//! CHO  2012/03/05  1.00    Creation
//! @endcode
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _PMX_MUSIC
#define _PMX_MUSIC // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "pmusic.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _PMX_MUSIC_H__
#include "pmusic.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES
// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: EXTERNAL SOURCES
// END OF:  EXTERNAL SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES
static int pmxMusOneNoteDuration = 15;
static int pmxMusHoleAfterNote = 3;
// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>




//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES

// Convert note value to frequency
int stringToTone(string val)
{
	// 3
	if (val=="A3") {return 220;}
	if (val=="#A3") {return 233;}
	if (val=="B3") {return 247;}
	// 4
	if (val=="C4") {return 262;}
	if (val=="#C4") {return 277;}
	if (val=="D4") {return 294;}
	if (val=="#D4") {return 311;}
	if (val=="E4") {return 330;}
	if (val=="F4") {return 349;}
	if (val=="#F4") {return 370;}
	if (val=="G4") {return 392;}
	if (val=="#G4") {return 415;}
	if (val=="A4") {return 440;}
	if (val=="#A4") {return 466;}
	if (val=="B4") {return 494;}
	// 5
	if (val=="C5") {return 523;}
	if (val=="#C5") {return 554;}
	if (val=="D5") {return 587;}
	if (val=="#D5") {return 622;}
	if (val=="E5") {return 659;}
	if (val=="F5") {return 698;}
	if (val=="#F5") {return 740;}
	if (val=="G5") {return 784;}
	if (val=="#G5") {return 831;}
	if (val=="A5") {return 880;}
	if (val=="#A5") {return 932;}
	if (val=="B5") {return 988;}
	// 6
	if (val=="C6") {return 1046;}
	if (val=="#C6") {return 1109;}
	if (val=="D6") {return 1175;}
	if (val=="#D6") {return 1245;}
	if (val=="E6") {return 1319;}
	if (val=="F6") {return 1397;}
	if (val=="#F6") {return 1480;}
	if (val=="G6") {return 1568;}
	if (val=="#G6") {return 1661;}
	if (val=="A6") {return 1760;}
	if (val=="#A6") {return 1865;}
	if (val=="B6") {return 1976;}
	return 0;
}

// Play note for duration
void note(string val, int duration)
{
	if(val=="0")
	{
		wait10Msec(duration*pmxMusOneNoteDuration);
		}else{
		PlayTone(stringToTone(val),(duration*pmxMusOneNoteDuration)-pmxMusHoleAfterNote);
		wait10Msec(duration*pmxMusOneNoteDuration);
	}
}

// Play a whole mesure
void playMesure(string mesure)
{
	int size = strlen(mesure);
	string noteVal;
	string duration_string;
	int duration;
	while(size>0)
	{
		noteVal = mesure;
		StringDelete(mesure, 0, 4);
		StringDelete(noteVal, 4, size-4);
		duration_string = noteVal;
		StringDelete(duration_string, 1, 3);
		StringDelete(noteVal, 0, 1);
		duration = atoi(duration_string);
		strTrim(noteVal);
		note(noteVal,duration);
		size = strlen(mesure);
	}
}
// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: TESTS

#if(PROJECT_MAIN_FILE == "pmusic.c")
	//-----------------------------------------------------------------------------------------------------------------------------
	//! @brief     this task tests the functions
	//! @return    none
	//! @author    cho
	//! @note
	//! @todo
	//-----------------------------------------------------------------------------------------------------------------------------
	task main()
	{
		nxtDisplayCenteredTextLine(0, "UNIT TEST");

	  string val = "A3";
	  note(val, 2);

  	string mesure ;
		mesure = "1A3 1C4 "; playMesure(mesure);
		mesure = "2D4 2D4 1D4 1E4 "; playMesure(mesure);
		mesure = "2F4 2F4 1F4 1G4 "; playMesure(mesure);


	}
#endif // (PROJECT_MAIN_FILE)

// END OF:  TESTS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif
