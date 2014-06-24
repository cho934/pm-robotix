/*!
 * \file
 * \brief Implementation de la classe UnitTestSuite.
 */

#include <sstream>
#include "DevUnitTestSuite.hpp"
#include "DevUnitTestAppender.hpp"
#include "../../common/cpp/Exception.hpp"

utils::DevUnitTestSuite::DevUnitTestSuite() : tests_()
{
}

void
utils::DevUnitTestSuite::run()
{
	//std::cout << "main robot-test Start" << std::endl;

    logger().info("Lancement des tests unitaires");
    utils::DevUnitTestAppender* appender
            = (utils::DevUnitTestAppender*) & logger().appender();

    appender->flush();
    utils::PointerList<DevUnitTest *>::iterator i = tests_.begin();
    for (; i != tests_.end(); i++)
    {
        appender->increaseIndent();
        DevUnitTest * test = *i;

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
