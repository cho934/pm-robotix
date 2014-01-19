/*!
 * \file
 * \brief Implémentation de la classe ChronometerTest.
 * \todo test sur APF : a deplacer dans robot-test
 */

#include <sstream>
#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include "ChronometerTest.hpp"

extern "C"
{

    //refer to http://cc.byexamples.com/2007/05/25/nanosleep-is-better-than-sleep-and-usleep/
    void sigfunc(int)
    {

    }

    int __nsleep(const struct timespec *req, struct timespec *rem)
    {
        struct timespec temp_rem;
        if (nanosleep(req, rem) == -1)
        {
            __nsleep(rem, &temp_rem);
            return 0;
        }
        else
            return 1;
    }

    int msleep2(unsigned long milisec)
    {
        struct timespec req = {0,0}, rem = {0,0};
        time_t sec = (int) (milisec / 1000);
        milisec = milisec - (sec * 1000);
        req.tv_sec = sec;
        req.tv_nsec = milisec * 1000000L;
        __nsleep(&req, &rem);
        return 1;
    }

    int msleep(unsigned long milisec)
    {
        struct timespec req = {0,0};
        time_t sec = (int) (milisec / 1000);
        milisec = milisec - (sec * 1000);
        req.tv_sec = sec;
        req.tv_nsec = milisec * 1000000L;
        while (nanosleep(&req, &req) == -1)
            continue;
        return 1;
    }

    int _usleep(unsigned long microsec)
    {
        struct timespec req = {0,0};
        time_t sec = (int) (microsec / 1000000);
        microsec = microsec - (sec * 1000000);
        req.tv_sec = sec;
        req.tv_nsec = microsec * 1000L;
        while (nanosleep(&req, &req) == -1)
            continue;
        return 1;
    }

}


using namespace test;

void
test::ChronometerTest::suite()
{
    testWithClock();
    testWithGettimeofday();
    testTimer();
    testTimerTickMin();
    testTimerMiPeriodCount();
    testTimerCheck();
    testTimerNanosleep();

}

void
test::ChronometerTest::testTimerNanosleep()
{
    //recupere la resolution de la clock
    struct timespec res;

    if ( clock_getres( CLOCK_REALTIME, &res) == -1 ) {
      //perror( "clock get resolution" );
      logger().error() << "clock get resolution" << utils::end;
    }
    //printf( "\n",res.tv_nsec / 1000 );
    logger().info() << "clock_getres() : Resolution minimum is " << res.tv_nsec / 1000 << " micro seconds." << utils::end;


    logger().info() << ":testTimerNanosleep : Comparaision d'attente avec nanosleep/usleep" << utils::end;


    struct sigaction sa; //todo warning a corriger
    sa.sa_handler = &sigfunc;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;

    sigaction(SIGINT, &sa, NULL);

    utils::Chronometer chrono;
    chrono.start();
    _usleep(1000);
    chrono.stop();
    logger().info() << "Wait 1 ms with nanosleep() : " << chrono.getElapsedTimeInMicroSec() << utils::end;

    chrono.start();//reset
    _usleep(10000);
    chrono.stop();
    logger().info() << "Wait 10 ms with nanosleep() : " << chrono.getElapsedTimeInMicroSec() << utils::end;

    chrono.start();//reset
    _usleep(75000);
    chrono.stop();
    logger().info() << "Wait 75 ms with nanosleep() : " << chrono.getElapsedTimeInMicroSec() << utils::end;

    chrono.start();//reset
    _usleep(300000);
    chrono.stop();
    logger().info() << "Wait 300 ms with nanosleep() : " << chrono.getElapsedTimeInMicroSec() << utils::end;

    chrono.start();//reset
    usleep(1000);
    chrono.stop();
    logger().info() << "usleep(1000) : " << chrono.getElapsedTimeInMicroSec() << utils::end;

    chrono.start();//reset
    usleep(10000);
    chrono.stop();
    logger().info() << "usleep(10000) : " << chrono.getElapsedTimeInMicroSec() << utils::end;

    chrono.start();//reset
    usleep(75000);
    chrono.stop();
    logger().info() << "usleep(75000) : " << chrono.getElapsedTimeInMicroSec() << utils::end;

    chrono.start();//reset
    usleep(300000);
    chrono.stop();
    logger().info() << "usleep(300000) : " << chrono.getElapsedTimeInMicroSec() << utils::end;

    logger().info() << "Conclusion : nanosleep n'est pas plus précis. Le parametre High Res Timer doit etre activé à la compilation du noyau." << utils::end;

    //todo : test clock_nanosleep et setitimer à faire

}

void
test::ChronometerTest::testTimerCheck()
{
    logger().info() << ":testTimerCheck : Attente de 1ms par wait system (while)" << utils::end;

    
    utils::Chronometer chrono;
    chrono.setTimer(1000);
    
    //Test avec boucle while
    while(1)
    {
        if(chrono.checkTimer() == 1)
        {
            logger().info() << "endtime:" << chrono.getElapsedTimeInMicroSec() << utils::end;
            break;
        }
    }
    logger().info() << "end" << utils::end;
}

