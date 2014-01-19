///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! @file      PMusicTest.c
//! @brief     This file is the main "musicTest" project file to play music.
//! @date      2013/03/05 (creation)
//! @author    cho
//! @copyright You may use this code as you wish, provided you give credit where its due.
//! @version   0.01
//! @todo      a lot of things :-)
//! @par       LOG:
//! @code
//! WHO  WHEN        VERSION WHAT
//!----------------------------------------------------------------------------------------------------------------------------
//! cho  2013/03/05  0.01    Chg: Organize c and h files.
//!
//! @endcode
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "PMusicTest.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#include "pmusicSong.h"
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES
// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: INCLUDED SOURCES
#include "pmusicSong.c"
// END OF:  INCLUDED SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES
// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES
#if (PROJECT_MAIN_FILE=="PMusicTest.c")
task main()
{
	//Display
  nxtDisplayCenteredTextLine(0, "PMX dev-test");
  nxtDisplayCenteredTextLine(1, "Music");
  nxtDisplayCenteredTextLine(2, "playSong");
	PlaySound(soundShortBlip);

  //Configuration volume
  nVolume = 4;

  //test
  string mesure ;
	mesure = "1A3 1C4 "; playMesure(mesure);
	mesure = "2D4 2D4 1D4 1E4 "; playMesure(mesure);

  //Play all Song1 with a new task
	StartTask(song1Task, 5);

}
#endif  //(PROJECT_MAIN_FILE)

// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
