/*!
 * \file
 * \brief Définition de la classe ChronometerTest.
 */

#ifndef TEST_CHRONOMETER_TEST_HPP
#define	TEST_CHRONOMETER_TEST_HPP

#include "DevUnitTest.hpp"
#include "../../common/cpp/Chronometer.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Teste la classe \ref utils::Chronometer.
     */
    class ChronometerTest : public utils::DevUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ChronometerTest.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ChronometerTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur par défaut.
         */
        ChronometerTest() : utils::DevUnitTest("ChronometerTest")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ChronometerTest()
        {
        }

        void testWithClock();

        void testWithGettimeofday();

        void testTimer();

        void testTimerTickMin();

        void testTimerMiPeriodCount();

        void testTimerCheck();

        void testTimerNanosleep();

        virtual void suite();
    };
}

#endif

