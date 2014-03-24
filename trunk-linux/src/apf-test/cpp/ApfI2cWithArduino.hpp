/*!
 * \file
 * \brief Définition de la classe ApfI2cWithArduino.
 * \brief basé sur http://binerry.de/post/27128825416/raspberry-pi-with-i2c-arduino-slave
 */

#ifndef TEST_APFI2CWITHARDUINO_HPP
#define TEST_APFI2CWITHARDUINO_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test pour communiquer avec une arduino par I2C.
     */
    class ApfI2cWithArduino : public pmx::ConsoleUnitTest, utils::Mutex
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfSpiWithLs7366.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfI2cWithArduino");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfI2cWithArduino() : pmx::ConsoleUnitTest("ApfI2cWithArduino : communication avec une arduino par i2c")
        {
        	i2c_bus = 0;
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfI2cWithArduino()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);


        struct as_i2c_device *i2c_bus;
        char buffer[7];

        void testCommand( const char command[3], const char identifier[5]);


		int writeI2CSize(struct as_i2c_device *aDev, const char *buf, size_t size);
		int readI2CSize(struct as_i2c_device *aDev, char *buf, size_t size);
    };
};

#endif