/*!
 * \brief Test des temps avec la methode Clock(): donne le minimum de resolution
 */
void
test::ChronometerTest::testWithClock()
{
    logger().info() << ":testWithClock: Resolution minimum avec Clock():" << utils::end;

    clock_t t1, t2;
    t1 = t2 = clock();

    // loop until t2 gets a different value
    while (t1 == t2)
    {
        t2 = clock();
    }

    // print resolution of clock()
    logger().info() << (double) (t2 - t1) / CLOCKS_PER_SEC * 1000 << " ms." << utils::end;

    logger().info() << "CLOCKS_PER_SEC: " << CLOCKS_PER_SEC << utils::end;
    logger().info() << "CLOCK() : " << clock() << utils::end;
}

/*!
 * \brief test des temps avec la methode Gettimeofday().
 */
void
test::ChronometerTest::testWithGettimeofday()
{
    logger().info() << ":testWithGettimeofday: Resolution minimum avec gettimeofday():" << utils::end;

    timeval t1, t2;
    double elapsedTime;

    // start timer
    gettimeofday(&t1, NULL);

    // do nothing

    // stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
    logger().info() << elapsedTime << " ms." << utils::end;

    logger().info() << ":testWithGettimeofday: Resolution 1000us avec gettimeofday():" << utils::end;
    gettimeofday(&t1, NULL);
    gettimeofday(&t2, NULL);
    while ((t2.tv_sec * 1000000 + t2.tv_usec) < t1.tv_sec * 1000000 + t1.tv_usec + 1000)
    {
        gettimeofday(&t2, NULL);
    }

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
    logger().info() << elapsedTime << " ms." << utils::end;
}

/*!
 * \brief test de la classe Chronometer.
 */
void
test::ChronometerTest::testTimer()
{
    logger().info() << ":testTimer: utilisation des fonctions start,stop,get." << utils::end;

    utils::Chronometer chrono;
    logger().info() << "Wait 1000us with usleep()" << utils::end;
    // start timer
    chrono.start();
    // do something  
    usleep(1000);
    // stop timer
    chrono.stop();
    // print the elapsed time
    logger().info() << chrono.getElapsedTimeInSec() << " s." << utils::end;
    logger().info() << chrono.getElapsedTimeInMilliSec() << " ms." << utils::end;
    logger().info() << chrono.getElapsedTimeInMicroSec() << " us." << utils::end;

    logger().info() << "Wait 10000us with usleep()" << utils::end;
    chrono.start();
    usleep(10000);
    chrono.stop();
    logger().info() << chrono.getElapsedTimeInSec() << " s." << utils::end;
    logger().info() << chrono.getElapsedTimeInMilliSec() << " ms." << utils::end;
    logger().info() << chrono.getElapsedTimeInMicroSec() << " us." << utils::end;

    logger().info() << "Wait 75000us with usleep()" << utils::end;
    chrono.start();
    usleep(75000);
    chrono.stop();
    logger().info() << chrono.getElapsedTimeInSec() << " s." << utils::end;
    logger().info() << chrono.getElapsedTimeInMilliSec() << " ms." << utils::end;
    logger().info() << chrono.getElapsedTimeInMicroSec() << " us." << utils::end;


}

/*!
 * \brief affiche le temps minimum (tick) pendant 1ms.
 */
void
test::ChronometerTest::testTimerTickMin()
{
    //std::cout.sync_with_stdio (false);
    logger().info() << ":testTimerTickMin: Ticks pendant 1 milliseconde " << utils::end;

    utils::Chronometer timer;

    timer.start();

    double tick1 = timer.getElapsedTimeInMilliSec();
    double tick2 = tick1;

    while (timer.getElapsedTimeInMilliSec() < 1) // boucle sur 1 ms
    {
        logger().info() << (tick2 - tick1) << "ms." << utils::end;
        tick1 = tick2;
        tick2 = timer.getElapsedTimeInMilliSec();
    }

}

/*!
 * \brief affiche le temps minimum, maximum, moyenne de l'ensemble des demi-periodes generees
 */
void
test::ChronometerTest::testTimerMiPeriodCount()
{
    //std::cout.sync_with_stdio(false);
    logger().info() << ":testTimerMiPeriodCount: Min,Max,Moy de la periode generee " << utils::end;
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
    while (timerTotal.getElapsedTimeInMilliSec() <= tempsTotalEnMilliSec)
    {
        timer.start();
        while (timer.getElapsedTimeInMicroSec() <= tempsMiPeriodeEnMicroSec)
        {
        }

        if (value == true)
        {
            value = false;
        }else
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
    logger().info() << "\ntimerTotal:" << tot << " us." << utils::end;
    logger().info() << "sommetot  :" << sommetot << utils::end;
    logger().info() << "Nb        :" << i << utils::end;
    logger().info() << "Max       :" << max << utils::end;
    logger().info() << "Min       :" << min << utils::end;
    logger().info() << "moytimer  :" << moy << utils::end;
    logger().info() << "moysomme  :" << sommetot / i << utils::end;

}


