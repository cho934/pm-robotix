/*!
 * \file
 * \brief Définition de la classe ConfigurationTest.
 */

#ifndef TEST_CONFIGURATIONTEST_H
#define	TEST_CONFIGURATIONTEST_H

#include "DevUnitTest.hpp"
#include "../../common/cpp/Configuration.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Teste la classe \ref utils::Configuration.
     */
    class ConfigurationTest : public utils::DevUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref Configuration.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ConfigurationTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur par défaut.
         */
        ConfigurationTest() : utils::DevUnitTest("ConfigurationTest")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ConfigurationTest()
        {
        }

        /*!
         * \brief Teste la méthode utils::Configuration::load().
         */
        void testLoad();

        /*!
         * \brief Teste la méthode utils::Configuration::getString().
         */
        void testGetString();

        /*!
         * \brief Teste la méthode utils::Configuration::getDouble().
         */
        void testGetDouble();

        /*!
         * \brief Teste la méthode utils::Configuration::getInt().
         */
        void testGetInt();

        /*!
         * \brief Execute les tests associés à la classe \ref ConfigurationTest.
         */
        virtual void suite();
    };
}

#endif
