/*!
 * \file
 * \brief Implémentation de la classe LedIndicator.
 */

#include "LedIndicator.hpp"

void pmx::LedIndicator::set(int position, int status)
{
    this->lock();
    as_gpio_set_pin_value(paths[position], status);
    this->unlock();

}

void pmx::LedIndicator::reset()
{
    for (int i = 0; i <= 7; i++)
    {
        this->set(i, 0);
    }
}

void pmx::LedIndicator::flash()
{
    for (int i = 0; i <= 7; i++)
    {
        this->set(i, 1);
    }
}

void pmx::LedIndicator::blink(int nb, int timeus)
{
    for (int i = 0; i <= nb; i++)
    {
        flash();
        usleep(timeus);
        reset();
        usleep(timeus);
    }
}
