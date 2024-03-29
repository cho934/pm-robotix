/*!
 * \file
 * \brief Implémentation de la classe GroveColorSensor concernant l'utilisation du détecteur Grove TSC3414.
 */

#include "GroveColorSensor.hpp"

#include <unistd.h>
#include <cmath>

#include "HostI2cBus.hpp"

pmx::GroveColorSensor::GroveColorSensor(pmx::Robot & robot)
		: ARobotElement(robot), connected_(false), integrationtime_(12), loopdelay_(12), percentageEnabled_(false), compensateEnabled_(
				false), colorTemperature_(false)
{
}

void pmx::GroveColorSensor::begin()
{
	try
	{
		//open i2c and setslave
		grovei2c_.open(GROVE_COLOR_DEFAULT_ADDRESS);

		//0x80 1000 0000 //write to Control register
		//0x01 0000 0001 //Turn the device on (does not enable ADC yet)
		write_i2c(0x80, 0x01);

		// Request ID to test if TCS3414 is connected
		uchar ID = 0;
		//0x84 1000 0100 //get information from ID register (04h)
		ID = read_i2c(0x84); //ID 0001 0000 (first byte == 0001 (TCS: 3413,3414,3415,3416) or 0000 (TCS: 3404).
		if (ID == 17) //0000 0001 || 0001 0001
		{
			logger().debug() << "TCS3414 is now ON : id=" << (int) ID << utils::end;
			connected_ = true;
			TCS3414Setup(10, 100); 	//setup and enable the grove sensor
		}
		else
		{
			logger().error() << "init() : TCS3414 is now OFF, ID=" << (int) ID << " not eq 17 !" << utils::end;
		}
	} catch (utils::Exception * e)
	{
		logger().error() << "init()::Exception - GroveColorSensor NOT CONNECTED !!! (ID test) " //<< e->what()
				<< utils::end;
	}
}

/*** Gets the blue sensor value and returns an unsigned int ***/
uchar pmx::GroveColorSensor::TSC3414Blue()
{
	logger().debug() << "conected=" << connected_ << utils::end;
	uchar blueLow = 0;
	uchar blueHigh = 0;
	if (connected_)
	{
		try
		{
			blueLow = read_i2c(0x94);
			blueHigh = read_i2c(0x95);

			logger().debug() << "blueLow: " << (int) blueLow << " \tblueHigh: " << (int) blueHigh << utils::end;
			blueHigh = (blueHigh * 256) + blueLow;
		} catch (utils::Exception * e)
		{
			logger().error() << "Exception TSC3414Blue: " << e->what() << utils::end;
		}
	}
	return blueHigh;
}

/*** Gets the green sensor value and returns an unsigned int ***/
uchar pmx::GroveColorSensor::TSC3414Green()
{
	uchar greenLow = 0;
	uchar greenHigh = 0;
	if (connected_)
	{
		try
		{
			greenLow = read_i2c(0x90);
			greenHigh = read_i2c(0x91);

			logger().debug() << "greenLow: " << (int) greenLow << " \tgreenHigh: " << (int) greenHigh << utils::end;
			greenHigh = (greenHigh * 256) + greenLow;
		} catch (utils::Exception * e)
		{
			logger().error() << "Exception TSC3414Green: " << e->what() << utils::end;
		}
	}
	return greenHigh;
}

/*** Gets the red sensor value and returns an unsigned int ***/
uchar pmx::GroveColorSensor::TSC3414Red()
{
	uchar redLow = 0;
	uchar redHigh = 0;
	if (connected_)
	{
		try
		{
			redLow = read_i2c(0x92);
			redHigh = read_i2c(0x93);
			logger().debug() << "redLow: " << (int) redLow << " \tredHigh: " << (int) redHigh << utils::end;
			redHigh = (redHigh * 256) + redLow;
		} catch (utils::Exception * e)
		{
			logger().error() << "Exception TSC3414Red: " << e->what() << utils::end;
		}
	}
	return redHigh;
}

