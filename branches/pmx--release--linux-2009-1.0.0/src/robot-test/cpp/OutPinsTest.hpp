/*!
 * \file
 * \brief Définition de la classe UnitTestTestDM.
 */

#ifndef TEST_OUTPINSTEST_HPP
#define TEST_OUTPINSTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test de LED sur tous les pins de tous les démultiplexeurs.
     */
    class OutPinsTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \return Trace associé à la classe.
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
        OutPinsTest() : pmx::RobotTest("Incrémentation de tous les pins de sortie")
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
        
    private:
        
        /*!
         * \brief (Fonction interne) Affiche une ligne de résultat.
         * \param dm Numéro du démultiplexeur courant.
         * \param nPin Numéro de la pin courante.
         * \param state Etat appliqué.
         */
        void drawLine(int dm, int nPin, bool state);
    };
};

#endif
