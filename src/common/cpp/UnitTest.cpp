/*!
 * \file
 * \brief Implémentation de la classe UnitTest.
 */

#include <iostream>
#include "UnitTest.hpp"
#include "Exception.hpp"
#include "UnitTestAppender.hpp"

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

void
utils::UnitTest::expectedError(const std::string & expected)
{
    this->expectedError(expected, "An error was expected byt was not raised");
}

void
utils::UnitTest::expectedError(const std::string & expected, const std::string & message)
{
    utils::Logger* rootLogger = utils::LoggerFactory::instance().rootLogger();
    utils::UnitTestAppender* appender = (utils::UnitTestAppender*) & rootLogger->appender();

    if (!appender->expectedError(expected))
    {
        this->fail(message);
    }
}
