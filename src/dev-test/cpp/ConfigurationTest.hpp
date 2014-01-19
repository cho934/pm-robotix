#ifndef TEST_CONFIGURATIONTEST_H
#define	TEST_CONFIGURATIONTEST_H

#include "UnitTest.hpp"
#include "Configuration.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Tests unitaires de la classe utils::Configuration.
     */
    class ConfigurationTest : public utils::UnitTest
    {
    private:
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
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
        ConfigurationTest() : utils::UnitTest("ConfigurationTest")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ ConfigurationTest()
        {}
        
        /*!
         * \brief Test de la classe utils::Configuration.
         */
        void testLoad();
        
        /*!
         * \brief Exécution des tests.
         */
        virtual void suite();
    };
}

#endif	/* TEST_CONFIGURATIONTEST_H */
