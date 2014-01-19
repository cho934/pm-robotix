/*!
 * \file
 * \brief Implémentation de la classe Timer.
 */

#include "Timer.hpp"
#include "Chronometer.hpp"
#include <iostream>

utils::Timer::Timer(int timeSpan, utils::ITimerListener* listener) : timeSpan_(timeSpan), listener_(listener), stop_(false)
{
}

void
utils::Timer::execute()
{
    int tps;
    //logger().debug() << "utils::Timer::execute() : start : TimeSpan :" << timeSpan_ << utils::end;
    chrono_.start();
    while (!stop_)
    {
        //pause jusqu'à la prochaine execution en us
        tps = (timeSpan_ * 1000) - chrono_.getElapsedTimeInMicroSec();
        //logger().debug() << "tps à attendre :" << tps << utils::end;
        if (tps < 0)
        {
            std::cout << "Timer:Temps du runTask dépassé (> à timeSpan:" << timeSpan_ << ") tps:" << tps << " chrono:" << chrono_.getElapsedTimeInMicroSec()<< std::endl;
            logger().debug() << "Timer:Temps du runTask dépassé (> à timeSpan:" << timeSpan_ << ") tps:" << tps << " chrono:" << chrono_.getElapsedTimeInMicroSec()<< utils::end;
            //!\todo créer une alerte LedIndicator
        }else
        {
            usleep(tps);
        }

        if (!stop_)
        {
            //logger().debug() << "utils::Timer::runTask() :" << chrono_.getElapsedTimeInMicroSec() << utils::end;
            this->runTask(chrono_);
        }
        
        chrono_.start();//reset du chrono
    }
    chrono_.stop();
}

void
utils::Timer::runTask(Chronometer chrono)
{
    //logger().debug() << "utils::Timer::runTask()" << utils::end;
    this->listener_->onTimer(chrono);
}
