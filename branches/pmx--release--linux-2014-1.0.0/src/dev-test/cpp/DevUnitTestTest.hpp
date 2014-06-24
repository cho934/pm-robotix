/*!
 * \file
 * \brief Définition de la classe DevUnitTestTest.
 */

#ifndef TEST_DEVUNIT_TEST_TEST_HPP
#define TEST_DEVUNIT_TEST_TEST_HPP

#include "DevUnitTest.hpp"

namespace test
{
    /*!
     * \brief Test unitaire des tests unitaires.
     * Ces tests valident le bon fonctionnement des méthodes de test unitaires
     * tels que fail() et assert().
     */
    class DevUnitTestTest : public utils::DevUnitTest
    {
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
    	DevUnitTestTest() : utils::DevUnitTest("UnitTestTest")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ DevUnitTestTest()
        {}
        
        /*!
         * \brief Test de la méthode UnitTest::fail() (tests visuels).
         */
        void testFail();
        
        /*!
         * \brief Test de la méthode UnitTest::assert() (tests visuels).
         */
        void testAssert();
        
        /*!
         * \brief Exécution des tests.
         */
        virtual void suite();
    };
};

#endif
