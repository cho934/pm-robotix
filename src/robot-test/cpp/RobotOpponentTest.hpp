/*!
 * \file
 * \brief Définition de la classe RobotOpponentTest.
 */

#ifndef TEST_ROBOTOPPONENTTEST_HPP
#define	TEST_ROBOTOPPONENTTEST_HPP


#include "RobotTest.hpp"
#include "IMotorListener.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace test
{
    /*!
     * \brief Test pour detecter l'adversaire.
     */
    class RobotOpponentTest : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref RobotOpponentTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::RobotOpponentTest");
            return instance;
        }
    public:

        /*!
         * \brief Constructeur de la classe.
         */
        RobotOpponentTest() : pmx::RobotTest("RobotOpponentTest : Détecte l'adversaire.")
        {}

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ RobotOpponentTest()
        {}

        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif	/* _ROBOTOPPONENTTEST_HPP */

