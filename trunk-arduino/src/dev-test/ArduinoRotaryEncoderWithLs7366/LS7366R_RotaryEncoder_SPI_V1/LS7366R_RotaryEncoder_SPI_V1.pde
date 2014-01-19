#include <Encoder.h>

//Arduino 0023

//Arduino pin setup
#define SLAVE0   9//ss0
#define SLAVE1   10//ss1
#define DATAOUT 11//MOSI 
#define DATAIN  12//MISO  
#define SPICLOCK  13//sck

Encoder encoderA(SLAVE1);

void setup()
{
  byte clr; //Variable for storing temporary "clear" data
  Serial.begin(9600);
  Serial.println("Nothing has happened yet");
  //Setup the pins for SPI communication
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK,OUTPUT);
  Serial.println("Arduino pins set"); //DEL
  //Setup the Arduino SPI control register: SPCR = 01010000
  //interrupt disabled,spi enabled,msb 1st,master,clk low when idle,
  //sample on rising edge of clk,system clock/4 rate (fastest)
  SPCR = (1<<SPE)|(1<<MSTR);
  //Clear the Arduino SPI status and data register
  clr=SPSR;
  clr=SPDR;
  Serial.println("Arduino cleared"); //DEL
  //setup LS7366
  //encoderA.initialize();
  encoderA.initialize(B10000011, 0); //MDRO=3 , MDR1=0  x4 and 4 bytes
  //Acknowledge setup
  delay(10);
  Serial.println("\nInitialized");
  delay(1000);
}

void loop()
{
  unsigned long count;
  byte count_status;
  count = encoderA.readCounter();
  encoderA.clearStatus();
  count_status = encoderA.readStatus();
  if(count_status & B00000010)
    Serial.print("UP - ");
  else
    Serial.print("DN - ");
  if(count_status & B00000001)
    Serial.print("NEG - ");
  else
    Serial.print("POS - ");
  Serial.print(count,DEC);
  if(count_status & B10000000)
  {
    Serial.print(" - OVERFLOW");
    encoderA.clearStatus();
  }
  if(count_status & B01000000)
  {
    Serial.print(" - UNDERFLOW");
  }
  Serial.print('\n',BYTE);
  delay(300); //pause for readability
}
