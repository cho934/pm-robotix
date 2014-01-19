/*!
 * \File
 * \brief Implémentation de la classe PointerListTest.
 */

#include <string>
#include "PointerListTest.hpp"
#include "PointerList.hpp"

#ifndef NULL
#define NULL ((void *)0)
#endif

void
test::PointerListTest::suite()
{
    this->testConstructorDefault();
    this->testConstructorInitialized();
    this->testConstructorCopy();
    this->testConstructorRange();
    this->testDestructor();
}

void
test::PointerListTest::testConstructorDefault()
{
    utils::PointerList<std::string*> instance;
    this->assert(instance.size() == 0, "Le constructeur pas défaut ne fournit pas une liste vide");
}

void
test::PointerListTest::testConstructorInitialized()
{
    /*utils::PointerList<std::string*> instance(10, NULL);
    this->assert(instance.size() == 10, "Le constructeur initialisé ne fournit pas le nombre de résultats attendus");
     */
}

void
test::PointerListTest::testConstructorCopy()
{
    /*utils::PointerList<std::string*> list(10, NULL);
    utils::PointerList<std::string*> instance(list);
    this->assert(instance.size() == 10, "Le constructeur par copie ne fournit pas le nombre de résultats attendus");*/
}

void
test::PointerListTest::testConstructorRange()
{
    /*utils::PointerList<std::string*> list(10, NULL);
    utils::PointerList<std::string*> instance(list.begin(), list.end());
    this->assert(instance.size() == 10, "Le constructeur par copie ne fournit pas le nombre de résultats attendus");*/
}

void
test::PointerListTest::testDestructor()
{
    /*utils::PointerList<std::string*> * instance1 = new utils::PointerList<std::string*>(10, NULL);
    try
    {
        delete instance1;
    }
    catch (std::exception* e)
    {
        this->fail("An exception occurs during the destruction of NULL elements");
        delete e;
    }

    utils::PointerList<std::string*> * instance2 = new utils::PointerList<std::string*>();
    try
    {
        delete instance2;
    }
    catch (std::exception* e)
    {
        this->fail("An exception occurs during the destruction an empty list");
        delete e;
    }

    utils::PointerList<std::string*> * instance3 = new utils::PointerList<std::string*>();
    instance3->push_front(new std::string("test"));
    instance3->push_front(new std::string("test"));
    try
    {
        delete instance3;
    }
    catch (std::exception* e)
    {
        this->fail("An exception occurs during the destruction an initialized list");
        delete e;
    }*/
}
