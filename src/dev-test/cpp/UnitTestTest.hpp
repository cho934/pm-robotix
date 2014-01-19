/*!
 * \file
 * \brief Définition de la classe UnitTestTest.
 */

#ifndef TEST_UNIT_TEST_TEST_HPP
#define TEST_UNIT_TEST_TEST_HPP

#include "UnitTest.hpp"

namespace test
{
    /*!
     * \brief Test unitaire des tests unitaires.
     * Ces tests valident le bon fonctionnement des méthodes de test unitaires
     * tels que fail() et assert().
     */
    class UnitTestTest : public utils::UnitTest
    {
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        UnitTestTest() : utils::UnitTest("UnitTestTest")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ UnitTestTest()
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
