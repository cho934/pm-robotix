/*!
 * \file
 * \brief Implémentation de la classe UnitTestAppender.
 */

#include "DevUnitTestAppender.hpp"
#include "DevUnitTest.hpp"

utils::DevUnitTestAppender::DevUnitTestAppender() {
    this->indent_=0;
}

utils::DevUnitTestAppender::~DevUnitTestAppender() {
}

void
utils::DevUnitTestAppender::writeMessage(const utils::Logger & logger, const utils::Level & level, const std::string & message) {
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
utils::DevUnitTestAppender::increaseIndent() {
    this->lock();
    this->indent_++;
    this->unlock();
}

void
utils::DevUnitTestAppender::decreaseIndent() {
    this->lock();
    this->indent_--;
    if (this->indent_ < 0) {
        this->indent_ = 0;
    }
    this->unlock();
}

bool
utils::DevUnitTestAppender::expectedError(const std::string& message) {
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
utils::DevUnitTestAppender::cleanMessages() {
    this->lock();
    this->messages_.clear();
    this->unlock();
}
