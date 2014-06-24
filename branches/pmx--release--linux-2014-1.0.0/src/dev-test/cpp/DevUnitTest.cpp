/*!
 * \file
 * \brief Implémentation de la classe DevUnitTest.
 */

#include <iostream>
#include "DevUnitTest.hpp"
#include "DevUnitTestAppender.hpp"
#include "../../common/cpp/Exception.hpp"

utils::DevUnitTest::DevUnitTest(const std::string & name)
{
    name_ = name;
}

void
utils::DevUnitTest::assert(bool test, const std::string & message)
{
    if (!test)
    {
        fail(message);
    }
}

void
utils::DevUnitTest::fail(const std::string & message)
{
    logger().error() << name() << ":" << message << utils::end;
}

void
utils::DevUnitTest::expectedError(const std::string & expected)
{
    this->expectedError(expected, "An error was expected byt was not raised");
}

void
utils::DevUnitTest::expectedError(const std::string & expected, const std::string & message)
{
    utils::Logger* rootLogger = utils::LoggerFactory::instance().rootLogger();
    utils::DevUnitTestAppender* appender = (utils::DevUnitTestAppender*) & rootLogger->appender();

    if (!appender->expectedError(expected))
    {
        this->fail(message);
    }
}
