/*!
 * \file
 * \brief Implémentation de la classe Logger.
 */

#include "Logger.hpp"

utils::Logger::Logger(const utils::Level & level, const std::string & name, utils::Appender & appender)
: level_(level), name_(name), appender_(appender)
{
}

utils::Logger::Logger(const utils::Logger & parent, const std::string & name)
: level_(parent.level_), name_(name), appender_(parent.appender_)
{
}

void
utils::Logger::writeMessage(const utils::Level & level, const std::string & message) const
{
    if (isActive(level))
    {
        appender_.writeMessage(*this, level, message);
    }
}

utils::Logger::LoggerBuffer::LoggerBuffer(const utils::Logger & logger, const utils::Level & level)
: logger_(logger), level_(level)
{
    if (logger.isActive(level))
    {
        stream_ = new std::ostringstream();
    }
    else
    {
        stream_ = NULL;
    }
}

utils::Logger::LoggerBuffer::~LoggerBuffer()
{
    if (stream_ != NULL)
    {
        delete stream_;
        stream_ = NULL;
    }
}

void
utils::end(utils::Logger::LoggerBuffer& buffer)
{
    buffer.end();
}
