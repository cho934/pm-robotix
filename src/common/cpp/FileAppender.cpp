#include "FileAppender.hpp"
#include <iostream>

utils::FileAppender::~FileAppender()
{
    ofs_.close();
}

void
utils::FileAppender::flush()
{
    while (this->messages().size() > 0)
    {
        std::string message = this->messages().front();
        ofs_ << message << std::endl;
        this->messages_.pop_front();
    }

    /* //log
    for (std::list<std::string>::iterator it = messages_.begin(); it != messages_.end(); it++)
    {
        ofs_ << *it << std::endl;
    }*/
}

void
utils::FileAppender::execute()
{
    while (true)
    {
        printData();
        usleep(20000);
    }
}

void
utils::FileAppender::printData()
{
    while (this->messages().size() > 0)
    {
        std::string message = this->messages().front();
        ofs_ << message << std::endl;
        this->messages_.pop_front();
    }
}
