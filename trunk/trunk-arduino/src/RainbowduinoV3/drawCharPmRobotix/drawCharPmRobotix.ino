/*
 Print "text" value (one letter after one), with a random color.
 based on "drawChar" example
*/

#include <Rainbowduino.h>

char* text = "PM-ROBOTIX";

void setup()
{
  Rb.init();
}

//unsigned char x,y,z;

void loop()
{
  for(int i=0; i<strlen(text); i++)
  {
     Rb.drawChar(text[i],0,1,random(0xFFFFFF)); 
     delay(500);
     Rb.blankDisplay();
  }
  
}




