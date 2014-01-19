/*!
 * \file
 * \brief Définition de la classe RobotMoveByPositionTest.
 */

#ifndef TEST_ROBOTMOVEBYPOSITIONTEST_HPP
#define TEST_ROBOTMOVEBYPOSITIONTEST_HPP

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
    class RobotMoveByPositionTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \return Trace associée à la classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::RobotMoveByPositionTest");
            return instance;
        }
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        RobotMoveByPositionTest() : pmx::RobotTest("Faire avancer le robot par position")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ RobotMoveByPositionTest()
        {}
        
        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
