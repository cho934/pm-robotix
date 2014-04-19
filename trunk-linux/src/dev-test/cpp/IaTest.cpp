/*!
 * \file
 * \brief Implémentation de la classe IaTest.
 */

#include "IaTest.hpp"

void test::IaTest::suite()
{
	logger().debug() << "IaTest : Go" << utils::end;
	testcho();

}

void test::IaTest::testcho()
{

	Imprimer(2);
}
