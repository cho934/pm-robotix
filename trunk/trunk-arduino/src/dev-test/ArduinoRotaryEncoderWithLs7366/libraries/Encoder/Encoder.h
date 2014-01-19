/*
  Encoder.h - - Interface library for chip LS7366R that does quadrature decoding 
                of rotary encoders.  Library for Wiring/Arduino - Version 0017
  
  (0.2) Corrected CLEAR_COUNTER op-code thanks to Christophe Chaudelet
  (0.1) Original library      
  
  by Jeff Bingham.
  More information can be found here:
  http://pendulum.binghamsite.com/rotary-encoders 
*/

// ensure this library description is only included once
#ifndef Encoder_h
#define Encoder_h

// define some LS7366R Op-codes
#define CLEAR_COUNTER 32
#define CLEAR_STATUS 48
#define READ_COUNTER 96
#define READ_STATUS 112
#define WRITE_MODE0 136
#define WRITE_MODE1 144

// library interface description
class Encoder {
  public:
    // constructors:
    Encoder(int slave_select_pin);
	
	// Methods for initializing the encoder through the SPI
	void initialize(void);
	void initialize(int setup_mdr0, int setup_mdr1);
	
    // Method for getting number of counts
	unsigned long readCounter(void);
	
	// Method for determining the status of the IC
	unsigned char readStatus(void);
	
	// Method for clearing the counter
	void clearCounter(void);
	
	// Method for clearing the status register
	void clearStatus(void);

  private:
	// Method for talking to IC over SPI
    char spiTransfer(volatile char data);
    
	unsigned char counterSize; //n-byte counter
	unsigned char prevStatus; //status register from previous read
	unsigned long prevCount; //count from previous read
	long prevTime; //time stamp of previous read
	long prevDiff; //difference in coundt from previous read
	int ss_pin; //slave select pin
};

#endif

