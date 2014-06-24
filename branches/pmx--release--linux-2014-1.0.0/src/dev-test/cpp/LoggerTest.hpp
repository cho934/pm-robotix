/*!
 * \file
 * \brief Définition de la classe LoggerTest.
 */

#ifndef TEST_LOGGER_TEST_HPP
#define TEST_LOGGER_TEST_HPP

#include "DevUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Teste la classe \ref utils::Logger.
     */
    class LoggerTest : public utils::DevUnitTest
    {
    public:

        /*!
         * \brief Constructeur par défaut.
         */
        LoggerTest() : utils::DevUnitTest("LoggerTest")
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
