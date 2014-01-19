/*!
 * \file
 * \brief Définition de la classe InPinsTest.
 */

#ifndef TEST_INPINSTEST_HPP
#define TEST_INTPINSTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Affiche l'etat d'un pin du multiplexage.
     */
    class InPinsTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref InPinsTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::InPinsTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        InPinsTest() : pmx::RobotTest("RobotIN : InPinsTest : Test du getValue via le multiplexage")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ InPinsTest()
        {}
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);

    };
};

#endif
