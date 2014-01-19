/*!
 * \file
 * \brief Définition de la classe ServoAdjustmentTest.
 */

#ifndef TEST_SERVOADJUSTMENTTEST_HPP
#define	TEST_SERVOADJUSTMENTTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace test
{
    /*!
     * \brief Test pour utiliser la pince.
     */
    class ServoAdjustmentTest : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ServoAdjustmentTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ServoAdjustmentTest");
            return instance;
        }
    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ServoAdjustmentTest() : pmx::RobotTest("ServoAdjustmentTest : ajuster un servomoteur (offset + position).")
        {}

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ ServoAdjustmentTest()
        {}

        /*!
         * Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif	/* TEST_SERVOADJUSTMENTTEST_HPP */

