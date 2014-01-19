/*
  Encoder.cpp - - Interface library for chip LS7366R that does quadrature decoding 
                of rotary encoders.  Library for Wiring/Arduino - Version 0017
  
  Original library     (0.1) by Jeff Bingham.

  More information can be found here:
  http://pendulum.binghamsite.com/rotary-encoders 
*/


#include "WProgram.h"
#include "Encoder.h"

/*
 * Encoder constructor.
 */
Encoder::Encoder(int slave_select_pin)
{
  this->counterSize = 2; //n-byte counter
  this->prevStatus = 0; //status register from previous read
  this->prevCount = 0; //count from previous read
  this->prevTime = millis(); //time stamp of previous read
  this->prevDiff = 0; //difference in coundt from previous read
  this->ss_pin = slave_select_pin; //slave select pin
  
  // setup the pins on the microcontroller
  pinMode(this->ss_pin, OUTPUT);
  digitalWrite(this->ss_pin, HIGH); //delay(10); //disable device
}

/*
  Initialize the encoder to the SPI with a default free-running 2-byte counter
 */

void Encoder::initialize(void)
{
  //Clear LS7366
  this->clearCounter(); //clear counter
  this->clearStatus(); //clear status
  
  //Setup LS7366
  digitalWrite(this->ss_pin,LOW); //enable device
  this->spiTransfer(WRITE_MODE0);     //filter divisor=1; async idx; idx off;
  this->spiTransfer((char)B00000011); //free running cnt; 4x quad cnt
  digitalWrite(this->ss_pin,HIGH); //release device
  digitalWrite(this->ss_pin,LOW); //enable device
  this->spiTransfer(WRITE_MODE1);
//  this->spiTransfer((char)B00000011); // 1-byte counter
  this->spiTransfer((char)B00000010); // 2-byte counter
//  this->spiTransfer((char)B00000001); // 3-byte counter
//  this->spiTransfer((char)B00000000); // 4-byte counter
  digitalWrite(this->ss_pin,HIGH); //release device
}

/*
  Initialize the encoder to the SPI with your own desired parameters
 */

void Encoder::initialize(int setup_mdr0, int setup_mdr1)
{
  this->counterSize = 4 - (((byte)setup_mdr1) & B00000011); //n-byte counter

  //Clear LS7366
  this->clearCounter(); //clear counter
  this->clearStatus(); //clear status
  
  //Setup LS7366
  digitalWrite(this->ss_pin,LOW); //enable device
  this->spiTransfer(WRITE_MODE0);
  this->spiTransfer((char)setup_mdr0);
  digitalWrite(this->ss_pin,HIGH); //release device
  digitalWrite(this->ss_pin,LOW); //enable device
  this->spiTransfer(WRITE_MODE1);
  this->spiTransfer((char)setup_mdr1);
  digitalWrite(this->ss_pin,HIGH); //release device
}

/*
  Used for transferring all data along the SPI
*/
char Encoder::spiTransfer(volatile char data)
{
  SPDR = data;                    // Start the transmission
//  delayMicroseconds(10);        // Might be required for IC timing
  while (!(SPSR & (1<<SPIF)))     // Wait for end of the transmission
  {
  };
  return SPDR;                    // return the received byte
}

/*
  Used for clearing the counter
*/
void Encoder::clearCounter(void)
{
  digitalWrite(this->ss_pin,LOW); //enable device
  this->spiTransfer(CLEAR_COUNTER); //transmit clear opcode
  digitalWrite(this->ss_pin,HIGH); //release device
  return;
}

/*
  Used for clearing the Status
*/
void Encoder::clearStatus(void)
{
  digitalWrite(this->ss_pin,LOW); //enable device
  this->spiTransfer(CLEAR_STATUS); //transmit clear opcode
  digitalWrite(this->ss_pin,HIGH); //release device
  return;
}

/*
  Used for reading the counter
*/
unsigned long Encoder::readCounter(void)
{
  unsigned char data;
  unsigned long returnVal = 0;
  digitalWrite(this->ss_pin,LOW);
  this->spiTransfer(READ_COUNTER);
  for(char i=this->counterSize; i>0; i--)
  {
    data = this->spiTransfer(0x00);
    returnVal = returnVal*255 + data;
  }
  return returnVal;
}

/*
  Used for reading the status
*/
unsigned char Encoder::readStatus(void)
{
  unsigned char data;
  digitalWrite(this->ss_pin,LOW); //enable device
  this->spiTransfer(READ_STATUS); //transmit read opcode
  data = this->spiTransfer(0xFF); //get data byte
  digitalWrite(this->ss_pin,HIGH); //release device
  return data;
}

