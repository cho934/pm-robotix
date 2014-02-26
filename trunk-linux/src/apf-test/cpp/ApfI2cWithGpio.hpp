/*!
 * \file
 * \brief Définition de la classe ApfI2cWithGpio.
 */

#ifndef TEST_APFI2CWITHGPIO_HPP
#define TEST_APFI2CWITHGPIO_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test pour contrôler les GPIO par I2C.
     */
    class ApfI2cWithGpio : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfSpiWithLs7366.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfI2cWithGpio");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfI2cWithGpio() : pmx::ConsoleUnitTest("ApfI2cWithGpio : test GPIO par i2c")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfI2cWithGpio()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