/*** Gets the clear sensor value and returns an unsigned int ***/
uchar pmx::GroveColorSensor::TSC3414Clear()
{
	uchar clearLow = 0;
	uchar clearHigh = 0;
	if (connected_)
	{
		try
		{
			clearLow = read_i2c(0x96);
			clearHigh = read_i2c(0x97);

			logger().debug() << "clearH: " << (int) clearLow << "  \tclearL: " << (int) clearHigh << utils::end;
			clearHigh = (clearHigh * 256) + clearLow;
		} catch (utils::Exception * e)
		{
			logger().error() << "Exception TSC3414Clear : " << e->what() << utils::end;
		}
	}
	return clearHigh;
}

/*
 * ======================================================
 * Sensor read functions - retrieves the RGBW raw sensor values
 * ======================================================
 */
void pmx::GroveColorSensor::TSC3414All(uchar allcolors[])
{
	uchar white = TSC3414Clear();
	uchar green = TSC3414Green();
	uchar red = TSC3414Red();
	uchar blue = TSC3414Blue();

	allcolors[0] = white;
	allcolors[1] = red;
	allcolors[2] = green;
	allcolors[3] = blue;
}

/*
 * ======================================================
 * TCS3414 Initialization
 * Turns on the sensor and sets integration time
 * ======================================================
 */
void pmx::GroveColorSensor::TCS3414Setup(int delay1, int delay2)
{
	CMD(0); //log
	if (connected_)
	{
		try
		{
			//slave address: 0011 1001
			//0x80 1000 0000 //write to Control register
			//0x01 0000 0001 //Turn the device on (does not enable ADC yet)
			write_i2c(0x80, 0x01);

			usleep(delay1 * 1000);				//14

			// Request confirmation //0011 1001
			uchar receivedVal;				//0001 (ADC valid) 0001 (Power on)
			receivedVal = read_i2c(0x39);
			/*
			 // Request ID //0011 1001
			 uchar ID;
			 //0x84 1000 0100 //get information from ID register (04h)
			 ID = read_i2c(0x84);
			 //0001 0000 (first byte == 0001 (TCS: 3413,3414,3415,3416) or 0000 (TCS: 3404).

			 if (ID == 1 || ID == 17)
			 { //0000 0001 || 0001 0001
			 logger().debug() << "TCS3414 is now ON" << utils::end;
			 }
			 else
			 {
			 logger().debug() << "TCS3414 is now OFF" << utils::end;
			 }*/

			//Write to Timing (integration) register
			if (integrationtime_ == 12)
			{
				//0000 0000 //set free running INTEG_MODE and integration time to 12ms
				write_i2c(0x81, 0x00);
			}
			else if (integrationtime_ == 100)
			{
				//0000 0001 //set free running INTEG_MODE and integration time to 100ms
				write_i2c(0x81, 0x01);
			}
			else if (integrationtime_ == 400)
			{
				//0000 0010 //set free running INTEG_MODE and integration time to 400ms
				write_i2c(0x81, 0x02);
			}
			else
			{
				logger().debug() << "improper integration time has been set!" << utils::end;
			}

			//0000 0011 //Enable ADC_EN (needed to allow integration every 100ms)
			write_i2c(0x80, 0x03);
		} catch (utils::Exception * e)
		{
			logger().error() << "Exception GroveColorSensor::TCS3414Initialize : " << e->what() << utils::end;
		}
		usleep(delay2 * 1000); //14 //wait for a moment to allow ADC to initialize*/
	}
}

/*** Keeps a running average of 4 values per color. ***/
void pmx::GroveColorSensor::calculateMedium(float med[], uchar value[], float divider)
{
	for (int i = 0; i < 4; i++)
	{
		med[i] = ((med[i] * (divider - 1.0)) + value[i]) / divider;
	}
}

/*** calculates percentages for R,G,B channels, if enabled.  ***/
void pmx::GroveColorSensor::makePercentage(uchar allcolors[], float allmedium[])
{ //makes every color a percentage, 100% is the average of the previous 4 values before this is entered.
	for (int i = 0; i < 4; i++)
	{
		allcolors[i] = (int) (allcolors[i] / allmedium[i] * 100);
	}
}

