/*!
 * \file
 * \brief Implementation de la classe MemoryAppender.
 */

#include "MemoryAppender.hpp"

utils::MemoryAppender::MemoryAppender() : messages_()
{
}

utils::MemoryAppender::~MemoryAppender()
{
    this->flush();
}

void
utils::MemoryAppender::flush()
{
    for (std::list<std::string>::iterator it = messages_.begin(); it != messages_.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    this->messages_.clear();
}
