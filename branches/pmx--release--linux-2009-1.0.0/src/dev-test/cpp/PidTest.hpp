/*!
 * \file
 * \brief Définition de la classe PidTest.
 */

#ifndef TEST_PIDTEST_H
#define	TEST_PIDTEST_H

#include "LoggerFactory.hpp"
#include "UnitTest.hpp"
#include "PID.hpp"

namespace test
{
    /*!
     * \brief Tests unitaires de la classe utils::Pid.
     */
    class PidTest : public utils::UnitTest
    {
    private:
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::PidTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        PidTest(): utils::UnitTest("PidTest")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ PidTest()
        {}
        
        /*!
         * \brief Test des getters de la classe utils::Pid.
         */
        void testGetters();
        
        /*!
         * \brief Test de la méthode ComputePID() de la classe utils::Pid avec des facteurs de (1, 0, 0).
         */
        void testComputePIDForP();
        
        /*!
         * \brief Test de la méthode ComputePID() de la classe utils::Pid avec des facteurs de (0, 1, 0).
         */
        void testComputePIDForI();
        
        /*!
         * \brief Test de la méthode ComputePID() de la classe utils::Pid avec des facteurs de (0, 0, 1).
         */
        void testComputePIDForD();
        
        /*!
         * \brief Exécution des tests.
         */
        virtual void suite();
    };
}

#endif
