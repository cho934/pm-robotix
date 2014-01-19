/*!
 * \file
 * \brief Définition de la classe ActionManagerTest.
 */

#ifndef TEST_ACTIONMANAGERTEST_HPP
#define TEST_ACTIONMANAGERTEST_HPP

#include "UnitTest.hpp"

namespace test
{

    /*!
     * \brief Teste la classe \ref pmx::ActionManager.
     */
    class ActionManagerTest : public utils::UnitTest
    {
    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ActionManagerTest() : utils::UnitTest("ActionManagerTest")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ActionManagerTest()
        {
        }

        virtual void suite();

        /*!
         * \brief Teste la méthode \ref pmx::ActionManager::count.
         */
        void testCount();

        /*!
         * \brief Teste la méthode \ref pmx::ActionManager::addAction.
         */
        void testAddAction();

        /*!
         * \brief Teste la méthode \ref pmx::ActionManager::clearActions.
         */
        void testClearActions();

        /*!
         * \brief Teste la méthode \ref pmx::ActionManager::execute.
         */
        void testExecute();
    };
}

#endif
