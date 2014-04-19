/*!
 * \file
 * \brief Implémentation de la classe ApfI2cWithGroveColor concernant l'utilisation du détecteur Grove TSC3414.
 */


#include "ApfI2cWithGroveColor.hpp"

#include <as_devices/as_i2c.h>
#include <unistd.h>
#include <cmath>
//#include <cstdint>
#include <cstdio>
#include <iostream>




int TCS3414values[4]; // [Clear,Red,Green,Blue]
float TCS3414medium[4]; // [Clear,Red,Green,Blue]
float TCS3414mediate[4]; // [Clear,Red,Green,Blue]
float ColorTemperature = 0;

// SET the integration time here. Higher times allow for higher values with better precicion.
int integrationtime = 12; //12 == 12ms, 100 = 100ms, 400 = 400ms. Other values are note accepted
int loopdelay = integrationtime; //loop delay depends on the integration time

bool debug = false; //change to true if you want to see the various debug serial output bits
bool percentageEnabled = false; //enable/disable the percentage mode
bool compensateEnabled = false; //enable/disable color compensation of the sensor sensitivity per color

void ApfI2cWithGroveColor::run(int, char*[])
{

	std::cout
			<< "APF : Use I2C on devLightV2 (As_devices) with Grove Color Sensor"
			<< std::endl;
	int value;
	int initialized = 0;


	struct as_i2c_device *i2c_bus= 0;
	int i2c_id = 0; //Bus I2C sur la carte APF9328

	printf("Open i2c bus\n");
	i2c_bus = as_i2c_open(i2c_id);
	if (i2c_bus < 0)
	{
		printf("Error can't open i2c bus\n");
	}
	else
	{
		printf("Bus %d opened\n", i2c_id);
		initialized = 1;
	}

	value = as_i2c_set_slave_addr(i2c_bus, GROVE_COLOR_DEFAULT_ADDRESS);
	if (value < 0)
	{
		printf(" Error, can't close i2c bus num %d\n", i2c_id);
	}
	usleep(5000); //fréq i2c à 100kHz : attente de l'application complète de la trame

	CMD(0);
	TCS3414Start(i2c_bus, 10, 100);
	for (int i = 0; i < 1000; i++)
	{
		TCS3414Loop(i2c_bus);
		//usleep(500000);
	}

	printf("Close i2c bus\n");
	value = as_i2c_close(i2c_bus);
	if (value < 0)
	{
		printf(" Error, can't close i2c bus num %d\n", i2c_id);
	}
	else
	{
		initialized = 0;
	}

	std::cout << "End Of APF-TEST" << std::endl;
}

/*
 * Private Methods
 */

int ApfI2cWithGroveColor::readRegisterbyte(struct as_i2c_device *aDev,	int reg, int* data)
{
	lock();
	int ret = 0;
	//ret = as_i2c_read_reg(fd_, adr, reg, data, 1); //return 0 on success, -1 on write error (\e reg byte), -2 on read error.

	ret = as_i2c_read_reg(aDev, (uint8_t)reg, (uint8_t*)data, 1);
	if (ret < 0)
	{
		//errorCount_++;
		if (ret == -1)
			std::cout << "as_i2c_read_reg_byte: reg " << (int) reg
					<< " WRITE error!" << std::endl;
		if (ret == -2)
			std::cout << "as_i2c_read_reg_byte: reg " << (int) reg
					<< " READ error!" << std::endl;
		//exit(1);
	}
	else
	{
		//errorCount_ = 0;
	}
	unlock();
	return ret;
}

