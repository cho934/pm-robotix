/*!
 * \file
 * \brief Définition de la classe ApfOutTest.
 */

#ifndef TEST_APFOUTTEST_HPP
#define TEST_APFOUTTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

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
    class ApfOutTest : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfOutTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfOutTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfOutTest() : pmx::RobotTest("APFOUT : ApfOutTest : Blink GPIO out on devLightV2 (with ioctl)")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfOutTest()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
