/*!
 * \file
 * \brief Définition de la classe UnitTest..
 */

#ifndef PMX_UNITTEST_H
#define	PMX_UNITTEST_H

#include <string>

namespace pmx
{
    /*!
     * \brief Classe abstraite servant de base pour les tests de fonctionnement
     * des tests unitaires..
     */
    class UnitTest
    {
    private:
        
        /*!
         * \brief Nom du test.
         */
        std::string name_;
        
    protected:
        
        /*!
         * \brief Constructeur de la classe.
         * \param name
         *        Nom du test.
         */
        UnitTest(const std::string & name) : name_(name)
        {}
        
    public:
        
        /*!
         * Destructeur de la classe.
         */
        virtual inline ~ UnitTest()
        {}
        
        /*!
         * \return Nom du test.
         */
        inline const std::string & name() const
        {
            return name_;
        }
        
        /*!
         * Méthode exécutant le test associé.
         */
        virtual void run(int argc, char *argv[]) =0;
    };
}

#endif
