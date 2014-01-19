/*!
 * \file
 * \brief Définition de la classe ColumnElementLeverTest.
 */

#ifndef TEST_COLUMNELEMENTLEVERTEST_HPP
#define	TEST_COLUMNELEMENTLEVERTEST_HPP


#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Test des differentes positions des leviers.
     */
    class ColumnElementLeverTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \return Trace associé à la classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ColumnElementLeverTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ColumnElementLeverTest() : pmx::RobotTest("Tests des differentes positions des leviers")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ ColumnElementLeverTest()
        {}
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
        
    };
};

#endif
