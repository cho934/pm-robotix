/*!
 * \file
 * \brief Implémentation de la classe LedIndicator.
 */

#include "LedIndicator.hpp"


void pmx::LedIndicator::set(int position, int status)
{
    as_gpio_set_pin_value(paths[position], status);

}

void pmx::LedIndicator::reset()
{
    for(int i=0;i<=7;i++)
    {
        this->set(i,0);
    }
}

void pmx::LedIndicator::flash()
{
    for(int i=0;i<=7;i++)
    {
        this->set(i,1);
    }
}

void pmx::LedIndicator::blink(int nb)
{
    for(int i=0;i<=nb;i++)
    {     
        flash();
        usleep(50000);
        reset();
        usleep(50000);
    }
}
