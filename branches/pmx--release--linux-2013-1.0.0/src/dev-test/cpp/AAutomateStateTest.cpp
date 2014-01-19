/*!
 * \file
 * \brief Implémentation de la classe AAutomateStateTest.
 */

#include "AAutomateStateTest.hpp"
#include "AAutomateState.hpp"

namespace test
{
    /*!
     * \brief Classe de test associé au test \ref test::AAutomateStateTest.
     */
    class MockAutomateState : public pmx::AAutomateState
    {
    public:

        /*!
         * Constructeur de la classe.
         */
        MockAutomateState()
        {
        }

        /*!
         * Destructeur de la classe.
         */
        virtual ~MockAutomateState()
        {
        }
          std::string name(){
            return "MockAutomateState";
        }
        /*!
         * \brief Ne fait rien.
         *
         * \param robot Le paramètre n'est pas utilisé.
         * \param data Le paramètre n'est pas utilisé.
         * \return retourne \c null.
         */
        virtual pmx::IAutomateState* execute(pmx::Robot& , void * )
        {
            return NULL;
        }
    };
}

void
test::AAutomateStateTest::suite()
{
    this->testAddState();
}

void
test::AAutomateStateTest::testAddState()
{
    logger().info() << "AAutomateStateTest::testAddState()" << utils::end;

    test::MockAutomateState instance;
    instance.addState("first", NULL);
    this->assert(instance.getState("first") == NULL, "La méthode addState() ne fonctionne pas");

    instance.addState("second", &instance);
    this->assert(instance.getState("second") == &instance, "La méthode addState() ne fonctionne pas2");

    this->assert(instance.getState("last") == NULL, "La méthode addState() ne fonctionne pas3");
}
