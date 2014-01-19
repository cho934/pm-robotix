/*!
 * \file
 * \brief Implémentation de la classe Thread.
 */

#include <iostream>
#include "Thread.hpp"
#include <sys/types.h>
#include <sys/syscall.h>

#ifndef EAGAIN
#define EAGAIN 11
#endif

#ifndef EINVAL
#define EINVAL 22
#endif


void *
utils::Thread::entryPoint(void *pthis)
{
    utils::Thread * pt = (utils::Thread *) pthis;
    
    pt->execute();
    pt->state_ = utils::STOPPED;

    return NULL;
}

utils::Thread::Thread() : threadId_(), state_(utils::CREATED)
{}
/*!
 * \brief rend la main. Cette fonction ne doit pas être utilisée.
 * \deprecated
 */
void
utils::Thread::yield()
{
    sched_yield(); //pthread_yield(); !!!!!!!!!!!!!!!!!!!!!!!!!!!!! pour arm-linux-g++
}

/*!
 * \brief Start thread
 * return false si aucun pb.
 */
bool
utils::Thread::start()
{
    printf("    utils::Thread::start()\n");
    this->state_ = utils::STARTING;
   
    int code = pthread_create(&threadId_, NULL, utils::Thread::entryPoint, (void *) this);

    this->state_ = utils::STARTED;

    if (code == 0)
    {
        pid_t tid;
        tid = syscall(SYS_gettid);
        std::cout << "Thread::started:" << &threadId_ << " : " << tid << std::endl;
        return false;
    }else
    {
        std::cout << "Thread::pthread_create: NOK \n" << std::endl;
        switch(code)
        {
            case EAGAIN :
            // The  system lacked the necessary resources to create another
            // thread, or the system-imposed limit on the total number of
            // threads in a process {PTHREAD_THREADS_MAX} would be exceeded.
                std::cout << "Thread::ERROR:EAGAIN \n" << std::endl;
            break;

            case EINVAL :
            // The value specified by attr is invalid.
                std::cout << "Thread::ERROR:EINVAL \n" << std::endl;
            break;
/*
            case EPERM :
            // The caller does not have appropriate permission to set the
            // required scheduling parameters or scheduling policy.
                std::cout << "Thread::ERROR:EAGAIN \n" << &threadId_ << std::endl;
            break;*/

            default:
                std::cout << "Thread::ERROR:default \n"  << std::endl;
        }
        return true;
    }
}
