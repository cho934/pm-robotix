/*!
 * \file
 * \brief Définition de la classe StateTest.
 */

#ifndef TEST_STATETEST_HPP
#define	TEST_STATETEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace test
{
    /*!
     * \brief Test pour utiliser les états.
     */
    class StateTest : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref StateTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::StateTest");
            return instance;
        }
    public:

        /*!
         * \brief Constructeur de la classe.
         */
        StateTest() : pmx::RobotTest("StateTest : Tester une IA.")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~StateTest()
        {
        }

        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif	/* TEST_STATETEST_HPP */

