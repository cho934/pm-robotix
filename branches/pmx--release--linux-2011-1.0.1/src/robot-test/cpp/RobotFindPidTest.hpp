/*!
 * \file
 * \brief Définition de la classe RobotFindPidTest.
 */

#ifndef TEST_ROBOTFINDPIDTEST_HPP
#define TEST_ROBOTFINDPIDTEST_HPP

#include <string>

#include "RobotTest.hpp"
#include "IMotorListener.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace test
{
    /*!
     * \brief Test pour trouver les coefficients de pid vitesse de chaque moteur.
     */
    class RobotFindPidTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref RobotFindPidTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::RobotFindPidTest");
            return instance;
        }
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        RobotFindPidTest() : pmx::RobotTest("RobotFindPidTest : Réglage PID : Avance via PID vitesse avec changement de consigne")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ RobotFindPidTest()
        {}
        
        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
