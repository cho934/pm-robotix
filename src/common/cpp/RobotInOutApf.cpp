/*!
 * \file
 * \brief Implémentation de la classe pmx::RobotInOutApf
 */

#include <string>
#include <cstdlib>
#include <stdio.h>
#include <linux/ppdev.h>
#include "RobotInOutApf.hpp"
#include "LedIndicator.hpp"

using namespace std;

#define GPIORDDIRECTION	_IOR(PP_IOCTL, 0xF0, int)
#define GPIOWRDIRECTION	_IOW(PP_IOCTL, 0xF1, int)
#define GPIORDDATA	_IOR(PP_IOCTL, 0xF2, int)
#define GPIOWRDATA	_IOW(PP_IOCTL, 0xF3, int)
#define GPIORDMODE	_IOR(PP_IOCTL, 0xF4, int)
#define GPIOWRMODE	_IOW(PP_IOCTL, 0xF5, int)

const char* pmx::RobotInOutApf::FILE_D("/dev/gpio/portD");

pmx::RobotInOutApf::RobotInOutApf() : IRobotIn(), IRobotOut(), utils::Mutex(), fileDescriptorD(open(FILE_D, O_RDWR))
{
    int ret = 0;
    if (this->fileDescriptorD < 0)
    {
        logger().error() << "No access to the file <" << FILE_D << ">" << utils::end;
    }

    //désactivation des bus de multiplexage à l'initialisation du robot.
    desactivateE1E2();

    //LED INDICATOR TEST INIT
    pmx::LedIndicator::instance().blinkPin(1, 3, 200000);

    //ouverture du DAC pour la puissance moteur
    max5821_dev = as_max5821_open(0, 0x38);
    if (this->max5821_dev == NULL)
    {
        logger().error() << "Error, can't open max5821" << utils::end;
        //LED INDICATOR TEST INIT
        pmx::LedIndicator::instance().setOff(1);
        exit(0);
    }else
    {
        //power up des DAC
        ret = as_max5821_power(max5821_dev, 'a', MAX5821_POWER_UP);
        if (ret < 0)
        {
            logger().error() << "Error, can't DAC[A] power up" << utils::end;
            //LED INDICATOR TEST INIT
            pmx::LedIndicator::instance().setOff(1);
            exit(0);
        }else
        {
            ret = as_max5821_power(max5821_dev, 'b', MAX5821_POWER_UP);
            if (ret < 0)
            {
                logger().error() << "Error, can't DAC[B] power up" << utils::end;
                //LED INDICATOR TEST INIT
                pmx::LedIndicator::instance().setOff(1);
                exit(0);
            }
        }
    }


    //ouverture du ADC pour les GP2

    //LED INDICATOR TEST INIT
    pmx::LedIndicator::instance().blinkPin(2, 3, 200000);
    
    AS_max1027_mode mode = AS_MAX1027_SLOW;
    max1027_dev = as_max1027_open(MAX1027_SPI_NUM, mode);
    if (max1027_dev == NULL)
    {
        logger().error() << "Error, can't open max1027. Is max1027 modprobed ?" << utils::end;
        //LED INDICATOR TEST INIT
        pmx::LedIndicator::instance().setOff(2);
        printf("Exiting RobotInOutApf 1\n");
        exit(51);
    }else
    {
        //average de 1 defini aussi à l'initialisation de IrSensor.cpp
        ret = as_max1027_set_averaging(max1027_dev, 32); //(4, 8, 16, 32). Set to 1 for disabling averaging.
        if (ret < 0)
        {
            logger().error() << "Error, can't set averaging" << utils::end;
            //LED INDICATOR TEST INIT
            pmx::LedIndicator::instance().setOff(2);
            printf("Exiting RobotInOutApf 2\n");
            exit(52);
        }
    }

}

void
pmx::RobotInOutApf::setValue(ushort demultiplexor, ushort pin, bool state)
{
    if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "setValue         [dm:" << demultiplexor << "] [pin:" << pin << "] [state:" << state << "]" << utils::end;
    }
    this->lock();
    setValueInternal(demultiplexor, pin, state);
    this->unlock();
}

void
pmx::RobotInOutApf::setValueInternal(ushort demultiplexor, ushort pin, bool state)
{
    long portval;
    ushort stateAsNumber = state ? 1 : 0;
    if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "setValueInternal [dm:" << demultiplexor << "] [pin:" << pin << "] [stateAsNumber:" << stateAsNumber << "]" << utils::end;
    }
    ioctl(fileDescriptorD, GPIORDDATA, &portval); //read GPIO
    if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "DATA flags before [portval:" << reinterpret_cast<void*> (portval) << "]" << utils::end; // Affiche la valeur actuelle en hexadecimal
    }
    portval |= (0x01E7 << 15); //set à 1 les pins concernés sauf E1/E2

    portval &= (((((((3 << 4) + stateAsNumber) << 3) + pin) << 5) + demultiplexor) << 15) + 0x7FFF; //set à 0 des pins necessaires
    ioctl(fileDescriptorD, GPIOWRDATA, &portval); //write GPIO
    if (logger().isActive(utils::Level::DEBUG))
    {
        ioctl(fileDescriptorD, GPIORDDATA, &portval); //read GPIO
        logger().debug() << "DATA flags after [portval:" << reinterpret_cast<void*> (portval) << "]" << utils::end; // Affiche la valeur actuelle en hexadecimal
    }

    //activation E1
    activateE1();

    //desactivateE1E2();
    desactivateE1E2();
}

