/*!
 * \file
 * \brief Définition de la classe RobotMoveToPawnTest.
 */

#ifndef TEST_ROBOTMOVETOPAWN_HPP
#define	TEST_ROBOTMOVETOPAWN_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace test
{
    /*!
     * \brief Test pour faire avancer le robot et prendre un pion.
     */
    class RobotMoveToPawnTest : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref RobotMoveTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::RobotMoveToPawnTest");
            return instance;
        }
    public:

        /*!
         * \brief Constructeur de la classe.
         */
        RobotMoveToPawnTest() : pmx::RobotTest("RobotMoveToPawnTest : Fait avancer le robot et prend le pion détecté.")
        {}

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ RobotMoveToPawnTest()
        {}

        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif	/* _ROBOTMOVETOPAWN_HPP */
