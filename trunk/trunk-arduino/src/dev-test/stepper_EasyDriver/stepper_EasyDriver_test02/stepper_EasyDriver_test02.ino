///////////////////////////////////////////////////////////
// Arduino 155
// Stepper Motor skecth for use with the EasyDriver v4.4 //
///////////////////////////////////////////////////////////

////// ED_v4  Step Mode Chart //////
//                                //
//   MS1 MS2 Resolution           //
//   L   L   Full step (2 phase)  //
//   H   L   Half step            //
//   L   H   Quarter step         //
//   H   H   Eighth step          //
//                                //
////////////////////////////////////

#include <AccelStepper.h>

int MS1 = 4;        
int MS2 = 5; 
int SLEEP = 6; 

// Define a stepper and the pins it will use
AccelStepper stepper(1, 3, 2); //AccelStepper::DRIVER (1) ; Step input ;  Direction input
int pos = 3600;
void setup()
{  
  pinMode(MS1, OUTPUT);   
  pinMode(MS2, OUTPUT);   
  pinMode(SLEEP, OUTPUT);
  
  int modeType = 8; // Different input states allowed are 1, 2, 4 or 8
  
  digitalWrite(MS1, MS1_MODE(modeType));  // Set state of MS1 based on the returned value from the MS1_MODE() switch statement.
  digitalWrite(MS2, MS2_MODE(modeType));  // Set state of MS2 based on the returned value from the MS2_MODE() switch statement.
  digitalWrite(SLEEP, HIGH);              // Set the Sleep mode to AWAKE.
    
  
  stepper.setMaxSpeed(8000.0);
  stepper.setAcceleration(1000.0);
  stepper.setMinPulseWidth(100);
}
void loop()
{
  if (stepper.distanceToGo() == 0)
  {
    delay(500);
    pos = -pos;
    stepper.moveTo(pos);
  }
  stepper.run();
}


int MS1_MODE(int MS1_StepMode){              // A function that returns a High or Low state number for MS1 pin
  switch(MS1_StepMode){                      // Switch statement for changing the MS1 pin state
                                             // Different input states allowed are 1,2,4 or 8
  case 1:
    MS1_StepMode = 0;
    Serial.println("Step Mode is Full...");
    break;
  case 2:
    MS1_StepMode = 1;
    Serial.println("Step Mode is Half...");
    break;
  case 4:
    MS1_StepMode = 0;
    Serial.println("Step Mode is Quarter...");
    break;
  case 8:
    MS1_StepMode = 1;
    Serial.println("Step Mode is Eighth...");
    break;
  }

  return MS1_StepMode;
}
 
 
int MS2_MODE(int MS2_StepMode){              // A function that returns a High or Low state number for MS2 pin
  switch(MS2_StepMode){                      // Switch statement for changing the MS2 pin state
                                             // Different input states allowed are 1,2,4 or 8
  case 1:
    MS2_StepMode = 0;
    break;
  case 2:
    MS2_StepMode = 0;
    break;
  case 4:
    MS2_StepMode = 1;
    break;
  case 8:
    MS2_StepMode = 1;
    break;
  }
  return MS2_StepMode;
}

