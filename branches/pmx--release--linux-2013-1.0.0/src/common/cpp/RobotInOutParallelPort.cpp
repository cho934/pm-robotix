/*!
 * \file
 * \brief Implémentation de la classe RobotInOutParallelPort.
 */

#include <unistd.h>
#include <iostream>
#include "RobotInOutParallelPort.hpp"

pmx::RobotInOutParallelPort::RobotInOutParallelPort() : IRobotIn(), IRobotOut(), utils::Mutex()
{
    setValue(15, getControlAddress()); // LPT_WRITE_CONTROL_BYTE(15);
    setValue(~0x0B, getControlAddress()); // LPT_WRITE_CONTROL_BYTE(~0x0B);

    desactivateE1E2();
    //permet de pouvoir le désactiver en mode entrée.
    activateCTRL_C3();

}

void pmx::RobotInOutParallelPort::setValueInternal(ushort demultiplexor, ushort pin, bool state)
{
    ushort stateAsNumber = state ? 1 : 0;
    ushort value = (((demultiplexor << 1) + stateAsNumber) << 3) + pin;

    setValue(value, getDataAddress());

    //activation E1 (carte démultiplexeurs, CONTROL C0 => mise à zero
    activateE1();
    //désactivation E1 et E2 (carte démultiplexeurs, CONTROL C0 => mise à 1) (0x03 ^ 0x0B = 0x08) et desactivation E2
    desactivateE1E2();
}

void pmx::RobotInOutParallelPort::setValue(ushort demultiplexor, ushort pin, bool state)
{
    this->lock();
    setValueInternal(demultiplexor, pin, state);
    this->unlock();
}

void pmx::RobotInOutParallelPort::setValues(ushort demultiplexor, int value)
{
    this->lock();
    for (ushort pin = 0; pin < 8; pin++)
    {
        bool pinValue = (value >> pin) & 0x01;
        setValueInternal(demultiplexor, pin, pinValue);
    }
    this->unlock();
}

int pmx::RobotInOutParallelPort::getValue(ushort multiplexor, ushort pin)
{
    this->lock();

    ushort value = (multiplexor << 4) + pin; //initialisation du bus d'adresse.
    setValue(value, getDataAddress()); //application sur le bus.

    activateE2();

    // Le pthread_yield ne peut pas être appliquer puisqu'on est dans un mutex ?
    usleep(1);

    //recuperation de la valeur sur les M et pin demandés.
    bool pinValue = getValue(4); //pin d'entrée utilisé (n°12) du port "STATUS".

    desactivateE1E2();

    this->unlock();
    return pinValue;
}

int pmx::RobotInOutParallelPort::getValues(ushort multiplexor)
{

    int result = 0;
    for (ushort pin = 0; pin < 8; pin++)
    {
        result = result | (pmx::RobotInOutParallelPort::getValue(multiplexor, pin) << pin);
    }

    return result;
}

bool pmx::RobotInOutParallelPort::getImpRight()
{
    bool pinValue = getValue(8); //pin d'entrée utilisé (n°10) du port "STATUS".
    return pinValue;
}

bool pmx::RobotInOutParallelPort::getImpLeft()
{
    bool pinValue = getValue(16); //pin d'entrée utilisé (n°11) du port "STATUS".
    return pinValue;
}

bool pmx::RobotInOutParallelPort::getImpLeftWay()
{
    bool pinValue = getValue(2); //pin d'entrée utilisé (n°13) du port "STATUS".
    return pinValue;
}

bool pmx::RobotInOutParallelPort::getImpRightWay()
{
    //pin d'entrée utilisé (n°17) du port "CONTROL".
    this->lock();
    activateCTRL_C3(); //activation niveau haut de la pin en mode output.
    bool pinValue = getValuesCTRL_C3(); //recuperation de la valeur inversée par un 74LS04.
    this->unlock();
    return pinValue;
}

