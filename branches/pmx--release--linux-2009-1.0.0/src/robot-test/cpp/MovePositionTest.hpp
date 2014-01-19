/*!
 * \file
 * \brief Définition de la classe RobotPositionTest.
 */

#ifndef TEST_MOVEPOSITIONTEST_HPP
#define	TEST_MOVEPOSITIONTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief
     */
    class MovePositionTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \return Trace associée à la classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::MovePositionTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        MovePositionTest() : pmx::RobotTest("Faire avancer le robot à une position donnée")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ MovePositionTest()
        {}
        
        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
}

#endif
