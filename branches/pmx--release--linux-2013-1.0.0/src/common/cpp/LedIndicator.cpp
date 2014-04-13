/*!
 * \file
 * \brief Implémentation de la classe LedIndicator.
 */

#include "LedIndicator.hpp"

void pmx::LedIndicator::set(int position, int status) {
    this->lock();
    as_gpio_set_pin_value(paths[position], status);
    this->unlock();

}

void pmx::LedIndicator::reset() {
    for (int i = 0; i <= 7; i++) {
        this->set(i, 0);
    }
}

void pmx::LedIndicator::flash() {
    for (int i = 0; i <= 7; i++) {
        this->set(i, 1);
    }
}

void pmx::LedIndicator::flashValue(uint hexValue) {
    for (int i = 0; i <= 7; i++) {
        bool test = (hexValue >> i) & 0x01;
        this->set(i, test);
    }
}

void pmx::LedIndicator::blink(uint nb, uint timeus) {
    for (uint i = 1; i <= nb; i++) {
        flash();
        usleep(timeus);
        if (i > nb) break;
        i++;
        reset();
        usleep(timeus);
    }
}

void pmx::LedIndicator::blinkPin(int position, uint nb, uint timeus) {
    for (uint i = 1; i <= nb; i++) {
        this->set(position, 1);
        usleep(timeus);
        i++;
        if (i > nb) break;
        this->set(position, 0);
        usleep(timeus);
    }
}

void pmx::LedIndicator::alternate(uint nb, uint timeus, uint val1, uint val2) {
    for (uint i = 1; i <= nb; i++) {
        flashValue(val1);
        usleep(timeus);
        i++;
        if (i > nb) break;
        flashValue(val2);
        usleep(timeus);
    }
}