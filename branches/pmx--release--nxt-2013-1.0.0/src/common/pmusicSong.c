///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! @file      pmusicSong.c
//! @brief     This file manages songs on the NXT.
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
#ifndef _PMX_MUSICSONG
#define _PMX_MUSICSONG // prevent multiple compilations


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "pmusicSong.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _PMX_MUSICSONG_H_
#include "pmusicSong.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES
// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: EXTERNAL SOURCES

#include "pmusic.c"
// END OF:  EXTERNAL SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES
// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES


void playSong1()
{
	string mesure ;
	mesure = "1A3 1C4 "; playMesure(mesure);
	mesure = "2D4 2D4 1D4 1E4 "; playMesure(mesure);
	mesure = "2F4 2F4 1F4 1G4 "; playMesure(mesure);
	mesure = "2E4 2E4 1D4 1C4 "; playMesure(mesure);
	mesure = "2D4 20  1A3 1C4 "; playMesure(mesure);

	/*
  // 7. 1st verse
  playMesure("1A3 1C4 ");
  playMesure("2D4 2D4 1D4 1E4 ");
  playMesure("2F4 2F4 1F4 1G4 ");
  playMesure("2E4 2E4 1D4 1C4 ");
  playMesure("2D4 20  1A3 1C4 ");
  // 11. 2nd verse
  playMesure("2D4 2D4 1D4 1E4 ");
  playMesure("2F4 2F4 1F4 1G4 ");
  playMesure("2E4 2E4 1D4 1C4 ");
  playMesure("2D4 20  1A3 1C4 ");
  // 15. 3rd verse
  playMesure("2D4 2D4 1D4 1F4 ");
  playMesure("2G4 2G4 1G4 1A4 ");
  playMesure("2#A42#A41A4 1G4 ");
  playMesure("2D4 20  1D4 1E4 ");
  // 19. BREAK
  playMesure("2F4 2F4 2G4 ");
  playMesure("1A4 2D4 10  1D4 1F4 ");
  playMesure("2E4 2E4 1F4 1D4 ");
  playMesure("2E4 20  1A4 1C5 ");
  // SECOND PART
  // 23. 1st verse
  playMesure("2D5 2D5 1D5 1E5 ");
  playMesure("2F5 2F5 1F5 1G5 ");
  playMesure("2E5 2E5 1D5 1C5 ");
  playMesure("2D5 20  1A4 1C5 ");
  // 27. 2st verse
  playMesure("2D5 2D5 1D5 1E5 ");
  playMesure("2F5 2F5 1F5 1G5 ");
  playMesure("2E5 2E5 1D5 1C5 ");
  playMesure("2D5 20  1A4 1C5 ");
  // 31. 3rd verse
  playMesure("2D5 2D5 1D5 1F5 ");
  playMesure("2G5 2G5 1G5 1G5 ");
  playMesure("2#A52#A51A5 1G5 ");
  playMesure("1A5 2D5 10  1D5 1E5");
  // 35. BREAK
  playMesure("2F5 2F5 2G5 ");
  playMesure("1A5 2D5 10  1D5 1F5 ");
  playMesure("2E5 2E5 1D5 1C5 ");
  playMesure("2D5 2D5 2E5 ");
  playMesure("2F5 1F5 1F5 2G5 ");
  playMesure("1A5 1F5 20  1F5 1D5 ");
  // 41.
  playMesure("1A4 50  ");
  playMesure("1#A530  1G5 1D5 ");
  playMesure("1#A450  ");
  playMesure("1E4 2E4 3D4 ");
  playMesure("3F4 10  1F4 1G4 ");
  // THIRD PART
  // 46. 1st verse
  playMesure("2A4 2A4 2A4 ");
  playMesure("1#A41A4 40  ");
  playMesure("2G4 2G4 2G4 ");
  playMesure("1G4 1A4 40  ");
  playMesure("2A4 2A4 2A4 ");
  playMesure("1#A41A4 40  ");
  // 52. 2nd verse
  playMesure("2G4 2F4 2E4 ");
  playMesure("2D4 20  1D4 1E4 ");
  playMesure("4F4 1G4 1A4 ");
  playMesure("2G4 2F4 2E4 ");
  playMesure("2F4 2G4 2A4 ");
  // 57.
  playMesure("2G4 20  1F4 1G4 ");
  playMesure("2A4 20  1G4 1F4 ");
  playMesure("2E4 2F4 2D4 ");
  playMesure("2D4 20  1E4 1C4 ");
  playMesure("1D4 30  1D5 1E5 ");
  // 62.
  playMesure("2F5 20  1E5 1F5 ");
  playMesure("2G5 2F5 2G5 ");
  playMesure("2A5 2G5 2F5 ");
  playMesure("2D5 20  1D5 1E5 ");
  playMesure("2F5 2G5 2A5 ");
  // 67.
  playMesure("2#A52D5 2G5 ");
  playMesure("2F5 20  1G5 1E5 ");
  playMesure("2D5 20  1E5 1#C5");
  playMesure("2A5 40  ");
  playMesure("2#A540  ");
  // 72.
  playMesure("2A5 2A5 2A5 ");
  playMesure("1A5 1G5 40  ");
  playMesure("2G5 40  ");
  playMesure("2F5 40  ");
  playMesure("2F5 2G5 2E5 ");
  // 77.
  playMesure("3D5 1D5 1E5 1F5 ");
  playMesure("3A5 1D5 1E5 1F5 ");
  playMesure("3#A51D5 1E5 1F5 ");
  playMesure("2A5 2A5 2C6 ");
  playMesure("1A5 1G5 40  ");
  // 82.
  playMesure("2G5 40  ");
  playMesure("2F5 40  ");
  playMesure("2F5 2G5 2E5 ");
  playMesure("3D5 30  ");
  playMesure("5D4 10  ");
  */
}

task song1Task()
{
	playSong1();
}
// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: TESTS

#if(PROJECT_MAIN_FILE == "pmusicSong.c")
	//-----------------------------------------------------------------------------------------------------------------------------
	//! @brief     this task tests the functions
	//! @return    none
	//! @author    cho
	//! @note
	//! @todo
	//-----------------------------------------------------------------------------------------------------------------------------
	task main()
	{
		//Display
  	nxtDisplayCenteredTextLine(0, "UNIT TEST");
	  playSong1();

	  //Play all Song1 with a new task
		StartTask(song1Task, 5);

	}
#endif // (PROJECT_MAIN_FILE)

// END OF:  TESTS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif
