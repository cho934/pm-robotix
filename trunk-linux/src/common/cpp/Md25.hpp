/*!
 * \file
 * \brief Définition de la classe MD25.
 *
 * Définition de l'utilisation I2C de la carte de motorisation MD25.
 * http://www.robot-electronics.co.uk/htm/md25tech.htm
 * Spécifications :
 *  Alimentation: 12 Vcc
 *  Consommation: 530 mA (150 mA à vide)
 *  Courant de blocage: 2,5 A
 *  Vitesse de rotation: 170 t/min (216 t/min à vide)
 *  Couple: 1,5 kg.cm
 *  Encodeur: 360 impulsions/tour
 *  Dimensions: Ø28,5 x 86,6 mm (axe de 10 mm inclus)
 */

#ifndef 	PMX_MD25_HPP
#define	PMX_MD25_HPP

#include "ARobotElement.hpp"
#include "LoggerFactory.hpp"
//#include <cmath>

#define     MD25_DEFAULT_ADDRESS    0x58 // Address of the MD25 (= 0xB0 >> 1) i.e. 0x58 as a 7 bit address for the wire lib

// modes
//
//  Mode        Description
//   0    Skid-steer with unsigned speed values (STOP = 128)
//   1    Skid-steer with signed speed values  (STOP = 0)
//   2    Forward/turn steer with unsigned values (speed1 to control both motors, speed2 for turn)
//   3    Forward/turn steer with signed values (speed1 to control both motors, speed2 for turn)
//
#define     MD25_MODE_0       0
#define     MD25_MODE_1       1
#define     MD25_MODE_2       2
#define     MD25_MODE_3       3

//
// register definitions
//
#define     MD25_SPEED1_REG         0
#define     MD25_SPEED2_REG         1
#define     MD25_ENCODER1_REG       2
#define     MD25_ENCODER2_REG       6
#define     MD25_VOLTAGE_REG        10
#define     MD25_CURRENT1_REG       11
#define     MD25_CURRENT2_REG       12
#define     MD25_SOFTWAREVER_REG    13
#define     MD25_ACCELRATE_REG      14
#define     MD25_MODE_REG           15
#define     MD25_CMD_REG            16        // command register
//
// Command register command set
//
#define     MD25_RESET_ENCODERS             0x20
#define     MD25_DISABLE_SPEED_REGULATION    0x30
#define     MD25_ENABLE_SPEED_REGULATION    0x31
#define     MD25_DISABLE_TIMEOUT            0x32
#define     MD25_ENABLE_TIMEOUT             0x33

namespace pmx
{
/*!
 * \brief Cette classe permet d'interagir avec la carte de motorisation MD25.
 *
 */
class Md25: public ARobotElement
{
private:
	bool connected_;

	/*!
	 * \brief Mode courant utilisé par la carte MD25 (MODE1).
	 */
	int current_mode_;

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref Md25.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Md25");
		return instance;
	}

public:

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~Md25()
	{
	}

	/*!
	 * \brief Constructeur par défaut.
	 *
	 * Le constructeur est privé pour éviter que la classe soit instanciée.
	 * \seealso Md25::instance()
	 */
	Md25(pmx::Robot & robot);


	bool isConnected()
	{
		return connected_;
	}

	/*!
	 * \brief Read encoder for channel 1 or 2.
	 *
	 * \return              O on success, sum of -1 on write error and  -2 on read error.
	 * \param value         32-bit signed long value of current encoder value for channel 1 or 2.
	 * \param MD25Register  Choose MD25_ENCODER1_REG ou MD25_ENCODER2_REG.
	 */
	int getEncoder(long* value, int MD25Register);

	/*!
	 * \brief Read encoder for channel 1 or 2.
	 *
	 * \return              Last value if error otherwise the new value of the encoder.
	 * \param last          Last value of current encoder.
	 * \param MD25Register  Choose MD25_ENCODER1_REG ou MD25_ENCODER2_REG.
	 */
	long ensureGetEncoder(long last, int MD25Register);

	/*!
	 * \brief Read current software version.
	 *
	 * \return   version number
	 */
	int getSoftwareVersion(void);

	/*!
	 * \brief Read battery voltage.
	 *
	 * \return   voltage value in float format
	 */
	float getBatteryVolts(void);

	/*!
	 * \brief read acceleration rate.
	 *
	 * \return   acceleration rate
	 */
	int getAccelerationRate(void);

	/*!
	 * \brief read current from motor channel 1.
	 *
	 * \return   current value
	 */
	int getMotor1Current(void);

	/*!
	 * \brief read current from motor channel 2.
	 *
	 * \return   current value in apprx. units of 0.1amp
	 */
	int getMotor2Current(void);

	/*!
	 * \brief read current speed register for motor channel 1.
	 *
	 * \return   speed value (0->255); meaning dependent on mode
	 */
	int getMotor1Speed(void);

	/*!
	 * \brief read current speed register for motor channel 2.
	 *
	 * \return   speed value (0->255); meaning dependent on mode
	 */
	int getMotor2Speed(void);

	/*!
	 * \brief read current mode.
	 *
	 * \return   mode value (0, 1, 2, or 3); default is mode 0
	 */
	int getMode(void);

	/*!
	 * \brief get the errors.
	 *
	 * \return   return the count of errors.
	 */
	int getNbErrors(void);

	/*!
	 * \brief set system mode.
	 *
	 * \param   mode     value (0, 1, 2, or 3)
	 */
	void setMode(int mode);

	/*!
	 * \brief set acceleration rate.
	 *
	 * \param   rate   acceleration rate
	 */
	void setAccelerationRate(int rate);

	/*!
	 * \brief send command to command register.
	 *
	 * \param   command   command code.
	 *
	 * MD25_RESET_ENCODERS             0x20
	 * MD25_DIABLE SPEED_REGULATION    0x30
	 * MD25_ENABLE_SPEED_REGULATION    0x31
	 * MD25_DISABLE_TIMEOUT            0x32
	 * MD25_ENABLE_TIMEOUT             0x33
	 */
	void setCommand(int command);

	/*!
	 * \brief set speed registers for both channels.
	 *
	 * Effect of value is dependent on system mode.
	 *
	 * \param   speed_1   speed register for channel 1  (-128->127)
	 * \param   speed_2   speed register for channel 2  (-128->127)
	 */
	void setSpeedRegisters(int speed_1, int speed_2);

	/*!
	 * \brief ensure (2 times) to set speed register for channel 1 or 2.
	 * \param speed >0 (MD25 mode0) => 0-128-255
	 *
	 */
	void ensureSetSpeed(int speed, int reg);

	/*!
	 * \brief set speed register for channel 1 or 2.
	 *
	 * Effect of value is dependent on system mode.
	 *
	 * \return 0 on success, the read value on error.
	 * \param   speed   speed register for channel  (-128->127)
	 * \param   MD25_SPEED1_REG or MD25_SPEED2_REG
	 */
	int setSpeedReg(int speed, int reg);

	/*!
	 * \brief switch motor (1 or 2) off.
	 *
	 * \param   MD25_SPEED1_REG or MD25_SPEED2_REG
	 */
	int stopMotor(int reg);

	/*!
	 * \brief switch both motors off.
	 */
	int stopMotors(void);

private:

	void write_i2c(int command, int value);

	int read_i2c(int command);

};
}

#endif
