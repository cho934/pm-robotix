/*!
 * \file
 * \brief Définition de la classe RobotTestManager.
 */

#ifndef PMX_ROBOTTESTMANAGER_H
#define	PMX_ROBOTTESTMANAGER_H

#include <vector>
#include "RobotTest.hpp"
#include <cstdlib>

namespace pmx
{
    /*!
     * \brief Classe de gestion de l'ensemble des tests de fonctionnement du
     * robot.
     */
    class RobotTestManager
    {
    public:
        /*!
         * \brief Type associé aux stockages des tests.
         */
        typedef std::vector<pmx::RobotTest *> data_type;
        
    private:
        
        /*!
         * \brief Liste des tests connus par le manager.
         */
        data_type tests_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        RobotTestManager();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ RobotTestManager()
        {}
        
        /*!
         * \brief Ajoute un test au gestionnaire.
         * \param test
         *        Le nouveau test associé au gestionnaire.
         */
        void add(pmx::RobotTest * test);
        
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
