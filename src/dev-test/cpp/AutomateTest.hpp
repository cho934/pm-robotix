/*!
 * \file
 * \brief Définition de la classe AutomateTest.
 */

#ifndef TEST_AUTOMATETEST_HPP
#define TEST_AUTOMATETEST_HPP

#include "UnitTest.hpp"

namespace test
{

    /*!
     * \brief Teste la classe \ref pmx::Automate.
     */
    class AutomateTest : public utils::UnitTest
    {
    public:

        /*!
         * \brief Constructeur de la classe.
         */
        AutomateTest() : utils::UnitTest("AutomateTest")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~AutomateTest()
        {
        }

        virtual void suite();

        /*!
         * \brief Teste la méthode \ref pmx::Automate::run.
         */
        void testRun();
    };
}

#endif
