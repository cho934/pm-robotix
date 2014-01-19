/*!
 * \file
 * \brief Implémentation de la classe LoggerFactory.
 */

#include "LoggerFactory.hpp"

utils::LoggerFactory::LoggerFactory()
: appenders_(), loggers_(), rootLogger_()
{
    lock=new Mutex();
    initialize();
    
    if(rootLogger() == NULL)
    {
        //! \todo Must throw an exception
    }
}

utils::LoggerFactory::~LoggerFactory()
{
    lock->lock();
    std::map < std::string, utils::Logger * >::iterator i1 = loggers_.begin();
    for (; i1 != loggers_.end(); i1++)
    {
        delete i1->second;
        i1->second = NULL;
    }
    std::map < std::string, utils::Appender * >::iterator i2 = appenders_.begin();
    for (; i2 != appenders_.end(); i2++)
    {
        delete i2->second;
        i2->second = NULL;
    }
    lock->unlock();
    delete lock;
}

const utils::Logger &
utils::LoggerFactory::logger(const std::string & name)
{
    
    LoggerFactory & instance = utils::LoggerFactory::instance();
   // instance.lock();
    std::map < std::string, utils::Logger * >::iterator value = instance.loggers_.find(name);
    if (value == instance.loggers_.end())
    {
        Logger * logger = new Logger(* instance.rootLogger(), name);
        instance.add(logger);
     //   instance.unlock();
        return * logger;
    }
   // instance.unlock();
    return *(value->second);
}

utils::Appender *
utils::LoggerFactory::appender(const std::string & name)
{
  // lock->lock();
    std::map < std::string, utils::Appender * >::iterator value = this->appenders_.find(name);
    if (value == this->appenders_.end())
    {
 //      lock->unlock();
        return NULL;
    }
    else
    {
     //   lock->unlock();
        return value->second;
    }
}

void
utils::LoggerFactory::add(Logger * logger)
{
//  lock->lock();
    if (logger->name() == "")
    {
       // lock->lock();
        this->rootLogger_ = logger;
       // lock->unlock();
    }
    else
    {
        loggers_.insert(std::make_pair(logger->name(), logger));
    }
   // lock->unlock();
}

void
utils::LoggerFactory::add(const std::string & name, utils::Appender * appender)
{
//   lock->lock();
    appenders_.insert(std::make_pair(name, appender));
  // lock->unlock();
}

void
utils::LoggerFactory::add(const Level & level, const std::string & loggerName, const std::string & appenderName)
{
  
    Appender * appender = this->appender(appenderName);
    if (appender == NULL)
    {
        //! \todo Must throw an exception
    }
    else
    {
       Logger *log= new Logger(level, loggerName, * appender);
        this->add(log);
    }
 
}
