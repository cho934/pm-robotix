/*!
 * \file
 * \brief Définition de la classe GroveColorTest.
 */

#ifndef ROBOTTEST_GROVECOLORTEST_HPP
#define	ROBOTTEST_GROVECOLORTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
    /*!
     * \brief Effectue un test.
     */
    class GroveColorTest : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref LedIndicatorTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::GroveColorTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        GroveColorTest() : pmx::ConsoleUnitTest("GroveColorTest : get colors from Gorve sensor")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~GroveColorTest()
        {
        }

        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
