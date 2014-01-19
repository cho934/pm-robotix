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
     * \brief Teste la classe \ref utils::Logger.
     */
    class LoggerTest : public utils::UnitTest
    {
    public:

        /*!
         * \brief Constructeur par défaut.
         */
        LoggerTest() : utils::UnitTest("LoggerTest")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~LoggerTest()
        {
        }

        /*!
         * \brief Teste la classe \ref utils::Logger (tests visuels).
         */
        void testLogger();

        /*!
         * \brief Execute les tests associés à la classe \ref LoggerTest.
         */
        virtual void suite();
    };
};

#endif
