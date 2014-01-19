/*!
 * \file
 * \brief Définition de la classe RobotNoPidTest.
 */

#ifndef TEST_ROBOTNOPIDTEST_HPP
#define TEST_ROBOTNOPIDTEST_HPP

#include <string>
#include "RobotTest.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace test
{
    /*!
     * \brief Test pour faire avancer le robot pendant un temps demandé par application d'un motorcode D et G demandée.
     */
    class RobotNoPidTest : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref RobotNoPidTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::RobotNoPidTest");
            return instance;
        }
    public:

        /*!
         * \brief Constructeur de la classe.
         */
        RobotNoPidTest() : pmx::RobotTest("RobotNoPidTest : Fait avancer le robot par motorCode.")
        {}

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ RobotNoPidTest()
        {}

        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
