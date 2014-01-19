/*!
 * \file
 * \brief Définition de la classe ARobotElementTest.
 */

#ifndef TEST_AROBOTELEMENTTEST_HPP
#define TEST_AROBOTELEMENTTEST_HPP

#include "UnitTest.hpp"

namespace test
{

    /*!
     * \brief Teste la classe \ref pmx::ARobotElement.
     */
    class ARobotElementTest : public utils::UnitTest
    {
    public:

        /*!
         * Constructeur de la classe.
         */
        ARobotElementTest() : utils::UnitTest("ARobotElementTest")
        {
        }

        /*!
         * Destructeur de la classe.
         */
        virtual ~ARobotElementTest()
        {
        }

        virtual void suite();

        /*!
         * \brief Teste le getter/setter \ref ARobotElement::robot().
         */
        virtual void testRobot();
    };
}

#endif
