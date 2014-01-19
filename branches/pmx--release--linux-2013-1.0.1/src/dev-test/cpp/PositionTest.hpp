/*!
 * \file
 * \brief Définition de la classe PositionTest.
 */

#ifndef TEST_POSITIONTEST_H
#define	TEST_POSITIONTEST_H

#include "UnitTest.hpp"
#include "Position.hpp"

namespace test
{
    /*!
     * \brief Teste la classe \ref pmx::Position.
     */
    class PositionTest : public utils::UnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref PositionTest.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::PositionTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur par défaut.
         */
        PositionTest() : utils::UnitTest("PositionTest")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~PositionTest()
        {
        }

        /*!
         * \brief Test du constructeur de la classe \ref pmx::Position et de ses accesseurs.
         */
        void testPosition();

        /*!
         * \brief Test de la méthode \ref pmx::Position::rotate().
         */
        void testRotate();

        /*!
         * \brief Exécution des tests.
         */
        inline virtual void suite()
        {
            logger().info() << "Go" << utils::end;
            testPosition();
            testRotate();
        }
    };
}

#endif
