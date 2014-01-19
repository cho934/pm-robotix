/*!
 * \file
 * \brief Définition de la classe ContactTest.
 */

#ifndef TEST_CONTACTTEST_HPP
#define	TEST_CONTACTTEST_HPP


#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Test des contacts du robot.
     */
    class ContactTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ContactTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ContactTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ContactTest() : pmx::RobotTest("RobotIN : ContactTest : Tests des contacts")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ ContactTest()
        {}
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
        
    };
};

#endif