int ApfI2cWithGroveColor::writeRegisterbyte(struct as_i2c_device *aDev, uchar reg, uchar value)
{
	//logger().error() << "as_i2c_write_reg_byte: adr=" << (int) adr << utils::end;
	lock();
	int result = 0;

	//result = as_i2c_write_reg_byte(fd_, adr, reg, value);
	result = as_i2c_write_reg_byte(aDev, reg, value);

	if (result < 0)
	{
		//errorCount_++;
		std::cout << "as_i2c_write_reg_byte: reg=" << (int) reg << " val="
				<< (int) value << " !" << std::endl;
		//exit(1);
	}
	else
	{
		//errorCount_ = 0;
	}
	//usleep(1000); //fréq i2c à 100kHz : attente de l'application complète de la trame

	unlock();
	return result;
}

/*** Gets the blue sensor value and returns an unsigned int ***/
int ApfI2cWithGroveColor::TSC3414Blue(struct as_i2c_device *aDev)
{

	int blueLow = 0;
	int blueHigh = 0;
	int ret = 0;
	ret = readRegisterbyte(aDev, 0x94, &blueLow); //read Clear register
	ret = readRegisterbyte(aDev, 0x95, &blueHigh); //read Clear register

	std::cout << "blueLow: " << (int) blueLow << " \tblueHigh: "
			<< (int) blueHigh << std::endl;
	blueHigh = (blueHigh * 256) + blueLow;

	return blueHigh;
}

/*** Gets the green sensor value and returns an unsigned int ***/
int ApfI2cWithGroveColor::TSC3414Green(struct as_i2c_device *aDev)
{

	int greenLow = 0;
	int greenHigh = 0;
	int ret = 0;
	ret = readRegisterbyte(aDev, 0x90, &greenLow); //read Clear register
	ret = readRegisterbyte(aDev, 0x91, &greenHigh); //read Clear register

	std::cout << "greenLow: " << (int) greenLow << " \tgreenHigh: "
			<< (int) greenHigh << std::endl;
	greenHigh = (greenHigh * 256) + greenLow;

	return greenHigh;

}

/*** Gets the red sensor value and returns an unsigned int ***/
int ApfI2cWithGroveColor::TSC3414Red(struct as_i2c_device *aDev)
{

	int redLow = 0;
	int redHigh = 0;
	int ret = 0;
	ret = readRegisterbyte(aDev, 0x92, &redLow); //read Clear register
	ret = readRegisterbyte(aDev, 0x93, &redHigh); //read Clear register

	std::cout << "redLow: " << (int) redLow << " \tredHigh: " << (int) redHigh
			<< std::endl;
	redHigh = (redHigh * 256) + redLow;

	return redHigh;
}

/*** Gets the clear sensor value and returns an unsigned int ***/
int ApfI2cWithGroveColor::TSC3414Clear(struct as_i2c_device *aDev)
{

	int clearLow = 0;
	int clearHigh = 0;
	int ret = 0;
	ret = readRegisterbyte(aDev, 0x96, &clearLow); //read Clear register
	ret = readRegisterbyte(aDev, 0x97, &clearHigh); //read Clear register

	std::cout << "clearH: " << (int) clearLow << "  \tclearL: "
			<< (int) clearHigh << std::endl;
	clearHigh = (clearHigh * 256) + clearLow;

	return clearHigh;
}

/*
 * ======================================================
 * Sensor read functions - retrieves the RGBW raw sensor values
 * ======================================================
 */
void ApfI2cWithGroveColor::TSC3414All(struct as_i2c_device *aDev, int allcolors[])
{
	uint8_t white = TSC3414Clear(aDev);
	uint8_t green = TSC3414Green(aDev);
	uint8_t red = TSC3414Red(aDev);
	uint8_t blue = TSC3414Blue(aDev);

	allcolors[0] = white;
	allcolors[1] = red;
	allcolors[2] = green;
	allcolors[3] = blue;
	//returns all colors;
}

/*
 * ======================================================
 * TCS3414 Initialization
 * Turns on the sensor and sets integration time
 * ======================================================
 */
