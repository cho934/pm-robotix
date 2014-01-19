/*!
 * \file
 * \brief Définition de la classe TestM2.
 */

#ifndef TESTM2_HPP
#define TESTM2_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Test de toutes les pin des multiplexeurs / démultiplexeurs.
     */
    class MultiDemultiAllPinsTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \return Trace associé à la classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::MultiDemultiAllPinsTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        MultiDemultiAllPinsTest() : pmx::RobotTest("Test de toutes les pin des multiplexeurs / démultiplexeurs")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ MultiDemultiAllPinsTest()
        {}
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
