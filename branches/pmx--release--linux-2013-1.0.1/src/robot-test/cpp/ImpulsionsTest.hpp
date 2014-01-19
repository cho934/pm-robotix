/*!
 * \file
 * \brief Définition de la classe ImpulsionsTest.
 */

#ifndef TEST_IMPULSIONSTEST_HPP
#define TEST_IMPULSIONSTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Compte le nombre d'impulsions gauche et droite et l'affiche
     * instantanément à l'ecran.
     */
    class ImpulsionsTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ImpulsionsTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ImpulsionsTest");
            return instance;
        }
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ImpulsionsTest() : pmx::RobotTest("RobotIN : ImpulsionsTest : Compter les impulsions des codeurs")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ ImpulsionsTest()
        {}
        
        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
