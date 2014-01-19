/*!
 * \file
 * \brief Implémentation de la classe ThreadTest.
 */

#include <cstdlib>
#include <iostream>
#include "ThreadTest.hpp"

void
test::ThreadTest::suite()
{
    testSimpleThread();
    testDoubleThread();
    testTripleThread();
}

void
test::ThreadTest::testSimpleThread()
{
    logger().info() << "testSimpleThread()" << utils::end;
    TestThread t1("1t1");

    t1.start();

    while (!t1.finished())
    {
        usleep(1000);
    }

    logger().info() << "testSimpleThread End" << utils::end;
}

void
test::ThreadTest::testDoubleThread()
{
    logger().info() << "testDoubleThread()" << utils::end;
    TestThread t1("2td1");
    TestThread t2("2td2");

    t1.start();
    t2.start();

    while (!t1.finished() && !t2.finished())
    {
        usleep(1000);
    }

    logger().info() << "testDoubleThread End" << utils::end;
}

void
test::ThreadTest::testTripleThread()
{
    logger().info() << "testTripleThread()" << utils::end;
    TestThread t1("3td1");
    TestThread t2("3td2");
    TestThread t3("3td3");

    t1.start();
    t2.start();
    t3.start();

    while (!t1.finished() && !t2.finished() && !t3.finished())
    {
        usleep(1000);
    }

    logger().info() << "testTripleThread End" << utils::end;
}

void
test::TestThread::execute()
{
    debugThread("TestThread");
    if (this->name_ == "3td2")
    {
        sleep(5); //test du sleep sur le 2ème thread.
    }
    else
    {
        simpleCount(this->name_);
    }
}

void
test::TestThread::simpleCount(std::string name)
{
    //compter pendant 5s
    int j = 0;
    time_t start = time(NULL); //! \todo supprimer time_t et utiliser chronometer
    while (start + 5 > time(NULL))
    {
        j++;
    }
}
