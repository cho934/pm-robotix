/*!
 * \file
 * \brief Définition de la classe RobotMoveTest.
 */

#ifndef TEST_ROBOTMOVETEST_HPP
#define TEST_ROBOTMOVETEST_HPP

#include <string>
#include "RobotTest.hpp"
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
         * \brief Retourne le \ref Logger associé à la classe \ref RobotMoveTest.
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
        RobotMoveTest() : pmx::RobotTest("RobotMoveTest : Fait avancer le robot à une position donnée avec ou sans correction par vecteur d'approche.")
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
