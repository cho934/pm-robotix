/*!
 * \file
 * \brief Définition de la classe RobotMoveByXYTest.
 */

#ifndef TEST_ROBOTMOVEBYXYTEST_HPP
#define TEST_ROBOTMOVEBYXYTEST_HPP

#include <string>

#include "RobotTest.hpp"
#include "IMotorListener.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace test
{
    /*!
     * \brief Test pour faire avancer le robot par position.
     */
    class RobotMoveByXYTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref RobotMoveByXYTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::RobotMoveByXYTest");
            return instance;
        }
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        RobotMoveByXYTest() : pmx::RobotTest("RobotMoveByXYTest : Faire avancer le robot à partir de point x,y,teta.")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ RobotMoveByXYTest()
        {}
        
        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
