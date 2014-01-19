/*!
 * \file
 * \brief Définition de la classe DistanceSensorTest.
 */

#ifndef TEST_DISTANCESENSORTEST_HPP
#define	TEST_DISTANCESENSORTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Test des capteurs de distance GP2 du robot.
     */
    class DistanceSensorTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref DistanceSensorTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::DistanceSensorTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        DistanceSensorTest() : pmx::RobotTest("RobotIN : DistanceSensorTest : Tests des GP2")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ DistanceSensorTest()
        {}
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
        
    };
};

#endif
