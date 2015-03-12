/*!
 * \file
 * \brief Implementation de la classe MemoryAppender.
 */

#include "MemoryAppender.hpp"

#include <iostream>

logs::MemoryAppender::MemoryAppender() : messages_()
{
}

logs::MemoryAppender::~MemoryAppender()
{
    this->flush();
}

void
logs::MemoryAppender::flush()
{
    for (std::list<std::string>::iterator it = messages_.begin(); it != messages_.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    this->messages_.clear();
}
