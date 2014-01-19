/*!
 * \file
 * \brief Définition de la classe CylinderTest.
 */

#ifndef TEST_CONTACTTEST_HPP
#define	TEST_CONTACTTEST_HPP


#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Test des contacts.
     */
    class ContactTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \return Trace associé à la classe.
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
        ContactTest() : pmx::RobotTest("Tests des contacts")
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
