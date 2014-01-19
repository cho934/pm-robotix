/*!
 * \file
 * \brief Définition de la classe GroveColorTest.
 */

#ifndef TEST_GROVECOLORTEST_HPP
#define	TEST_GROVECOLORTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"
#include "Md25.hpp"

namespace test
{
    /*!
     * \brief Effectue un test du composant GroveColorTest par I2C.
     */
    class GroveColorTest : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfInAdcTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::GroveColorTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        GroveColorTest() : pmx::RobotTest("I2C : GroveColorTest : Use I2C to control GroveColorSensor")
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