void ApfI2cWithGroveColor::TCS3414Start(struct as_i2c_device *aDev, int delay1, int delay2)
{

	int ret = 0;
	//slave address: 0011 1001
	//0x80 1000 0000 //write to Control register
	//0x01 0000 0001 //Turn the device on (does not enable ADC yet)
	ret = writeRegisterbyte(aDev, 0x80, 0x01);

	usleep(delay1 * 1000); //14

	// Request confirmation //0011 1001
	int receivedVal; //0001 (ADC valid) 0001 (Power on)
	ret = readRegisterbyte(aDev, 0x39, &receivedVal);

	// Request ID //0011 1001
	int ID;
	//0x84 1000 0100 //get information from ID register (04h)
	ret = readRegisterbyte(aDev, 0x84, &ID);
	//0001 0000 (first byte == 0001 (TCS: 3413,3414,3415,3416) or 0000 (TCS: 3404).

	if (ID == 1 || ID == 17)
	{ //0000 0001 || 0001 0001
		std::cout << "TCS3414 is now ON" << std::endl;
	}
	else
	{
		std::cout << "TCS3414 is now OFF" << std::endl;
	}

	//Write to Timing (integration) register
	if (integrationtime == 12)
	{
		//0000 0000 //set free running INTEG_MODE and integration time to 12ms
		ret = writeRegisterbyte(aDev, 0x81, 0x00);
	}
	else if (integrationtime == 100)
	{
		//0000 0001 //set free running INTEG_MODE and integration time to 100ms
		ret = writeRegisterbyte(aDev, 0x81, 0x01);
	}
	else if (integrationtime == 400)
	{
		//0000 0010 //set free running INTEG_MODE and integration time to 400ms
		ret = writeRegisterbyte(aDev, 0x81, 0x02);
	}
	else
	{
		std::cout << "improper integration time has been set!" << std::endl;
	}

	//0000 0011 //Enable ADC_EN (needed to allow integration every 100ms)
	ret = writeRegisterbyte(aDev, 0x80, 0x03);

	usleep(delay2 * 1000); //14 //wait for a moment to allow ADC to initialize*/

}

/*** Keeps a running average of 4 values per color. ***/
void ApfI2cWithGroveColor::calculateMedium(float med[], int value[], 	float divider)
{
	for (int i = 0; i < 4; i++)
	{
		med[i] = ((med[i] * (divider - 1.0)) + value[i]) / divider;
	}
}

/*** calculates percentages for R,G,B channels, if enabled.  ***/
void ApfI2cWithGroveColor::makePercentage(int allcolors[], 	float allmedium[])
{ //makes every color a percentage, 100% is the average of the previous 4 values before this is entered.
	for (int i = 0; i < 4; i++)
	{
		allcolors[i] = (int) (allcolors[i] / allmedium[i] * 100);
	}
}

//compensateEnabled = false; //enable/disable color compensation of the sensor sensitivity per color
void ApfI2cWithGroveColor::colorCompensator(int allcolors[])
{
	allcolors[2] = (int) (allcolors[2] * 1.3125); //green
	allcolors[3] = (int) (allcolors[2] * 1.5973); //blue
	//look at the graph in the datasheet to find the following percentages
	//blue  52%    (r/b == 1.5973)
	//green 63.28% (r/g == 1.3125)
	//red   83.06%
}

/*** takes the raw values from the sensors and converts them to
 Correlated Color Temperature.  Returns a float with CCT ***/
