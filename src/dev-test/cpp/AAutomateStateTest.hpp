/*!
 * \file
 * \brief Définition de la classe AAutomateStateTest.
 */

#ifndef TEST_AAUTOMATESTATETEST_HPP
#define	TEST_AAUTOMATESTATETEST_HPP

#include "UnitTest.hpp"

namespace test
{
    /*!
     * \brief Teste la classe \ref pmx::AAutomateState.
     */
    class AAutomateStateTest : public utils::UnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref AAutomateStateTest.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::AAutomateStateTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur par défaut.
         */
        AAutomateStateTest() : utils::UnitTest("AAutomateStateTest")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~AAutomateStateTest()
        {
        }

        /*!
         * \brief Teste la méthode \ref pmx::AAutomateState::addState.
         */
        void testAddState();

        /*!
         * \brief Execute les tests associés à la classe \ref AAutomateStateTest.
         */
        virtual void suite();
    };
}

#endif
