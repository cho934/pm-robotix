/*!
 * \file
 * \brief Implémentation de la classe ConsoleAppender.
 */

#include "ConsoleAppender.hpp"

#include <unistd.h>
#include <list>

void
utils::ConsoleAppender::flush() {
    static_cast<Thread *>(this)->lock();
    for (std::list<std::string>::iterator it = messages_.begin(); it != messages_.end(); it++) {
        (*this->out_) << *it << std::endl;
    }
    static_cast<Thread *>(this)->unlock();
}

void
utils::ConsoleAppender::execute() {

    while (true) {
        this->printData();
        usleep(100000);
    }
}

void
utils::ConsoleAppender::printData() {
    static_cast<Thread *>(this)->lock();
    while (this->messages().size() > 0) {
        std::string message = this->messages().front();
        (*this->out_) << message << std::endl;
        this->messages_.pop_front();
    }
    static_cast<Thread *>(this)->unlock();
}
