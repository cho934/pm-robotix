/*!
 * \file
 * \brief Définition de la classe ServoMotorsTest.
 */

#ifndef TEST_SERVOMOTORSTEST_HPP
#define	TEST_SERVOMOTORSTEST_HPP


#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Test des differentes positions des leviers.
     */
    class ServoMotorsTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \return Trace associé à la classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ServoMotorsTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ServoMotorsTest() : pmx::RobotTest("Tests des differentes positions des servomoteurs.")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ ServoMotorsTest()
        {}
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
        
    };
};

#endif
