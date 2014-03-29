/*!
 * \file
 * \brief Définition de la classe LedIndicatorTest.
 */

#ifndef ROBOTTEST_LEDINDICATORTEST_HPP
#define	ROBOTTEST_LEDINDICATORTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
    /*!
     * \brief Effectue un test de clignotement des LEDs du tableau d'affichage.
     */
    class LedIndicatorTest : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref LedIndicatorTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::LedIndicatorTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        LedIndicatorTest() : pmx::ConsoleUnitTest("LedIndicatorTest : Blink LedBar and LedIndicator board")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~LedIndicatorTest()
        {
        }

        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
