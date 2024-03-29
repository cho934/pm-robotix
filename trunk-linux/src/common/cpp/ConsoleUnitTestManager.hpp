/*!
 * \file
 * \brief Définition de la classe ConsoleUnitTestManager.
 */

#ifndef PMX_CONSOLEUNITTESTMANAGER_H
#define	PMX_CONSOLEUNITTESTMANAGER_H

#include <vector>
#include <cstdlib>
#include "ConsoleUnitTest.hpp"

namespace pmx
{
    /*!
     * \brief Classe de gestion de l'ensemble des tests de fonctionnement du
     * robot.
     */
    class ConsoleUnitTestManager
    {
    public:
        /*!
         * \brief Type associé aux stockages des tests.
         */
        typedef std::vector<pmx::ConsoleUnitTest *> data_type;
        
    private:
        
        /*!
         * \brief Liste des tests connus par le manager.
         */
        data_type tests_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ConsoleUnitTestManager();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ ConsoleUnitTestManager()
        {}
        
        /*!
         * \brief Ajoute un test au gestionnaire.
         * \param test
         *        Le nouveau test associé au gestionnaire.
         */
        void add(pmx::ConsoleUnitTest * test);
        
        /*!
         * \brief Affiche un menu de sélection des tests.
         */
        void run(char *argv0);
        
        /*!
         * \brief Détermine un test a lancer en fonction des paramètres
         * de la ligne de commande.
         */
        void run(uint nTest, int argc, char *argv[]);
        
    protected:
        
        /*!
         * \brief Execute un test en particulier en fonction de son identifiant.
         * \param nTest
         *        Numéro de test à exécuter (à partir de 1).
         * \param argv
         *        Tableau d'argument.
         */
        void executeTest(uint nTest, char* argv0);
        void executeTest(uint nTest, int argc, char *argv[]);
    };
}

#endif
