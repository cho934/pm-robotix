/*!
 * \file
 * \brief Implémentation de la classe UnitTestAppender.
 */

#include "UnitTestAppender.hpp"
#include "UnitTest.hpp"

utils::UnitTestAppender::UnitTestAppender() {
    this->indent_=0;
}

utils::UnitTestAppender::~UnitTestAppender() {
}

void
utils::UnitTestAppender::writeMessage(const utils::Logger & logger, const utils::Level & level, const std::string & message) {
    if (level == utils::Level::INFO) {
        this->lock();
        std::ostringstream out;
        for (int i = 0; i<this->indent_; i++) {
            out << "   ";
        }
        out << message;
        this->messages_.push_back(out.str());
        this->unlock();
    }else {
        utils::MemoryAppender::writeMessage(logger, level, message);
    }
}

void
utils::UnitTestAppender::increaseIndent() {
    this->lock();
    this->indent_++;
    this->unlock();
}

void
utils::UnitTestAppender::decreaseIndent() {
    this->lock();
    this->indent_--;
    if (this->indent_ < 0) {
        this->indent_ = 0;
    }
    this->unlock();
}

bool
utils::UnitTestAppender::expectedError(const std::string& message) {
    this->lock();
    for (std::list<std::string>::iterator it = messages_.begin(); it != messages_.end(); it++) {
        if (*it == message) {
            this->messages_.erase(it);
            this->unlock();
            return true;
        }
    }
    this->unlock();
    return false;
}

void
utils::UnitTestAppender::cleanMessages() {
    this->lock();
    this->messages_.clear();
    this->unlock();
}
