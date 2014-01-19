/*!
 * \file
 * \brief Implémentation de la classe UnitTestTest.
 */

#include "UnitTestTest.hpp"

using namespace test;

void UnitTestTest::testFail()
{
    fail("fail - Faux positif");
}

void UnitTestTest::testAssert()
{
    assert(true, "Message ne devant pas s'afficher");
    assert(false, "assert - Faux positif");
}

void UnitTestTest::suite()
{
    testFail();
    testAssert();
}