//compensateEnabled = false; //enable/disable color compensation of the sensor sensitivity per color
void pmx::GroveColorSensor::colorCompensator(uchar allcolors[])
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
float pmx::GroveColorSensor::CCTCalc(uchar allcolors[])
{
	//calculate tristimulus values (chromaticity coordinates)
	//The tristimulus Y value represents the illuminance of our source
	TCS3414tristimulus_[0] = (-0.14282 * allcolors[1]) + (1.54924 * allcolors[2]) + (-0.95641 * allcolors[3]);		//X
	TCS3414tristimulus_[1] = (-0.32466 * allcolors[1]) + (1.57837 * allcolors[2]) + (-0.73191 * allcolors[3]);//Y // = Illuminance
	TCS3414tristimulus_[2] = (-0.68202 * allcolors[1]) + (0.77073 * allcolors[2]) + (0.56332 * allcolors[3]);		//Z

	float XYZ = TCS3414tristimulus_[0] + TCS3414tristimulus_[1] + TCS3414tristimulus_[2];

	//calculate the chromaticiy coordinates
	TCS3414chromaticityCoordinates_[0] = TCS3414tristimulus_[0] / XYZ;		//x
	TCS3414chromaticityCoordinates_[1] = TCS3414tristimulus_[1] / XYZ;		//y

	float n = (TCS3414chromaticityCoordinates_[0] - 0.3320) / (0.1858 - TCS3414chromaticityCoordinates_[1]);

	float CCT = ((449 * pow(n, 3)) + (3525 * pow(n, 2)) + (6823.3 * n) + 5520.33);

	logger().debug() << "Illuminance: " << TCS3414tristimulus_[1] << " \tx: " << TCS3414chromaticityCoordinates_[0]
			<< " \ty: " << TCS3414chromaticityCoordinates_[1] << " \tCCT:  " << CCT << " K" << utils::end;

	return CCT;
}

// [Clear,Red,Green,Blue]
uchar* pmx::GroveColorSensor::TCS3414GetColor()
{
	//gets the raw values from the sensors and writes it to TCS3414values[]
	TSC3414All(TCS3414values_);

	//compensate based on the filter characteristics of the TCS3414
	if (compensateEnabled_)
		colorCompensator(TCS3414values_);

	//TODO keeps a running average from the last 4 values per color.
	calculateMedium(TCS3414mediate_, TCS3414values_, 4.0);

	//calculates the color temperature, using the algorithm in the TCS3414 datasheet
	colorTemperature_ = CCTCalc(TCS3414values_);

	//displays percentage values, if enabled.
	if (percentageEnabled_)
	{
		makePercentage(TCS3414values_, TCS3414medium_);
	}

	logger().info() << "Clear: " << (int) TCS3414values_[0] << " \tRed: " << (int) TCS3414values_[1] << " \tGreen: "
			<< (int) TCS3414values_[2] << " \tBlue:  " << (int) TCS3414values_[3] << utils::end;

	//pause
	usleep(loopdelay_ * 1000); //delays by the integration time between measurements

	return TCS3414values_;
}

void pmx::GroveColorSensor::CMD(int delayTime)
{

	if (percentageEnabled_)
	{
		logger().debug() << "TSC3414 Percentage mode ON" << utils::end;
	}
	else
	{
		logger().debug() << "TSC3414 Percentage mode OFF" << utils::end;
	}

	if (compensateEnabled_)
	{
		logger().debug() << "TSC3414 Color compensation mode ON" << utils::end;
	}
	else
	{
		logger().debug() << "TSC3414 Color compensation mode OFF" << utils::end;
	}

	usleep(delayTime * 1000);
}

void pmx::GroveColorSensor::write_i2c(uchar command, uchar value)
{
	grovei2c_.writeRegValue(GROVE_COLOR_DEFAULT_ADDRESS, command, value);
}

uchar pmx::GroveColorSensor::read_i2c(uchar command)
{
	uchar receivedVal = 0;
	grovei2c_.readRegValue(GROVE_COLOR_DEFAULT_ADDRESS, command, &receivedVal);
	return receivedVal;
}
