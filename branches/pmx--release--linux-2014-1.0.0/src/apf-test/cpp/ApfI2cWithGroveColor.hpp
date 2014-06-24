/*!
 * \file
 * \brief Définition de la classe ApfI2cWithGroveColor.
 */

#ifndef TEST_APFI2CWITHGROVECOLORSENSOR_HPP
#define TEST_APFI2CWITHGROVECOLORSENSOR_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/Macro.hpp"
#include "../../common/cpp/Mutex.hpp"

#define     GROVE_COLOR_DEFAULT_ADDRESS    0x39 // Address of the grove Color Sensor 0x39

//namespace test
//{
/*!
 * \brief Effectue un test pour contrôler le détecteur de couleur Grove TSC3414.
 */
class ApfI2cWithGroveColor: public pmx::ConsoleUnitTest, utils::Mutex
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ApfI2cWithGroveColor.
	 */
	/*static inline const utils::Logger & logger()
	 {
	 static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfI2cWithGroveColor");
	 return instance;
	 }*/

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ApfI2cWithGroveColor()
			: pmx::ConsoleUnitTest("ApfI2cWithGroveColor : test GroveColorSensor TSC3414")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~ApfI2cWithGroveColor()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);

	/*!
	 * \brief Grove Color Sensor Methods.
	 */

private:
	void CMD(int delayTime);
	//void getSerialCommands();
	void TSC3414All(struct as_i2c_device *aDev, int allcolors[]);
	int TSC3414Red(struct as_i2c_device *aDev);
	int TSC3414Green(struct as_i2c_device *aDev);
	int TSC3414Blue(struct as_i2c_device *aDev);
	int TSC3414Clear(struct as_i2c_device *aDev);

	void TCS3414Start(struct as_i2c_device *aDev, int delay1, int delay2);
	void calculateMedium(float med[], int value[], float divider);
	void makePercentage(int allcolors[], float allmedium[]);
	void colorCompensator(int allcolors[]);
	float CCTCalc(int allcolors[]);
	void TCS3414Loop(struct as_i2c_device *aDe);

	/*!
	 * \brief Read a byte from the given register. Private Methods.
	 *
	 * \param   struct as_i2c_device *aDev contenant l'adress I2C
	 * \param   reg   the given register.
	 * \param   data   the read value.
	 *
	 * \return return 0 on success, -1 on write error (\e reg byte), -2 on read error.
	 */
	int readRegisterbyte(struct as_i2c_device *aDev, int reg, int* data);

	/*!
	 * \brief Write a byte to the I2C given register. Private Methods.
	 *
	 * \param   struct as_i2c_device *aDev contenant l'adress I2C
	 * \param   reg   register to write.
	 * \param   value   value to apply.
	 *
	 * \return 0 on success, -1 on error.
	 */
	int writeRegisterbyte(struct as_i2c_device *aDev, uchar reg, uchar value);

};
//}


#endif
