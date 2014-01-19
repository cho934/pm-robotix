/*!
 * \file
 * \brief Définition de la classe ApfInXenomaiTest.
 */

#ifndef TEST_APFINXENOMAITEST_HPP
#define	TEST_APFINXENOMAITEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test de récupération des codeurs gauche et droit par interruption materiel xenomai.
     */
    class ApfInXenomaiTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfInXenomaiTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfInXenomaiTest");
            return instance;
        }

        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ApfInXenomaiTest() : pmx::RobotTest("APFIN  : ApfInXenomaiTest : Test des interruptions via Xenomai")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ ApfInXenomaiTest()
        {}
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
        
    };
};

#endif
