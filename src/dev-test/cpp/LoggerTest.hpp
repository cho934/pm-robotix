/*!
 * \file
 * \brief Définition de la classe LoggerTest.
 */

#ifndef TEST_LOGGER_TEST_HPP
#define TEST_LOGGER_TEST_HPP

#include "UnitTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Tests unitaires de la classe utils::Logger.
     */
    class LoggerTest: public utils::UnitTest
    {
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        LoggerTest(): utils::UnitTest("LoggerTest")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ LoggerTest()
        {}
        
        /*!
         * \brief Test de la classe utils::Logger (tests visuels).
         */
        void testLogger();
        
        /*!
         * \brief Exécution des tests.
         */
        virtual void suite();
    };
};

#endif
