/*!
 * \file
 * \brief Définition de la classe FlashBallWheelTest.
 */

#ifndef TEST_FLASHBALLWHEELTEST_HPP
#define	TEST_FLASHBALLWHEELTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test de tir de balle de ping pong.
     */
    class FlashBallWheelTest : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref FlashBallWheelTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::FlashBallWheelTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        FlashBallWheelTest() : pmx::RobotTest("FlashBallWheelTest : tir de balle")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~FlashBallWheelTest()
        {
        }

        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