void
pmx::RobotInOutApf::desactivateE1E2()
{
    //Mise à 1 de E1 et E2 en laissant les autres pins.
    long portval;
    ioctl(fileDescriptorD, GPIORDDATA, &portval); //read GPIO
    if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "DATA(E1/E2=>0) flags before [portval:" << reinterpret_cast<void*> (portval) << "]" << utils::end; // Affiche la valeur actuelle en hexadecimal
    }
    portval |= (0x3000 << 15); //set à 1 les pins concernés (PD27=E1 et PD28=E2)
    ioctl(fileDescriptorD, GPIOWRDATA, &portval); //write GPIO
    if (logger().isActive(utils::Level::DEBUG))
    {
        ioctl(fileDescriptorD, GPIORDDATA, &portval); //read GPIO
        logger().debug() << "DATA(E1/E2=>1) flags after [portval:" << reinterpret_cast<void*> (portval) << "]" << utils::end; // Affiche la valeur actuelle en hexadecimal
    }
}

void
pmx::RobotInOutApf::activateE1()
{
   
    //mise à zero de E1
    long portval;
    ioctl(fileDescriptorD, GPIORDDATA, &portval); //read GPIO
    if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "DATA(E1=>1) flags before [portval:" << reinterpret_cast<void*> (portval) << "]" << utils::end; // Affiche la valeur actuelle en hexadecimal
    }
    portval &= (0xF7FFFFFF); //set à 0 des pins necessaires (PD27=E1)
    ioctl(fileDescriptorD, GPIOWRDATA, &portval); //write GPIO
    if (logger().isActive(utils::Level::DEBUG))
    {
        ioctl(fileDescriptorD, GPIORDDATA, &portval); //read GPIO
        logger().debug() << "DATA(E1=>0) flags after [portval:" << reinterpret_cast<void*> (portval) << "]" << utils::end; // Affiche la valeur actuelle en hexadecimal
    }
     
}

void
pmx::RobotInOutApf::activateE2()
{
    
    //mise à zero de E2
    long portval;
    ioctl(fileDescriptorD, GPIORDDATA, &portval); //read GPIO
    if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "DATA(E2=>1) flags before [portval:" << reinterpret_cast<void*> (portval) << "]" << utils::end; // Affiche la valeur actuelle en hexadecimal
    }
    portval &= (0xEFFFFFFF); //set à 0 des pins necessaires (PD28=E2)
    ioctl(fileDescriptorD, GPIOWRDATA, &portval); //write GPIO
    if (logger().isActive(utils::Level::DEBUG))
    {
        ioctl(fileDescriptorD, GPIORDDATA, &portval); //read GPIO
        logger().debug() << "DATA(E2=>0) flags after [portval:" << reinterpret_cast<void*> (portval) << "]" << utils::end; // Affiche la valeur actuelle en hexadecimal
    }
    
}

void
pmx::RobotInOutApf::setValues(ushort element, int value) //Value de -128=>127
{
    logger().info() << "setValues : VALUE=" << value << " element=" << (int)element << utils::end;
      this->lock();
    if (element == IRobotOut::MD25_MOTOR_LEFT)
    {
        logger().info() << "IRobotOut::MD25_MOTOR_LEFT=" << (int)element << utils::end;
        utils::Md25::instance().ensureSetSpeed(value+128, MD25_SPEED1_REG); //mode 0 : 0=>128=>255
        
    }else if (element == IRobotOut::MD25_MOTOR_RIGHT)
    {
        logger().info() << "IRobotOut::MD25_MOTOR_RIGHT=" << (int)element << utils::end;
        utils::Md25::instance().ensureSetSpeed(value+128, MD25_SPEED2_REG); //mode 0 : 0=>128=>255
        
    }else if (element == IRobotOut::DAC_MOTOR_RED) //Value de 0 à 1024
    {
        logger().debug() << "setValues on DAC_MOTOR_RED [value:" << value << "]" << utils::end;
        if (as_max5821_set_one_value(max5821_dev, 'b', value) < 0)
        {
            logger().error() << "Error, can't select value" << utils::end;
        }
        if (value == 0)
        {
            //!\todo désactivation du DAC b
            //as_max5821_power(max5821_dev,'b', MAX5821_POWER_DOWN_MODE2);
        }
    }else if (element == IRobotOut::DAC_MOTOR_YELLOW) //Value de 0 à 1024
    {
        logger().debug() << "setValues on DAC_MOTOR_YELLOW [value:" << value << "]" << utils::end;
        if (as_max5821_set_one_value(max5821_dev, 'a', value) < 0)
        {
            logger().error() << "Error, can't select value" << utils::end;
        }
        if (value == 0)
        {
            //!\todo désactivation du DAC a
            //as_max5821_power(max5821_dev,'a', MAX5821_POWER_DOWN_MODE2);
        }
    }else
    {
        logger().debug() << "setValues on dm [element:" << element << "] [value:" << value << "]" << utils::end;

      
        for (ushort pin = 0; pin < 8; pin++)
        {
            bool pinValue = (value >> pin) & 0x01;
            setValueInternal(element, pin, pinValue);
        }
      
    }
      this->unlock();
}

