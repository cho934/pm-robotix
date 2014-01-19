/*!
 * \file
 * \brief Définition de la classe ClampTest.
 */

#ifndef TEST_CLAMPTEST_HPP
#define TEST_CLAMPTEST_HPP

#include <string>

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace test
{
    /*!
     * \brief Test pour utiliser la pince.
     */
    class ClampTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ClampTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ClampTest");
            return instance;
        }
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ClampTest() : pmx::RobotTest("ClampTest : Tester la pince du robot.")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ ClampTest()
        {}
        
        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
