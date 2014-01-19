#include "Mutex.hpp"
#include "LoggerFactory.hpp"

utils::Mutex::Mutex()
{
    pthread_mutex_init(& mutex_, NULL);
}

void utils::Mutex::lock()
{
    utils::LoggerFactory::logger("utils::Mutex").debug() << "mutex lock " << mutex_.__align << utils::end;
    /// \todo Lever une exception en cas d'erreur
    int value = pthread_mutex_lock(& mutex_);
    if (value != 0)
    {
        utils::LoggerFactory::logger("utils::Mutex").error() << "mutex error " << value << utils::end;
    }
}

void utils::Mutex::unlock()
{
    utils::LoggerFactory::logger("utils::Mutex").debug() << "mutex unlock " << mutex_.__align << utils::end;
    /// \todo Lever une exception en cas d'erreur
    int value = pthread_mutex_unlock(& mutex_);
    if (value != 0)
    {
        utils::LoggerFactory::logger("utils::Mutex").error() << "mutex error " << value << utils::end;
    }
}

bool utils::Mutex::tryLock()
{
    int value = pthread_mutex_trylock(& mutex_);
    return value == 0;
}
