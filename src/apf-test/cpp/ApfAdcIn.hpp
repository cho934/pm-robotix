/*!
 * \file
 * \brief Définition de la classe ApfAdcIn.
 */

#ifndef TEST_APFADCINTEST_HPP
#define TEST_APFADCINTEST_HPP

//MAX1027_SPI_NUM on APF9328
#define MAX1027_SPI_NUM (1)

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test des ADC MAX1027 via le module as_devices de la carte DevLightV2.
     */
    class ApfAdcIn : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfInAdcTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfAdcIn");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfAdcIn() : pmx::ConsoleUnitTest("ApfAdcIn : Use AdC Input on devLightV2 (as_devices)")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfAdcIn()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);

       // int32_t my_as_adc_close(struct as_adc_device *aDev);

        int iRConvert2cm (int value, int model);


    };
};

#endif
