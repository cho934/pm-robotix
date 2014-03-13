/*!
 * \file
 * \brief Définition de la classe pmx::RobotInOutApf
 */

#include <sys/ioctl.h>
#include <fcntl.h>

#include <as_devices/as_max5821.h>
#include <as_devices/as_max1027.h>
#include <as_devices/as_gpio.h>

#include "IRobotInOut.hpp"

#include "LoggerFactory.hpp"
#include "Mutex.hpp"


#ifndef PMX_ROBOTINOUTAPF_H
#define PMX_ROBOTINOUTAPF_H


namespace pmx
{
    /*!
     * \brief Cette classe implemente les interfaces pmx::IRobotInOut
     * définissant les communications avec la carte APF9328.
     * \sa pmx::IRobotInOut
     * \sa utils::Mutex
     */
    class RobotInOutApf : public IRobotInOut, public utils::Mutex
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref RobotInOutApf.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::RobotInOutApf");
            return instance;
        }


    private:


        /*!
         * \brief Structure du DAC MAX5821
         */
        struct as_max5821_device *max5821_dev;

        /*!
         * \brief Structure du ADC MAX1027
         */
        struct as_max1027_device *max1027_dev;

    public:

        /*!
         * \brief Constructeur par défaut.
         */
        RobotInOutApf();

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~RobotInOutApf()
        {
/*
            //fermeture du DAC
            if (as_max5821_close(this->max5821_dev) < 0) {
                logger().error() << "Error on closing max5821_dev" << utils::end;
            }
            //fermeture des ADC
            if (as_max1027_close(this->max1027_dev) < 0) {
                logger().error() << "Error on closing max1027_dev" << utils::end;
            }*/
        }


    };
}

#endif
