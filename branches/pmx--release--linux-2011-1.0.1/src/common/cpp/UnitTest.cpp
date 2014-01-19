/*!
 * \file
 * \brief Implémentation de la classe UnitTest.
 */

#include "UnitTest.hpp"
#include <iostream>

utils::UnitTest::UnitTest(const std::string & name)
{
    name_ = name;
}

void
utils::UnitTest::assert(bool test, const std::string & message)
{
    if (!test)
    {
        fail(message);
    }
}

void
utils::UnitTest::fail(const std::string & message)
{
    logger().error() << name() << ":" << message << utils::end;
}
