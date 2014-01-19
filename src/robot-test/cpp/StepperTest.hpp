/*!
 * \file
 * \brief Définition de la classe StepperTest.
 */

#ifndef TEST_STEPPERTEST_HPP
#define	TEST_STEPPERTEST_HPP


#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Test d'un moteur pas à pas.
     */
    class StepperTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \return Trace associé à la classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::StepperTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        StepperTest() : pmx::RobotTest("Test d'un moteur pas à pas")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ StepperTest()
        {}
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
