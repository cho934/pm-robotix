/*!
 * \file
 * \brief Définition de la classe OutPinsTest.
 */

#ifndef TEST_OUTPINSTEST_HPP
#define TEST_OUTPINSTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Clignote un pin de sortie DM.
     */
    class OutPinsTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref OutPinsTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::OutPinsTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        OutPinsTest() : pmx::RobotTest("RobotOUT: OutPinsTest : Clignote un pin de sortie DM")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ OutPinsTest()
        {}
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);

    };
};

#endif