bool
pmx::RobotInOutApf::getGpioDValue(int pinOnPortD)
{
    long portval;
    ioctl(fileDescriptorD, GPIORDDATA, &portval); //read GPIO
    if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "getGpioDValue [portval:" << reinterpret_cast<void*> (portval) << "]" << utils::end; // Affiche la valeur actuelle en hexadecimal
    }
    return (portval >> pinOnPortD) & 0x01;
}

bool
pmx::RobotInOutApf::as_getGpioDValue(int pinOnPortD)
{
    struct as_gpio_device *pd;
    pd = as_gpio_open('D', pinOnPortD);
    int value = as_gpio_get_pin_value(pd);
    as_gpio_close(pd);
    return (bool)value;
}

void
pmx::RobotInOutApf::setMultiplexor(ushort multiplexor, ushort pin)
{
    long portval;
    ioctl(fileDescriptorD, GPIORDDATA, &portval); //read GPIO
    if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "setMultiplexor flags before [portval:" << reinterpret_cast<void*> (portval) << "]" << utils::end; // Affiche la valeur actuelle en hexadecimal
    }
    portval |= (0x00E7 << 15); //set à 1 les pins concernés sauf E1/E2/AD
    portval &= (((((0xFF8 + pin) << 5) + multiplexor) << 15) + 0x7FFF); //mise en place de l'adresse du multiplexeur et de la pin sur le portD
    ioctl(fileDescriptorD, GPIOWRDATA, &portval); //write GPIO
    if (logger().isActive(utils::Level::DEBUG))
    {
        ioctl(fileDescriptorD, GPIORDDATA, &portval); //read GPIO
        logger().debug() << "setMultiplexor flags after [portval:" << reinterpret_cast<void*> (portval) << "]" << utils::end; // Affiche la valeur actuelle en hexadecimal
    }
}

int
pmx::RobotInOutApf::getValue(ushort element, ushort pin)
{
    this->lock();
    if (element == IRobotIn::ADC_USE)
    {
        //PIN 0-6 uniquement
        if (pin > 6)
        {
            logger().error() << "Error on max1027_dev : pin > 6" << utils::end;
        }
        int value = 0;
        int ret = as_max1027_get_value_milliVolt(this->max1027_dev, pin, &value);
        if (ret < 0)
        {
            logger().error() << "Error on max1027_dev:as_max1027_get_value_milliVolt()" << utils::end;
            //!\TODO LEDINDICATOR Error on max1027_dev:as_max1027_get_value_milliVolt()
        }else
        {
            logger().info() << " pin:" << pin << " mV:" << value << utils::end;
            this->unlock();
            return value;
        }
    }else
    {

        if (logger().isActive(utils::Level::DEBUG))
        {
            logger().debug() << "multiplexor:" << element << " pin:" << pin << utils::end; // Affiche la valeur actuelle en hexadecimal
        }
        

        setMultiplexor(element, pin);

        activateE2();

        //recuperation de la valeur d'entrée "DE" du multiplexage.
        bool pinValue = getGpioDValue(18); //PD18

        desactivateE1E2();

        logger().info() << "multiplexor:" << element << " pin:" << pin << utils::end;

        this->unlock();
        return pinValue;
    }
    this->unlock();
    return 0; //pour supprimer un warning
}

int
pmx::RobotInOutApf::getValues(ushort multiplexor)
{
    int result = 0;
    for (ushort pin = 0; pin < 8; pin++)
    {
        result = result | (pmx::RobotInOutApf::getValue(multiplexor, pin) << pin);
    }
    return result;
}

bool
pmx::RobotInOutApf::getImpRight()
{
    bool pinValue = getGpioDValue(19); //pin IMPD

    return pinValue;
}

bool
pmx::RobotInOutApf::getImpLeft()
{
    bool pinValue = getGpioDValue(24); //pin IMPG

    return pinValue;
}

bool
pmx::RobotInOutApf::getImpLeftWay()
{
    bool pinValue = getGpioDValue(25); //pin IMPGD

    return pinValue;
}

bool
pmx::RobotInOutApf::getImpRightWay()
{
    bool pinValue = getGpioDValue(26); //pin IMPDD

    return pinValue;
}
