/*!
 * \file
 * \brief Définition de la classe TestM.
 */

#ifndef TESTM4_HPP
#define TESTM4_HPP

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
         * \return Trace associé à la classe.
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
        ImpulsionsTest() : pmx::RobotTest("Compter les impulsions sur les roues codeuses")
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
