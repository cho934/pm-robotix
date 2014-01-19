/*!
 * \file
 * \brief Définition de la classe RobotMoveIncrementTest.
 */

#ifndef TEST_ROBOTMOVEBYINCREMENTTEST_HPP
#define TEST_ROBOTMOVEBYINCREMENTTEST_HPP

#include <string>
#include "RobotTest.hpp"
#include "Motor.hpp"
#include "MotorLocation.hpp"

namespace test
{
    /*!
     * \brief Test pour faire avancer le robot par incrementation du motor_code pendant un temps donné.
     *
     * Cette classe assure l'étalonnage de la vitesse par rapport aux codes moteur.
     */
    class RobotMoveByIncrementTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref RobotMoveByIncrementTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::RobotMoveByIncrementTest");
            return instance;
        }
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        RobotMoveByIncrementTest() : pmx::RobotTest("RobotMoveByIncrement : Réglage AX+B : Fait avancer le robot par increment")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ RobotMoveByIncrementTest()
        {}
        
        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
