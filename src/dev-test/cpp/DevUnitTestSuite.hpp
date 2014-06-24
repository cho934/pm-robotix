/*!
 * \file
 * \brief Définition de la classe DevUnitTestSuite.
 */

#ifndef UTILS_DEVUNITTESTSUITE_H
#define UTILS_DEVUNITTESTSUITE_H

#include "../../common/cpp/PointerList.hpp"
#include "DevUnitTest.hpp"


namespace utils
{
    /*!
     * \brief Cette classe assure la gestion d'une suite de tests unitaires.
     */
    class DevUnitTestSuite
    {
    private:

        /*!
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
         */
        static inline const utils::Logger & logger()
        {
            return utils::LoggerFactory::logger("test");
        }

        /*!
         * \brief Ensemble des tests associés à cette suite.
         */
        utils::PointerList<DevUnitTest*> tests_;

    public:
        /*!
         * \brief Constructeur de la classe.
         */
        DevUnitTestSuite();

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~DevUnitTestSuite()
        {
        }

        /*!
         * \brief Ajoute un objet de test à cette suite sous la forme d'un
         * pointeur qui sera détruit en même temps que cette suite.
         *
         * \param unitTest
         *        Pointeur vers l'objet de test.
         */
        inline void addTest(DevUnitTest * unitTest)
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
