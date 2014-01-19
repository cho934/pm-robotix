/*!
 * \file
 * \brief Implémentation de la classe ConsoleAppender.
 */

#include "ConsoleAppender.hpp"
#include <iostream>
#include <sys/types.h>
#include <sys/syscall.h>
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
    debugThread("ConsoleAppender");
    
    

    while (true)
    {
        this->printData();
        usleep(100000);
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
