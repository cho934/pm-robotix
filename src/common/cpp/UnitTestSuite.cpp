/*!
 * \file
 * \brief Implementation de la classe UnitTestSuite.
 */

#include "UnitTestSuite.hpp"

utils::UnitTestSuite::UnitTestSuite() : tests_()
{}

void
utils::UnitTestSuite::run()
{
    utils::PointerList<UnitTest *>::iterator i = tests_.begin();
    for (; i != tests_.end(); i++)
    {
        UnitTest * test = *i;
        test->suite();
    }
}
