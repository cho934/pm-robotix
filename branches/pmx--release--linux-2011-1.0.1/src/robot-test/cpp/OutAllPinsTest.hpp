/*!
 * \file
 * \brief Définition de la classe OutAllPinsTest.
 */

#ifndef TEST_OUTALLPINSTEST_HPP
#define TEST_OUTALLPINSTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Clignote tous les pins de sorties sur les démultiplexeurs de la carte rouge des démultiplexeurs.
     */
    class OutAllPinsTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref OutAllPinsTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::OutAllPinsTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        OutAllPinsTest() : pmx::RobotTest("RobotOUT: OutAllPinsTest : clignote tous les pins de sortie DM")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ OutAllPinsTest()
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
