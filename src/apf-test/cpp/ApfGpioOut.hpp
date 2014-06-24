/*!
 * \file
 * \brief Définition de la classe ApfGpioOut.
 */

#ifndef TEST_APFGPIOOUT_HPP
#define TEST_APFGPIOOUT_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

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