float ApfI2cWithGroveColor::CCTCalc(int allcolors[])
{
	float TCS3414tristimulus[3]; // [tri X, tri Y, tri Z]
	float TCS3414chromaticityCoordinates[2]; //chromaticity coordinates // [x, y]

	//calculate tristimulus values (chromaticity coordinates)
	//The tristimulus Y value represents the illuminance of our source
	TCS3414tristimulus[0] = (-0.14282 * allcolors[1]) + (1.54924 * allcolors[2])
			+ (-0.95641 * allcolors[3]); //X
	TCS3414tristimulus[1] = (-0.32466 * allcolors[1]) + (1.57837 * allcolors[2])
			+ (-0.73191 * allcolors[3]); //Y // = Illuminance
	TCS3414tristimulus[2] = (-0.68202 * allcolors[1]) + (0.77073 * allcolors[2])
			+ (0.56332 * allcolors[3]); //Z

	float XYZ = TCS3414tristimulus[0] + TCS3414tristimulus[1]
			+ TCS3414tristimulus[2];

	//calculate the chromaticiy coordinates
	TCS3414chromaticityCoordinates[0] = TCS3414tristimulus[0] / XYZ; //x
	TCS3414chromaticityCoordinates[1] = TCS3414tristimulus[1] / XYZ; //y

	float n = (TCS3414chromaticityCoordinates[0] - 0.3320)
			/ (0.1858 - TCS3414chromaticityCoordinates[1]);

	float CCT =
			((449 * pow(n, 3)) + (3525 * pow(n, 2)) + (6823.3 * n) + 5520.33);

	std::cout << "Illuminance: " << TCS3414tristimulus[1] << " \tx: "
			<< TCS3414chromaticityCoordinates[0] << " \ty: "
			<< TCS3414chromaticityCoordinates[1] << " \tCCT:  " << CCT << " K"
			<< std::endl;

	return CCT;
}

void ApfI2cWithGroveColor::TCS3414Loop(struct as_i2c_device *aDev)
{
	//getSerialCommands(); //to be able to receive commands

	//gets the raw values from the sensors and writes it to TCS3414values[]
	TSC3414All(aDev, TCS3414values);

	//compensate based on the filter characteristics of the TCS3414
	if (compensateEnabled)
		colorCompensator(TCS3414values);

	//keeps a running average from the last 4 values per color.
	calculateMedium(TCS3414mediate, TCS3414values, 4.0);

	//calculates the color temperature, using the algorithm in the TCS3414 datasheet
	ColorTemperature = CCTCalc(TCS3414values);

	//displays percentage values, if enabled.
	if (percentageEnabled)
	{
		makePercentage(TCS3414values, TCS3414medium);
	}

	std::cout << "Clear: " << (int) TCS3414values[0] << " \tRed: "
			<< (int) TCS3414values[1] << " \tGreen: " << (int) TCS3414values[2]
			<< " \tBlue:  " << (int) TCS3414values[3] << std::endl;
	std::cout << std::endl;

	//pause
	usleep(loopdelay * 1000); //delays by the integration time between measurements

}

void ApfI2cWithGroveColor::CMD(int delayTime)
{

	if (percentageEnabled)
	{
		std::cout << "TSC3414 Percentage mode ON" << std::endl;
	}
	else
	{
		std::cout << "TSC3414 Percentage mode OFF" << std::endl;
	}

	if (compensateEnabled)
	{
		std::cout << "TSC3414 Color compensation mode ON" << std::endl;
	}
	else
	{
		std::cout << "TSC3414 Color compensation mode OFF" << std::endl;
	}

	usleep(delayTime * 1000);

	/*Serial.println("=========== Command list ===========");
	 Serial.println("\'                                  \'");
	 Serial.println("  ? == Show this command list");
	 Serial.println("");
	 Serial.println("  p == pause for 5 seconds (stackable)");
	 Serial.println("");
	 Serial.println("  1 == Enable Percentage mode");
	 Serial.println("  0 == Disable Percentage mode");
	 Serial.print("  Percentage mode is currently: ");
	 if(percentageEnabled){
	 Serial.println("ON");
	 }else{
	 Serial.println("OFF");
	 }
	 Serial.println("");
	 Serial.println("  c == Enable Color compensation mode");
	 Serial.println("  n == Disable Color compensation mode");
	 Serial.print("  Color compensation mode is currently: ");
	 if(compensateEnabled){
	 Serial.println("ON");
	 }else{
	 Serial.println("OFF");
	 }
	 Serial.println("\'                                  \'");
	 Serial.println("====================================");
	 delay(delayTime);*/
}

