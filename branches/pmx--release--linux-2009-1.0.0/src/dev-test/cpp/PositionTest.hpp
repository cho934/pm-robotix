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
     * \brief Tests unitaires de la classe pmx::Position.
     */
    class PositionTest : public utils::UnitTest
    {
    private:
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
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
        PositionTest(): utils::UnitTest("PositionTest")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ PositionTest()
        {}
        
        /*!
         * \brief Test du constructeur de la classe pmx::Position et de ses accesseurs.
         */
        void testPosition();
        
        /*!
         * \brief Test de la méthode rotate().
         */
        void testRotate();
        
        /*!
         * \brief Exécution des tests.
         */
        inline virtual void suite()
        {
            testPosition();
            testRotate();
        }
    };
}

#endif
