/*!
 * \file
 * \brief Implémentation de la classe ActionManagerTest.
 */

#include "ActionManagerTest.hpp"
#include "ActionManager.hpp"

class MockAction : public pmx::IAction
{
public:

    MockAction()
    {
    }

    virtual ~MockAction()
    {
    }

    virtual bool execute(pmx::IRobotOut *)
    {
        return true;
    }

    virtual std::string info()
    {
        return "MockAction";
    }
};

void
test::ActionManagerTest::suite()
{
    this->testCount();
    this->testAddAction();
    this->testClearActions();
    this->testExecute();
}

void
test::ActionManagerTest::testCount()
{
    /*! \todo Finalize the tests */
    pmx::ActionManager manager;
    this->assert(manager.count() == 0, "ActionManager::count() ne renvoie pas 0 pour un nouvel ActionManager");

    manager.addAction(new MockAction());
    this->assert(manager.count() == 1, "ActionManager::count() ne renvoie pas 1 après un ajout");

    manager.clearActions();
    this->assert(manager.count() == 0, "ActionManager::count() ne renvoie pas 0 après clearActions()");
}

void
test::ActionManagerTest::testAddAction()
{
    /*! \todo Finalize the tests */
}

void
test::ActionManagerTest::testClearActions()
{
    /*! \todo Finalize the tests */
}

void
test::ActionManagerTest::testExecute()
{
    /*! \todo Finalize the tests */
}
