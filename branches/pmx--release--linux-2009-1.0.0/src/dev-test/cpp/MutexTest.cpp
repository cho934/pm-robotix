#include "MutexTest.hpp"

void test::MutexTest::testSimpleThread()
{
    test::mutex::Counter* c = new test::mutex::Counter();
    
    for (int i = 0 ; i < 5 ; i++)
    {
        c->addOneWithLock();
        c->addOneWithoutLock();
    }

    if(c->value() != 10)
    {
        fail("Mutex non fonctionnel en environnement simple thread");
        logger().info() << "valeur : " << c->value() << " au lieu de 20" << utils::end;
    }
}

void test::MutexTest::testDoubleThread()
{
    test::mutex::Counter* c = new test::mutex::Counter();
    test::mutex::TestThread t1(c, true);
    test::mutex::TestThread t2(c, false);
    
    t1.start();
    t2.start();
    
    while (!t1.finished() || !t2.finished())
    {
        usleep(1000);
    }
    
    if(c->value() != 20)
    {
        fail("Mutex non fonctionnel en environnement double thread");
        logger().info() << "valeur : " << c->value() << " au lieu de 20" << utils::end;
    }
}

void test::MutexTest::suite()
{
    testSimpleThread();
    testDoubleThread();
}

void test::mutex::TestThread::execute()
{
    for (int i = 0 ; i < 10 ; i++)
    {
        if (implicitLock_)
        {
            counter_->addOneWithLock();
        }
        else
        {
            counter_->lock();
            counter_->addOneWithoutLock();
            counter_->unlock();
        }
        this->yield();
    }
}
