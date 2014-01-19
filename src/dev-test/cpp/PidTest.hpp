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
     * \brief Teste la classe \ref utils::PID.
     */
    class PidTest : public utils::UnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref PidTest.
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
        PidTest() : utils::UnitTest("PidTest")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~PidTest()
        {
        }

        /*!
         * \brief Test des getters de la classe \ref utils::PID.
         */
        void testGetters();

        /*!
         * \brief Test de la méthode \ref utils::PID::ComputePID de la classe
         * \ref utils::PID avec des facteurs de (1, 0, 0).
         */
        void testComputePIDForP();

        /*!
         * \brief Test de la méthode \ref utils::PID::ComputePID de la classe
         * \ref utils::PID avec des facteurs de (0, 1, 0).
         */
        void testComputePIDForI();

        /*!
         * \brief Test de la méthode \ref utils::PID::ComputePID de la classe
         * \ref utils::PID avec des facteurs de (0, 0, 1).
         */
        void testComputePIDForD();

        /*!
         * \brief Execute les tests associés à la classe \ref PidTest.
         */
        virtual void suite();
    };
}

#endif
