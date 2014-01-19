#pragma config(Sensor, S1,     DPRESS,              sensorAnalogInactive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * dexterind-pressure.h provides an API for the Dexter Industries dPressure sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Dexter Industries for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.55 beta 2 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 13 June 2010
 * version 0.1
 */

#include "drivers/dexterind-pressure.h"

task main() {
  float pressure;
  byte state = 0;

  nxtDisplayTextLine(0, "Dexter Industries");
  nxtDisplayCenteredTextLine(1, "dPressure 250");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect sensor");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);
  eraseDisplay();

  nxtDisplayTextLine(0, "Dexter Industries");
  nxtDisplayCenteredTextLine(7, "< switch scale >");
  //loop to read temp
  while (true) {
    switch(nNxtButtonPressed) {
      // If the right button is pressed, cycle through the scales
      case kRightButton:
        if (++state > 1)
          state = 0;
        while (nNxtButtonPressed != kNoButton) EndTimeSlice();
        break;

        // If the left button is pressed, cycle through the scales in reverse
      case kLeftButton:
        if (--state < 0)
          state = 1;
        // debounce the button
        while (nNxtButtonPressed != kNoButton) EndTimeSlice();
        break;
    }


    nxtDisplayCenteredBigTextLine(1, "Pressure:");
    switch(state) {
      // if state: 0, display temp in degrees celcius
      case 0: DPRESSreadPress250kPa(DPRESS, pressure);
              nxtDisplayCenteredBigTextLine(3, "%4.2f", pressure);
              nxtDisplayCenteredBigTextLine(5, "kPa");
              break;

      // if state: 1, display temp in Fahrenheit
      case 1: DPRESSreadPress250PSI(DPRESS, pressure);
              nxtDisplayCenteredBigTextLine(3, "%4.2f", pressure);
              nxtDisplayCenteredBigTextLine(5, "PSI.");
              break;
    }
    wait1Msec(10);
  }
}
