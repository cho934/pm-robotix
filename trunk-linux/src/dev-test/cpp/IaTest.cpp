/*!
 * \file
 * \brief Implémentation de la classe IaTest.
 */

#include "IaTest.hpp"

void test::IaTest::suite()
{
	logger().debug() << "IaTest : Go" << utils::end;
	testPileManagement();

}

void test::IaTest::testPileManagement()
{
	iaInitialize(0);
	iaExecuteNextAction();
	iaExecuteNextAction();
	iaExecuteNextAction();
	iaExecuteNextAction();
	iaExecuteNextAction();
	iaExecuteNextAction();
}
