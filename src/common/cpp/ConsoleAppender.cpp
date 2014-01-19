#include "ConsoleAppender.hpp"

void
utils::ConsoleAppender::flush()
{
    for (std::list<std::string>::iterator it = messages_.begin(); it != messages_.end(); it++)
    {
        (*this->out_) << *it << std::endl;
    }
}

void
utils::ConsoleAppender::execute()
{
    while (true)
    {
        this->printData();
        usleep(15000);
    }
}

void
utils::ConsoleAppender::printData()
{
    while (this->messages().size() > 0)
    {
        std::string message = this->messages().front();
        (*this->out_) << message << std::endl;
        this->messages_.pop_front();
    }
}
