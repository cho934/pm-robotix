/*!
 * \file
 * \brief Définition de la classe UTApfGpioOut.
 */

#ifndef TEST_APFGPIOOUT_HPP
#define TEST_APFGPIOOUT_HPP


#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

#define LED_GPIO_PORT_PATH   "/dev/gpio/port"

#define GPIORDDIRECTION	_IOR(PP_IOCTL, 0xF0, int)
#define GPIOWRDIRECTION	_IOW(PP_IOCTL, 0xF1, int)
#define GPIORDDATA	_IOR(PP_IOCTL, 0xF2, int)
#define GPIOWRDATA	_IOW(PP_IOCTL, 0xF3, int)
#define GPIORDMODE	_IOR(PP_IOCTL, 0xF4, int)
#define GPIOWRMODE	_IOW(PP_IOCTL, 0xF5, int)

namespace test
{
    /*!
     * \brief Effectue un test de clignotement de LED sur tous les pads de sorties de la carte DevLightV2.
     */
    class ApfGpioOut : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref UTApfGpioOut.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfGpioOut");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfGpioOut() : pmx::ConsoleUnitTest("ApfGpioOut : Blink GPIO out on devLightV2 (with ioctl)")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfGpioOut()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
