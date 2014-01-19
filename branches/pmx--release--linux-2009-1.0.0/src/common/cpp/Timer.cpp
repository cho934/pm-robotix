/*!
 * \file
 * \brief Implémentation de la classe Timer.
 */

#include "Timer.hpp"
#include "Chronometer.hpp"

utils::Timer::Timer(int timeSpan, utils::ITimerListener* listener) : timeSpan_(timeSpan), listener_(listener), stop_(false)
{
}

void
utils::Timer::execute()
{
    logger().debug() << "utils::Timer::execute() : start" << utils::end;
    
    while(! stop_)
    {
        startTime_ = Chronometer::getTime();
        //timeSpan : ms
        //timeval ulong tv_sec : s
        //timeval long  tv_usec : us

        timeval now = Chronometer::getTime();

        //soustraction sur les sec
        int ecartSec = now.tv_sec - startTime_.tv_sec;
        //soustration des micro sec
        int ecartUsec = now.tv_usec - startTime_.tv_usec;
        //ecart global
        int ecart = ecartSec * 1000000 + ecartUsec; //en micro sec
        
        //logger().debug() << "utils::Timer::execute() : ecart global en us : " << ecart << utils::end;
        
        //boucle d'attente
        while(!stop_ && ecart < timeSpan_ * 1000)
        {
            this->yield();
            now = Chronometer::getTime();
            ecartSec = now.tv_sec - startTime_.tv_sec;
            ecartUsec = now.tv_usec - startTime_.tv_usec;
            ecart = ecartSec * 1000000 + ecartUsec; //en micro sec
        }

        if(!stop_)
        {
            logger().debug() << "utils::Timer::runTask() : ecart : " << ecart << utils::end;
            this->runTask();
        }
    }
}

void
utils::Timer::runTask()
{
    logger().debug() << "utils::Timer::runTask()" << utils::end;
    
    this->listener_->onTimer(this->timeSpan_);
}
