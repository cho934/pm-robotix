/*
=================================================================================
 Name        : I2CSlave.ino
 Version     : 0.1

 Copyright (C) 2012 by Andre Wussow, 2012, desk@binerry.de

 Description :
     Sample of controlling an Arduino connected to Raspberry Pi via I2C.

	 Recommended connection (http://www.raspberrypi.org/archives/384):
	 Arduino pins      I2C-Shifter      Raspberry Pi
	 GND                                P06  - GND
	 5V                5V
	 SDA               SDA2
	 SCL               SCL2
	                   3V3              P01 - 3.3V
	                   SDA1             P03 - SDA
	                   SCL1             P05 - SCL
	 D2                                               LED1 with 1k resistor to GND
	 D3                                               LED2 with 1k resistor to GND
	 D4                                               LED3 with 1k resistor to GND
	 D5                                               Relay with transistor driver

 
 References  :
 http://binerry.de/post/27128825416/raspberry-pi-with-i2c-arduino-slave
 
================================================================================
This sample is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This sample is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
================================================================================
*/
 
#include "Commander.h"
#include "Wire.h"

/*
  General Setup
*/
// define i2c commands
#define LED1_ON_COMMAND    "L11"
#define LED1_OFF_COMMAND   "L10"
#define LED2_ON_COMMAND    "L21"
#define LED2_OFF_COMMAND   "L20"


// define slave address (0x2A = 42 [the answer to the ultimate question of life, the universe, and everything ;)] )
#define SLAVE_ADDRESS 0x2A 

// instantiate i2cCommander
Commander commander = Commander();

// pin setup
int led1pin = 13;
int led2pin = 3;

// other vars
int answer = 0;

void setup() {                
  
  Serial.begin(115200);              // Begin Serial Comunication
  
  // initialize the digital pins for leds and relay as an output
  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);  

  
  // create commands for i2cCommander
  // led 1:
  Command_t cmdLed1On;
  cmdLed1On.execCommand = LED1_ON_COMMAND;
  cmdLed1On.callback = led1On;
  
  Command_t cmdLed1Off;
  cmdLed1Off.execCommand = LED1_OFF_COMMAND;
  cmdLed1Off.callback = led1Off;
  
  // led 2:
  Command_t cmdLed2On;
  cmdLed2On.execCommand = LED2_ON_COMMAND;
  cmdLed2On.callback = led2On;
  
  Command_t cmdLed2Off;
  cmdLed2Off.execCommand = LED2_OFF_COMMAND;
  cmdLed2Off.callback = led2Off;
  
  
  // add commands to i2cCommander
  commander.addCommand(cmdLed1On);
  commander.addCommand(cmdLed1Off);
  commander.addCommand(cmdLed2On);
  commander.addCommand(cmdLed2Off);
  
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
   
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  
  Serial.print(" *** Setup ok: ");
  digitalWrite(led1pin, HIGH);
  delay(100);
  digitalWrite(led1pin, LOW);
  delay(100);
  digitalWrite(led1pin, HIGH);
  delay(100);
  digitalWrite(led1pin, LOW);
  delay(100);
}

void loop() {
  Serial.print("loop");
  delay(2000);
}

// callback for received data
void receiveData(int byteCount) 
{  
  String requestCommand = "";
  int w = Wire.available();
  Serial.print("w=");
  Serial.println(w);
  while(Wire.available())
  { 
     requestCommand = requestCommand + (char)Wire.read();
  }
  //requestCommand = requestCommand.substring(0,3); //4 caracters are received
  commander.processCommand(requestCommand);
}

// callback for sending data
void sendData()
{ 
  Wire.write(answer);  
  answer = 0;
}

void led1On(String command)
{
  Serial.println(" *** led1pin ON ");
  // switch led 1 on
  digitalWrite(led1pin, HIGH);
  
  // reply with command and success info
  answer = 1; 


}

void led1Off(String command)
{
  Serial.println(" *** led1pin OFF ");
  // switch led 1 off
  digitalWrite(led1pin, LOW);
  
  // reply with command and success info
  answer = 1; 

}

void led2On(String command)
{
  Serial.println(" *** led2pin ON ");
  // switch led 2 on
  digitalWrite(led2pin, HIGH);
  
  // reply with command and success info
  answer = 1; 
  
}

void led2Off(String command)
{
  Serial.println(" *** led2pin OFF ");
  // switch led 2 off
  digitalWrite(led2pin, LOW);
  
  // reply with command and success info
  answer = 1; 

}


