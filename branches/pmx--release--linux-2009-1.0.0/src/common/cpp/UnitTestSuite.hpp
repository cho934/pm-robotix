/*!
 * \file
 * \brief Définition de la classe UnitTestSuite.
 */

#ifndef _UNITTESTSUITE_H
#define	_UNITTESTSUITE_H

#include "PointerList.hpp"
#include "UnitTest.hpp"

namespace utils
{
    /*!
     * \brief Cette classe assure la gestion d'une suite de tests unitaires.
     */
    class UnitTestSuite
    {
    private:
        
        /*!
         * \brief Ensemble des tests associés à cette suite.
         */
        utils::PointerList<UnitTest*> tests_;
        
    public:
        /*!
         * \brief Constructeur de la classe.
         */
        UnitTestSuite();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~UnitTestSuite()
        {}
        
        /*!
         * \brief Ajoute un objet de test à cette suite sous la forme d'un
         * pointeur qui sera détruit en même temps que cette suite.
         *
         * \param unitTest
         *        Pointeur vers l'objet de test.
         */
        inline void addTest(UnitTest * unitTest)
        {
            tests_.push_back(unitTest);
        }
        
        /*!
         * \brief Execution de tous les tests.
         */
        void run();
    };
}

#endif
