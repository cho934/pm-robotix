/*!
 * \file
 * \brief Implementation de la classe UnitTestSuite.
 */

#include <sstream>
#include "UnitTestSuite.hpp"
#include "Exception.hpp"
#include "UnitTestAppender.hpp"

utils::UnitTestSuite::UnitTestSuite() : tests_()
{
}

void
utils::UnitTestSuite::run()
{
    logger().info("Lancement des tests unitaires");
    utils::UnitTestAppender* appender
            = (utils::UnitTestAppender*) & logger().appender();

    appender->flush();
    utils::PointerList<UnitTest *>::iterator i = tests_.begin();
    for (; i != tests_.end(); i++)
    {
        appender->increaseIndent();
        UnitTest * test = *i;

        bool succeed;
        try
        {
            test->suite();
            succeed = appender->messages().size() == 0;
        }
        catch (Exception* exception)
        {
            std::ostringstream oss;
            oss << "Le test à généré une exception: " << exception->what();
            test->fail(oss.str());
            succeed = false;
        }
        catch (std::exception* exception)
        {
            std::ostringstream oss;
            oss << "Le test à généré une exception: " << exception->what();
            test->fail(oss.str());
            succeed = false;
        }

        logger().info()
                << (succeed ? "[OK]   " : "[FAIL] ")
                << "Execution de <"
                << test->name()
                << ">"
                << utils::end;

        appender->decreaseIndent();
        appender->flush();
    }

    logger().info("Fin des test unitaires");
}
