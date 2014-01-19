/*!
 * \file
 * \brief Définition de la classe LedIndicatorTest.
 */

#ifndef TEST_LEDINDICATORTEST_HPP
#define	TEST_LEDINDICATORTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test de clignotement des LEDs du tableau d'affichage.
     */
    class LedIndicatorTest : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref LedIndicatorTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::LedIndicatorTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        LedIndicatorTest() : pmx::RobotTest("APFOUT : LedIndicatorTest : Blink LedIndicator board")
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
