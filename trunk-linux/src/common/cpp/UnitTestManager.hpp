/*!
 * \file
 * \brief Définition de la classe RobotTestManager.
 */

#ifndef PMX_UNITTESTMANAGER_H
#define	PMX_UNITTESTMANAGER_H

#include <vector>
#include <cstdlib>
#include "UnitTest.hpp"

namespace pmx
{
    /*!
     * \brief Classe de gestion de l'ensemble des tests de fonctionnement du
     * robot.
     */
    class UnitTestManager
    {
    public:
        /*!
         * \brief Type associé aux stockages des tests.
         */
        typedef std::vector<pmx::UnitTest *> data_type;
        
    private:
        
        /*!
         * \brief Liste des tests connus par le manager.
         */
        data_type tests_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        UnitTestManager();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ UnitTestManager()
        {}
        
        /*!
         * \brief Ajoute un test au gestionnaire.
         * \param test
         *        Le nouveau test associé au gestionnaire.
         */
        void add(pmx::UnitTest * test);
        
        /*!
         * \brief Affiche un menu de sélection des tests.
         */
        void run();
        
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
        void executeTest(uint nTest);
        void executeTest(uint nTest, int argc, char *argv[]);
    };
}

#endif
