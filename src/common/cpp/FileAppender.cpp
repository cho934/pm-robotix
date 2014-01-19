/*!
 * \file
 * \brief Implémentation de la classe FileAppender.
 */

#include <iostream>
#include "FileAppender.hpp"

utils::FileAppender::~FileAppender() {
    static_cast<Thread *>(this)->lock();
    ofs_.close();
   
    static_cast<Thread *>(this)->unlock();

}

void
utils::FileAppender::flush() {
    static_cast<Thread *>(this)->lock();
    while (this->messages().size() > 0) {
        std::string message = this->messages().front();
        ofs_ << message << std::endl;
        this->messages_.pop_front();
    }
    static_cast<Thread *>(this)->unlock();
}

void
utils::FileAppender::execute() {
    while (true) {
        printData();
        usleep(20000);
        static_cast<Thread *>(this)->lock();
        if (ofs_ == NULL) {
            static_cast<Thread *>(this)->unlock();
            break;
        }
        static_cast<Thread *>(this)->unlock();
    }
}

void
utils::FileAppender::printData() {
    static_cast<Thread *>(this)->lock();
    while (this->messages().size() > 0) {
        std::string message = this->messages().front();
        ofs_ << message << std::endl;
        this->messages_.pop_front();
    }
    static_cast<Thread *>(this)->unlock();
}
