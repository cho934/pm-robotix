/*!
 * \file
 * \brief Définition de la classe BaseTest.
 */

#ifndef TEST_BASE_TEST_HPP
#define	TEST_BASE_TEST_HPP

#include "UnitTest.hpp"

namespace test
{
    /*!
     * \brief Teste la classe \ref pmx::Base.
     */
    class BaseTest : public utils::UnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref BaseTest.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::BaseTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur par défaut.
         */
        BaseTest() : utils::UnitTest("BaseTest")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~BaseTest()
        {
        }

        /*!
         * \brief Teste la propriété \ref pmx::Base::vecteurCorrectionEnabled.
         */
        void testVecteurCorrectionEnabled();

        /*!
         * \brief Teste la propriété \ref pmx::Base::pidPositionEnabled.
         */
        void testPidPositionEnabled();

        /*!
         * \brief Teste la propriété \ref pmx::Base::pidSpeedEnabled.
         */
        void testPidSpeedEnabled();

        /*!
         * \brief Teste le calcul du vecteur destination.
         */
        void testComputeDestionationVector();

        /*!
         * \brief Teste le calcul de l'angle destination.
         */
        void testComputeAngleToGo();

        /*!
         * \brief Execute les tests associés à la classe \ref BaseTest.
         */
        virtual void suite();
    };
}

#endif
