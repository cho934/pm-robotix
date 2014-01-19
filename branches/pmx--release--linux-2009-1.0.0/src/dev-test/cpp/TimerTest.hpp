/*!
 * \file
 * \brief Définition de la classe TimerTest.
 */
#ifndef TEST_TIMER_TEST_HPP
#define	TEST_TIMER_TEST_HPP

#include "UnitTest.hpp"
#include "Chronometer.hpp"

namespace test
{
    class TimerTest: public utils::UnitTest
    {
    private:
        /**
         * \brief Cette m??thode retourne le logger associ?? ?? cette classe.
         * \return Le logger de cette classe.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::TimerTest");
            return instance;
        }
    public:
        
        TimerTest(): utils::UnitTest("TimerTest")
        {}
        
        virtual ~ TimerTest()
        {}
        
        void testWithClock();
        
        void testWithGettimeofday();
        
        void testTimer();
        
        void testTimerTickMin();
        
        void testTimerMiPeriodCount();
        
        virtual void suite();
    };
}

#endif

