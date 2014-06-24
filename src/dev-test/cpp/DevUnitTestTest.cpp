/*!
 * \file
 * \brief Implémentation de la classe UnitTestTest.
 */

#include "DevUnitTestTest.hpp"

using namespace test;

void DevUnitTestTest::testFail()
{
    this->fail("fail - Faux positif");
    this->expectedError("test ERROR UnitTestTest:fail - Faux positif");
}

void DevUnitTestTest::testAssert()
{
    this->assert(true, "Message ne devant pas s'afficher");
    this->assert(false, "assert - Faux positif");
    this->expectedError("test ERROR UnitTestTest:assert - Faux positif");
}

void DevUnitTestTest::suite()
{
    this->testFail();
    this->testAssert();
}
