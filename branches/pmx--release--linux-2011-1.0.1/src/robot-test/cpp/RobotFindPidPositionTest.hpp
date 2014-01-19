/*!
 * \file
 * \brief Définition de la classe RobotFindPidPositionTest.
 */

#ifndef TEST_ROBOTFINDPIDPOSITIONTEST_HPP
#define TEST_ROBOTFINDPIDPOSITIONTEST_HPP

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
    class RobotFindPidPositionTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref RobotFindPidPositionTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::RobotFindPidPositionTest");
            return instance;
        }
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        RobotFindPidPositionTest() : pmx::RobotTest("RobotFindPidPositionTest : Réglage PID : Avance via PID vitesse et position")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ RobotFindPidPositionTest()
        {}
        
        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
