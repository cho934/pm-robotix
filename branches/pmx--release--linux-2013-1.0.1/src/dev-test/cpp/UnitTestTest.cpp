/*!
 * \file
 * \brief Implémentation de la classe UnitTestTest.
 */

#include "UnitTestTest.hpp"

using namespace test;

void UnitTestTest::testFail()
{
    this->fail("fail - Faux positif");
    this->expectedError("test ERROR UnitTestTest:fail - Faux positif");
}

void UnitTestTest::testAssert()
{
    this->assert(true, "Message ne devant pas s'afficher");
    this->assert(false, "assert - Faux positif");
    this->expectedError("test ERROR UnitTestTest:assert - Faux positif");
}

void UnitTestTest::suite()
{
    this->testFail();
    this->testAssert();
}
