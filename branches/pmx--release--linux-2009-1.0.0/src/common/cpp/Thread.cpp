/*!
 * \file
 * \brief Implémentation de la classe Thread.
 */

#include "Thread.hpp"
#include "LoggerFactory.hpp"

void *
utils::Thread::entryPoint(void *pthis)
{
    utils::Thread * pt = (utils::Thread *) pthis;
    
    /*
     * if (utils::LoggerFactory::logger("utils::Thread").isActive(utils::Level::DEBUG))
     * {
     * pthread_attr_t attr;
     * sched_param param;
     * pthread_getattr_np(pt->threadId_, &attr);
     * pthread_attr_getschedparam(&attr, &param);
     * utils::LoggerFactory::logger("utils::Thread").debug() << "utils::Thread::start() [priority:" << param.__sched_priority << "]" << utils::end;
     * pthread_attr_destroy(&attr);
     * }
     */
    
    pt->execute();
    pt->finished_ = true;
    
    return NULL;
}

utils::Thread::Thread() : threadId_(), finished_(false)
{}

void
utils::Thread::yield()
{
    pthread_yield();
}

/*!
 * \todo Use code to throw exceptions.
 */
void
utils::Thread::start()
{
    int code = pthread_create(&threadId_, NULL, utils::Thread::entryPoint, (void *) this);
    
    if (code == 0)
    {
        return;
    }
    /*
     * switch(code)
     * {
     * case EAGAIN :
     * // The  system lacked the necessary resources to create another
     * // thread, or the system-imposed limit on the total number of
     * // threads in a process {PTHREAD_THREADS_MAX} would be exceeded.
     * break;
     *
     * case EINVAL :
     * // The value specified by attr is invalid.
     * break;
     *
     * case EPERM :
     * // The caller does not have appropriate permission to set the
     * // required scheduling parameters or scheduling policy.
     * break;
     *
     * default:
     * }
     */
}
