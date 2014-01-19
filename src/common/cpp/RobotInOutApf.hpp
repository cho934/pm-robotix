/*!
 * \file
 * \brief Définition de la classe pmx::RobotInOutApf
 */

#include <sys/ioctl.h>
#include <fcntl.h>
#include <as_devices/as_max5821.h>
#include <as_devices/as_max1027.h>
#include <as_devices/as_gpio.h>
#include "IRobotOut.hpp"
#include "IRobotIn.hpp"
#include "LoggerFactory.hpp"
#include "Mutex.hpp"
#include "Md25.hpp"

#ifndef PMX_ROBOTINOUTAPF_H
#define	PMX_ROBOTINOUTAPF_H

#define MAX1027_SPI_NUM (1) //MAX1027_SPI_NUM on APF9328

namespace pmx
{
    /*!
     * \brief Cette classe implemente les interfaces pmx::IRobotIn et
     * pmx::IRobotOut pour une communication avec la carte APF9328.
     * \sa pmx::IRobotOut
     * \sa pmx::IRobotIn
     * \sa utils::Mutex
     */
    class RobotInOutApf : public IRobotIn, public IRobotOut, public utils::Mutex
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

        static const char* FILE_D;

    private:

        /*!
         * \brief Le descripteur de fichier associé avec le port D de l'Apf
         */
        int fileDescriptorD;

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
            close(this->fileDescriptorD);

            //fermeture du DAC
            if (as_max5821_close(this->max5821_dev) < 0) {
                logger().error() << "Error on closing max5821_dev" << utils::end;
            }
            //fermeture des ADC
            if (as_max1027_close(this->max1027_dev) < 0) {
                logger().error() << "Error on closing max1027_dev" << utils::end;
            }

            //fermeture I2C
            utils::Md25::instance().closeI2C();
        }

        virtual void setValue(ushort demultiplexor, ushort pin, bool state);

        virtual void setValues(ushort demultiplexor, int value);

        /*!
         * \brief Equivalent non-threadsafe de la méthode setValue(ushort, ushort, bool).
         */
        virtual void setValueInternal(ushort demultiplexor, ushort pin, bool state);

        virtual void desactivateE1E2();

        virtual void activateE1();

        virtual void activateE2();

        /*!
         * \deprecated remplacer par les interruption matérielle dans le sensorManager
         */
        virtual bool getImpRight();

        /*!
         * \deprecated remplacer par les interruption matérielle dans le sensorManager
         */
        virtual bool getImpLeft();

        /*!
         * \deprecated remplacer par les interruption matérielle dans le sensorManager
         */
        virtual bool getImpLeftWay();

        /*!
         * \deprecated remplacer par les interruption matérielle dans le sensorManager
         */
        virtual bool getImpRightWay();

        virtual int getValue(ushort element, ushort pin);

        virtual int getValues(ushort multiplexor);

        virtual bool getGpioDValue(int pinOnPortD);

        virtual bool as_getGpioDValue(int pinOnPortD);

        virtual void setMultiplexor(ushort multiplexor, ushort pin);

    };
}

#endif
