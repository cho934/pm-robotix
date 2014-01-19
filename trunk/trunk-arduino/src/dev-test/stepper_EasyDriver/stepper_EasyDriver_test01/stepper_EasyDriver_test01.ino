///////////////////////////////////////////////////////////
// Arduino 155
// Stepper Motor skecth for use with the EasyDriver v4.4 //
///////////////////////////////////////////////////////////
 
// Based on Dan Thompson 2010
// For all the product details visit http://www.schmalzhaus.com/EasyDriver/
// For the full tutorial visit http://danthompsonsblog.blogspot.com/
 
 
////// ED_v4  Step Mode Chart //////
//                                //
//   MS1 MS2 Resolution           //
//   L   L   Full step (2 phase)  //
//   H   L   Half step            //
//   L   H   Quarter step         //
//   H   H   Eighth step          //
//                                //
////////////////////////////////////

//pin definition
int DIR = 2;        
int STEP = 3;        
int MS1 = 4;        
int MS2 = 5;         
int SLEEP = 6;  

int nbStep = 48; //Number of steps for this test
 
void setup() {
  Serial.begin(115200);     // open the serial connection at 9600bps
  pinMode(DIR, OUTPUT);   // set to output
  pinMode(STEP, OUTPUT);  // set to output
  pinMode(MS1, OUTPUT);   // set to output
  pinMode(MS2, OUTPUT);   // set to output
  pinMode(SLEEP, OUTPUT); // set to output
}

void loop()
{
  int modeType = 1;                         // This number increases by multiple of 2 each through the while loop..
                                            // ..to identify our step mode type.                                           
  while (modeType<=8){                      // loops the following block of code 4 times before repeating .
    digitalWrite(DIR, LOW);                 // Set the direction change LOW to HIGH to go in opposite direction
    digitalWrite(MS1, MS1_MODE(modeType));  // Set state of MS1 based on the returned value from the MS1_MODE() switch statement.
    digitalWrite(MS2, MS2_MODE(modeType));  // Set state of MS2 based on the returned value from the MS2_MODE() switch statement.
    digitalWrite(SLEEP, HIGH);              // Set the Sleep mode to AWAKE.
     
    int i = 0;                              // Set the counter variable.    
    while(i<(modeType*nbStep))                 // Iterate for 48, 96, 192, 284 steps. Then reset to 48 and start again.
    {
      digitalWrite(STEP, LOW);              // This LOW to HIGH change is what creates the..
      digitalWrite(STEP, HIGH);             // .."Rising Edge" so the easydriver knows to when to step.
      //delayMicroseconds(1600/modeType);   // This delay time determines the speed of the stepper motor. Delay shortens from 1600 to 800 to 400 to 200 then resets.
      //delay(100/modeType);                // This delay time determines the speed of the stepper motor. Delay shortens from 100 to 50 to 25 to 17 then resets.
      
      switch(modeType){                // This delay time determines the speed of the stepper motor. Delay shortens from 10 to 5 to 2.5 to 1.75ms then resets.                                                
        case 1:
          delay(10);
          break;
        case 2:
          delay(5);
          break;
        case 4:
          delayMicroseconds(2500);
          break;
        case 8:
          delayMicroseconds(1750);
          break;
      }
      i++;
    }   
    Serial.print(">> ");    
    Serial.println(modeType*nbStep);
    modeType = modeType * 2;                // Multiply the current modeType value by 2 and make the result the new value for modeType.
                                            // This will make the modeType variable count 1,2,4,8 each time we pass though the while loop.
    delay(500);
  }
  digitalWrite(SLEEP, LOW);                 // switch off the power to stepper
  Serial.print("SLEEPING..");
  delay(1000);
  Serial.print("z");
  delay(1000);
  Serial.print("z");
  delay(1000);
  Serial.print("z");
  delay(1000);
  Serial.println("");
  digitalWrite(SLEEP, HIGH);
  Serial.println("AWAKE!!!");                // Switch on the power to stepper
  delay(1000);
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

