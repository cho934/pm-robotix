/*!
 * \file
 * \brief Implémentation de la classe ConsoleAppender.
 */

#include "ConsoleAppender.hpp"

#include <unistd.h>
#include <list>

void
logs::ConsoleAppender::flush() {
    static_cast<utils::Thread *>(this)->lock();
    for (std::list<std::string>::iterator it = messages_.begin(); it != messages_.end(); it++) {
        (*this->out_) << *it << std::endl;
    }
    static_cast<utils::Thread *>(this)->unlock();
}

void
logs::ConsoleAppender::execute() {

    while (true) {
        this->printData();
        usleep(100000);
    }
}

void
logs::ConsoleAppender::printData() {
    static_cast<utils::Thread *>(this)->lock();
    while (this->messages().size() > 0) {
        std::string message = this->messages().front();
        (*this->out_) << message << std::endl;
        this->messages_.pop_front();
    }
    static_cast<utils::Thread *>(this)->unlock();
}
