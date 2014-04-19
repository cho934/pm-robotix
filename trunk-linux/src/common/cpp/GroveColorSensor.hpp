/*!
 * \file
 * \brief Définition de la classe GroveColorSensor.
 */

#ifndef PMX_GROVECOLORSENSOR_HPP
#define PMX_GROVECOLORSENSOR_HPP

#include <stdint.h>

#include "ARobotElement.hpp"
#include "LoggerFactory.hpp"
#include "Macro.hpp"

#define     GROVE_COLOR_DEFAULT_ADDRESS    0x39 // Address of the grove Color Sensor 0x39

namespace pmx
{
/*!
 * \brief Implémentation du détecteur de couleur Grove associée au robot.
 */
class GroveColorSensor: public ARobotElement
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref GroveColorSensor.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::GroveColorSensor");
		return instance;
	}

	bool connected_;

	// SET the integration time here. Higher times allow for higher values with better precicion.
	int integrationtime_; //12 == 12ms, 100 = 100ms, 400 = 400ms. Other values are note accepted
	int loopdelay_; //loop delay depends on the integration time

	bool percentageEnabled_; //enable/disable the percentage mode
	bool compensateEnabled_; //enable/disable color compensation of the sensor sensitivity per color

	uchar TCS3414values_[4]; // [Clear,Red,Green,Blue]
	float TCS3414medium_[4]; // [Clear,Red,Green,Blue]
	float TCS3414mediate_[4]; // [Clear,Red,Green,Blue]

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	GroveColorSensor(pmx::Robot & robot);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~GroveColorSensor()
	{
	}

	bool isConnected()
	{
		return connected_;
	}

	/*!
	 * \brief TCS3414 Initialization
	 * Turns on the sensor and sets integration time.
	 */
	void TCS3414Initialize(int delay1, int delay2);

	/*!
	 * \brief Get the color values [Clear,Red,Green,Blue]
	 */
	uint8_t* TCS3414GetValues();

private:
	/*!
	 * \brief Log the parameters.
	 */
	void CMD(int delayTime);

	/*!
	 * \brief retrieve all colors.
	 */
	void TSC3414All(uchar allcolors[]);
	uchar TSC3414Red();
	uchar TSC3414Green();
	uchar TSC3414Blue();
	uchar TSC3414Clear();

	/*!
	 * \brief Keeps a running average of 4 values per color.
	 */
	void calculateMedium(float med[], uchar value[], float divider);

	/*!
	 * \brief calculates percentages for R,G,B channels, if enabled.
	 */
	void makePercentage(uchar allcolors[], float allmedium[]);

	/*!
	 * \brief enable/disable color compensation of the sensor sensitivity per color.
	 */
	void colorCompensator(uchar allcolors[]);

	/*!
	 * \brief takes the raw values from the sensors and converts them to
	 Correlated Color Temperature.  Returns a float with CCT.
	 */
	float CCTCalc(uchar allcolors[]);

	void write_i2c(uchar command, uchar value);

	uchar read_i2c(uchar command);

};
}

#endif
