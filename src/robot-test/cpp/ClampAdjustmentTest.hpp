/*!
 * \file
 * \brief Définition de la classe ClampAdjustmentTest.
 */
#ifndef TEST_CLAMPADJUSTMENTTEST_HPP
#define	TEST_CLAMPADJUSTMENTTEST_HPP


#include "RobotTest.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace test
{
    /*!
     * \brief Test pour utiliser la pince.
     */
    class ClampAdjustmentTest : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ClampAdjustmentTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ClampAdjustmentTest");
            return instance;
        }
    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ClampAdjustmentTest() : pmx::RobotTest("ClampAdjustmentTest : ajuster un servomoteur (bras) de la pince (offset + position).")
        {}

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ ClampAdjustmentTest()
        {}

        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif	/* _CLAMPADJUSTMENTTEST_HPP */

