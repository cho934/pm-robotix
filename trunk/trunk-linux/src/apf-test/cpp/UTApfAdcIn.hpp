/*!
 * \file
 * \brief Définition de la classe UTApfAdcIn.
 */

#ifndef TEST_APFINADCTEST_HPP
#define TEST_APFINADCTEST_HPP

//MAX1027_SPI_NUM on APF9328
//#define MAX1027_SPI_NUM (1)

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test des ADC MAX1027 via le module as_devices de la carte DevLightV2.
     */
    class UTApfAdcIn : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfInAdcTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::UTApfAdcIn");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        UTApfAdcIn() : pmx::ConsoleUnitTest("UTApfAdcIn : Use AdC Input on devLightV2 (as_devices)")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~UTApfAdcIn()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
