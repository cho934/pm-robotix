#include "FileAppender.hpp"

utils::FileAppender::FileAppender(const std::string & filename) : ofs_(filename.c_str())
{
    start();
}

utils::FileAppender::~FileAppender()
{
    ofs_.close();
}

void
utils::FileAppender::flush()
{
    for(std::list<std::string>::iterator it = messages_.begin(); it != messages_.end(); it++ )
    {
        ofs_ << *it << std::endl;
    }
}

void
utils::FileAppender::execute()
{
    while(true)
    {
        printData();
        this->yield();
    }
}

void
utils::FileAppender::printData()
{
    while(this->messages().size() > 0)
    {
        std::string message = this->messages().front();
        ofs_ << message << std::endl;
        this->messages_.pop_front();
        this->yield();
    }
}
