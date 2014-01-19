/*!
 * \file
 * \brief Implémentation de la classe ARobotElementTest.
 */

#include "ARobotElementTest.hpp"
#include "ARobotElement.hpp"
#include "Robot.hpp"

class MockRobotElement : public pmx::ARobotElement
{
public:

    MockRobotElement(pmx::Robot & robot) : pmx::ARobotElement(robot)
    {
    }

    virtual ~MockRobotElement()
    {
    }
};

void
test::ARobotElementTest::suite()
{
    this->testRobot();
}

void
test::ARobotElementTest::testRobot()
{
    pmx::Robot robot;
    MockRobotElement instance(robot);
    this->assert(&instance.robot() == &robot, "La propriété robot n'est pas disponible");
}
