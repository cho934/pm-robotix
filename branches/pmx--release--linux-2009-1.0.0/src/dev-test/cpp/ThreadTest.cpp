/*!
 * \file
 * \brief Implémentation de la classe ThreadTest.
 */

#include "ThreadTest.hpp"

#include <iostream>

void
test::ThreadTest::suite()
{
    testSimpleThread();
    testDoubleThread();
}

/*!
 * \todo supprimer la validation visuelle.
 */
void
test::ThreadTest::testSimpleThread()
{
    TestThread t1("t1");
    
    t1.start();
    
    while (!t1.finished())
    {
        usleep(1000);
    }
}

/*!
 * \todo supprimer la validation visuelle.
 */
void
test::ThreadTest::testDoubleThread()
{
    TestThread t1("td1");
    TestThread t2("td2");
    
    t1.start();
    t2.start();
    
    while (!t1.finished() && !t2.finished())
    {
        usleep(1000);
    }
}

/*!
 * \todo supprimer la validation visuelle.
 */
void
test::TestThread::execute()
{
    for (uint i = 0; i <= 10; i++)
    {
        usleep(10000);
    }
}
