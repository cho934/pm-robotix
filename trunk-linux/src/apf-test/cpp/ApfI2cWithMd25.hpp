/*!
 * \file
 * \brief Définition de la classe ApfI2cWithMd25.
 */

#ifndef TEST_APFI2CWITHMD25_HPP
#define TEST_APFI2CWITHMD25_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/Mutex.hpp"



#define     MD25_I2C_BUS  0 //Bus I2C sur la carte APF9328
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

/*
//
// Grove Color Sensor
//
#define REG_CTL 0x80
#define REG_TIMING 0x81
#define REG_INT 0x82
#define REG_INT_SOURCE 0x83
#define REG_ID 0x84
#define REG_GAIN 0x87
#define REG_LOW_THRESH_LOW_BYTE 0x88
#define REG_LOW_THRESH_HIGH_BYTE 0x89
#define REG_HIGH_THRESH_LOW_BYTE 0x8A
#define REG_HIGH_THRESH_HIGH_BYTE 0x8B
#define REG_BLOCK_READ 0xCF
#define REG_GREEN_LOW 0xD0
#define REG_GREEN_HIGH 0xD1
#define REG_RED_LOW 0xD2
#define REG_RED_HIGH 0xD3
#define REG_BLUE_LOW 0xD4
#define REG_BLUE_HIGH 0xD5
#define REG_CLEAR_LOW 0xD6
#define REG_CLEAR_HIGH 0xD7
#define CTL_DAT_INIITIATE 0x03
#define CLR_INT 0xE0

//Timing Register
#define SYNC_EDGE 0x40
#define INTEG_MODE_FREE 0x00
#define INTEG_MODE_MANUAL 0x10
#define INTEG_MODE_SYN_SINGLE 0x20
#define INTEG_MODE_SYN_MULTI 0x30

//Interrupt Souce Register
#define INT_SOURCE_GREEN 0x00
#define INT_SOURCE_RED 0x01
#define INT_SOURCE_BLUE 0x10
#define INT_SOURCE_CLEAR 0x03

//Interrupt Control Register
#define INTR_STOP 40
#define INTR_DISABLE 0x00
#define INTR_LEVEL 0x10
#define INTR_PERSIST_EVERY 0x00
#define INTR_PERSIST_SINGLE 0x01

//Gain Register
#define GAIN_1 0x00
#define GAIN_4 0x10
#define GAIN_16 0x20
#define GANI_64 0x30
#define PRESCALER_1 0x00
#define PRESCALER_2 0x01
#define PRESCALER_4 0x02
#define PRESCALER_8 0x03
#define PRESCALER_16 0x04
#define PRESCALER_32 0x05
#define PRESCALER_64 0x06
*/



//namespace test
//{
    /*!
     * \brief Effectue un test pour contrôler la carte de motorisation MD25..
     */
    class ApfI2cWithMd25 : public pmx::ConsoleUnitTest, utils::Mutex
    {
    private:



    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfI2cWithMd25() : pmx::ConsoleUnitTest("ApfI2cWithMd25 : test MD25")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfI2cWithMd25()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);


        /*!
		 * \brief Read current software version.
		 *
		 * \return   version number
		 */
		int getSoftwareVersion(struct as_i2c_device *aDev);

		/*!
		 * \brief Read battery voltage.
		 *
		 * \return   voltage value in float format
		 */
		float getBatteryVolts(struct as_i2c_device *aDev);


        /*!
		 * \brief Read a byte from the given register. Private Methods.
		 *
		 * \param   struct as_i2c_device *aDev contenant l'adress I2C
		 * \param   reg   the given register.
		 * \param   data   the read value.
		 *
		 * \return return 0 on success, -1 on write error (\e reg byte), -2 on read error.
		 */
		int readRegisterbyte(struct as_i2c_device *aDev, unsigned char reg, unsigned char *data);

		/*!
		 * \brief Write a byte to the I2C given register. Private Methods.
		 *
		 * \param   struct as_i2c_device *aDev contenant l'adress I2C
		 * \param   reg   register to write.
		 * \param   value   value to apply.
		 *
		 * \return 0 on success, -1 on error.
		 */
		int writeRegisterbyte(struct as_i2c_device *aDev, unsigned char reg, unsigned char value);

    };
//}

#endif
