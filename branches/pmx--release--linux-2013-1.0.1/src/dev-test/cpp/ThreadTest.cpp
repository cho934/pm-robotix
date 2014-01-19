/*!
 * \file
 * \brief Implémentation de la classe ThreadTest.
 */

#include <cstdlib>
#include <iostream>
#include "ThreadTest.hpp"
#include "DummyThread.hpp"

void
test::ThreadTest::suite() {
     testSimpleThread();
      testDoubleThread();
    testTripleThread();
}

void
test::ThreadTest::testSimpleThread() {
    logger().info() << "testSimpleThread()" << utils::end;
    DummyThread t1("1t1");

    t1.start();
    // logger().info() << "testSimpleThread() start done" << utils::end;
    while (!t1.finished()) {
        usleep(1000);
    }
    t1.waitForEnd();
    logger().info() << "testSimpleThread End" << utils::end;
}

void
test::ThreadTest::testDoubleThread() {
    logger().info() << "testDoubleThread()" << utils::end;
    DummyThread t1("2td1");
    DummyThread t2("2td2");

    t1.start();
    t2.start();

    while (!t1.finished() && !t2.finished()) {
        usleep(1000);
    }
    t1.waitForEnd();
    t2.waitForEnd();
    logger().info() << "testDoubleThread End" << utils::end;
}

void
test::ThreadTest::testTripleThread() {
    logger().info() << "testTripleThread()" << utils::end;
    DummyThread t1("3td1");
    DummyThread t2("3td2");
    DummyThread t3("3td3");

    t1.start();
    t2.start();
    t3.start();

    while (!t1.finished() && !t2.finished() && !t3.finished()) {
        usleep(1000);
    }
    t1.waitForEnd();
    t2.waitForEnd();
    t3.waitForEnd();
    logger().info() << "testTripleThread End" << utils::end;
}


