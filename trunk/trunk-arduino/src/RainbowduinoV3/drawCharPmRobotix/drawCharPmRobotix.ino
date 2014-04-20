/*
 Print "text" value (one letter after one), with a random color.
 based on "drawChar" example
 
 text can be updated by i2c (see i2cMaster)
*/

#include <Rainbowduino.h>
#include <Wire.h>

char* text = "PM-ROBOTIX                                    ";
int textSize = 11;

void setup()
{
  Rb.init();
  
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
}


void loop()
{
  for(int i=0; i<textSize; i++)
  {
     Rb.drawChar(text[i],0,1,random(0xFFFFFF)); 
     delay(500);
     Rb.blankDisplay();
  } 
}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  textSize = howMany;
  for(int i=0; i<textSize; i++)
  {
    text[i] =  Wire.read();
  }
}
