/*!
 * \file
 * \brief Implémentation de la classe MutexTest.
 */

#include "MutexTest.hpp"

#include <unistd.h>

#include "../../common/cpp/Logger.hpp"

void test::MutexTest::testSimpleThread() {
    test::mutex::Counter* c = new test::mutex::Counter();

    for (int i = 0; i < 5; i++) {
        c->addOneWithLock();
        c->addOneWithoutLock();
    }

    if (c->value() != 10) {
        fail("Mutex non fonctionnel en environnement simple thread");
        logger().info() << "valeur : " << c->value() << " au lieu de 20" << utils::end;
    }
    delete c;
}

void test::MutexTest::testDoubleThread() {
    test::mutex::Counter* c = new test::mutex::Counter();
    test::mutex::TestThread t1(c, true);
    test::mutex::TestThread t2(c, false);

    t1.start("t1");
    t2.start("t2");

    t1.waitForEnd();
    t2.waitForEnd();

    if (c->value() != 20) {
        fail("Mutex non fonctionnel en environnement double thread");
        logger().info() << "valeur : " << c->value() << " au lieu de 20" << utils::end;
    }

    delete c;
}

void test::MutexTest::suite() {
    logger().info() << "MutexTest : Go" << utils::end;
    testSimpleThread();
    testDoubleThread();
}

void test::mutex::TestThread::execute() {

    for (int i = 0; i < 10; i++) {
        if (implicitLock_) {
            counter_->addOneWithLock();
        }else {
            counter_->lock();
            counter_->addOneWithoutLock();
            counter_->unlock();
        }
        usleep(1000);
    }
}
