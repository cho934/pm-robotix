/*!
 * \File
 * \brief Implémentation de la classe AutomateTest.
 */

#include "AutomateTest.hpp"
#include "Automate.hpp"
#include "AAutomateState.hpp"
#include "Robot.hpp"

class MockState : public pmx::AAutomateState
{
private:

    bool executed_;

public:

    MockState() : executed_(false)
    {
    }

    virtual ~MockState()
    {
    }

    virtual pmx::IAutomateState* execute(pmx::Robot & , void * )
    {
        this->executed_ = true;
        return NULL;
    }

    bool executed() const
    {
        return this->executed_;
    }
};

void
test::AutomateTest::suite()
{
    this->testRun();
}

void
test::AutomateTest::testRun()
{
    pmx::Robot robot;
    pmx::Automate instance;
    pmx::IAutomateState* state = new MockState();

    // Test avec un paramètre null - doit réussir et ne rien faire.
    instance.run(robot, NULL, NULL);

    // Test avec un parametre initialisé
    instance.run(robot, state, NULL);
}
