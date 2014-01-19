/*!
 * \file
 * \brief Définition de la classe ClampTest.
 */

#ifndef TEST_SERVOTEST_HPP
#define TEST_SERVOTEST_HPP

#include <string>
#include "RobotTest.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace test
{
    /*!
     * \brief Tests pour utiliser les objets servomotors.
     */
    class ServoTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ClampTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ServoTest");
            return instance;
        }
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ServoTest() : pmx::RobotTest("ServoTest : Tester les objets servomoteurs du robot.")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ ServoTest()
        {}
        
        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
