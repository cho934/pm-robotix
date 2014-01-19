/*!
 * \file
 * \brief Définition de la classe RobotMoveTest.
 */

#ifndef TEST_ROBOTMOVETEST_HPP
#define TEST_ROBOTMOVETEST_HPP

#include <string>

#include "RobotTest.hpp"
#include "IMotorListener.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace test
{
    /*!
     * \brief Test pour faire avancer le robot pendant un temps demandé par application d'un motorcode D et G demandée.
     */
    class RobotMoveTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \return Trace associée à la classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::RobotMoveTest");
            return instance;
        }
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        RobotMoveTest() : pmx::RobotTest("Faire avancer le robot avec demande de temps/motorCodeD/motorCodeG")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ RobotMoveTest()
        {}
        
        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
