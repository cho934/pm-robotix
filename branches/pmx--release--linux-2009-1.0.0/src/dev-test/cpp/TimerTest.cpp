/*!
 * \file
 * \brief Implémentation de la classe TimerTest.
 */

#include "TimerTest.hpp"
#include <sstream>
#include <iostream>
#include <sys/time.h>

using namespace test;

//todo suppression de l'affichage ostringstream....en attente du flush des memorylogger de FK...
std::ostringstream strout;

void
test::TimerTest::suite()
{
    testWithClock();
    testWithGettimeofday();
    testTimer();
    testTimerTickMin();
    testTimerMiPeriodCount();
    //affichage
    //std::cout << strout.str() << std::endl;
}

/*!
 * \brief Test des temps avec la m?thode Clock(): donne le minimum de r?solution
 */
void
test::TimerTest::testWithClock()
{
    logger().info() << ":testWithClock: Resolution minimum avec Clock():" << utils::end;
    
    clock_t t1, t2;
    t1 = t2 = clock();
    
    // loop until t2 gets a different value
    while(t1 == t2)
    {
        t2 = clock();
    }
    
    // print resolution of clock()
    logger().info() << (double)(t2 - t1) / CLOCKS_PER_SEC * 1000 << " ms." << utils::end;
    
    logger().info() << "CLOCKS_PER_SEC: " << CLOCKS_PER_SEC << utils::end;
    logger().info() << "CLOCK() : " << clock() << utils::end;
}

/*!
 * \brief test des temps avec la m?thode Gettimeofday().
 */
void
test::TimerTest::testWithGettimeofday()
{
    logger().info() << ":testWithGettimeofday: Resolution minimum avec gettimeofday():" << utils::end;
    
    timeval t1, t2;
    double elapsedTime;
    
    // start timer
    gettimeofday(&t1, NULL);
    
    // do something
    
    // stop timer
    gettimeofday(&t2, NULL);
    
    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    logger().info() << elapsedTime << " ms." << utils::end;;
}

/*!
 * \brief test de la classe Timer.
 */
void
test::TimerTest::testTimer()
{
    logger().info() << ":testTimer: utilisation des fonctions start,stop,get." << utils::end;
    
    utils::Chronometer timer;
    
    // start timer
    timer.start();
    
    // do something
    logger().info() << "test" << utils::end;
    
    // stop timer
    timer.stop();
    
    // print the elapsed time
    logger().info() << timer.getElapsedTimeInSec() << " s." << utils::end;
    logger().info() << timer.getElapsedTimeInMilliSec() << " ms." << utils::end;
    logger().info() << timer.getElapsedTimeInMicroSec() << " us." << utils::end;
}

/*!
 * \brief affiche le temps minimum (tick) pendant 1ms.
 */
void
test::TimerTest::testTimerTickMin()
{
    std::cout.sync_with_stdio (false);
    logger().info() << ":testTimerTickMin: Ticks pendant 1 milliseconde avec strout." << utils::end;
    strout << "\n::testTimerTickMin: Ticks pendant 1 milliseconde.\n"<< std::ends;
    
    utils::Chronometer timer;
    
    timer.start();
    
    double tick1 = timer.getElapsedTimeInMilliSec();
    double tick2 = tick1;

    while(timer.getElapsedTimeInMilliSec() < 1)       // boucle sur 1 ms
    {
        strout << (tick2 - tick1) << "ms." << std::ends;
        tick1 = tick2;
        tick2 = timer.getElapsedTimeInMilliSec();
    }
    
}

/*!
 * \brief affiche le temps minimum, maximum, moyenne de l'ensemble des demi-p?riodes generees
 */
void
test::TimerTest::testTimerMiPeriodCount()
{
    std::cout.sync_with_stdio(false);
    logger().info() << ":testTimerMiPeriodCount: Min,Max,Moy de la periode generee avec strout." << utils::end;
    strout << "\n\n:testTimerMiPeriodCount: Min,Max,Moy de la periode generee."<< std::ends;
    int tempsTotalEnMilliSec = 1000;
    int tempsMiPeriodeEnMicroSec = 1000;
    
    utils::Chronometer timer;
    utils::Chronometer timerTotal;
    bool value = false;
    int i = 0;
    long max = 0;
    long min = tempsMiPeriodeEnMicroSec * 10;
    long sommetot = 0;
    
    timerTotal.start();
    while(timerTotal.getElapsedTimeInMilliSec() <= tempsTotalEnMilliSec)       
    {
        timer.start();
        while(timer.getElapsedTimeInMicroSec() <= tempsMiPeriodeEnMicroSec) {}      
       
        if (value == true)
        {
            value = false;
        }
        else
        {
            value = true;
        }
        long miperiode = timer.getElapsedTimeInMicroSec();
        //strout << value << ":" << miperiode << " " << std::ends;
        if (miperiode > max)
        {
            max = miperiode;
        }else if (miperiode < min && miperiode != 0)
        {
            min = miperiode;
        }
        sommetot += miperiode;
        i++;
        timer.stop();  
    } 
    long tot = timerTotal.getElapsedTimeInMicroSec();
    timerTotal.stop();
    
    //calcul de la moyenne
    long moy = tot / i;
    
    // print the elapsed time in millisec
    strout << "\ntimerTotal:" << tot << " us.\n" << std::ends;
    strout << "sommetot  :" << sommetot << " \n" << std::ends;
    strout << "Nb        :" << i << " \n" << std::ends;
    strout << "Max       :" << max << " \n" << std::ends;
    strout << "Min       :" << min << " \n" << std::ends;
    strout << "moytimer  :" << moy << " \n" << std::ends;   
    strout << "moysomme  :" << sommetot / i << " \n" << std::ends;   
}


