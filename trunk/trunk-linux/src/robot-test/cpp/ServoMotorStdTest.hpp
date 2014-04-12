/*!
 * \file
 * \brief Définition de la classe ServoMotorStdTest.
 */

#ifndef ROBOTTEST_SERVOMOTORSTDTEST_HPP
#define	ROBOTTEST_SERVOMOTORSTDTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
    /*!
     * \brief Effectue un test sur un servomotor standard.
     */
    class ServoMotorStdTest : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref LedIndicatorTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::ServoMotorStdTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ServoMotorStdTest() : pmx::ConsoleUnitTest("ServoMotorStdTest : test servomotor std par fpga")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ServoMotorStdTest()
        {
        }

        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
