/*!
 * \file
 * \brief Définition de l'interface IRobotInOut.
 */

#include "Macro.hpp"

#ifndef PMX_IROBOTINOUT_H
#define	PMX_IROBOTINOUT_H

namespace pmx
{
    /*!
     * \brief Représente les entrées/sorties du robot qui permettent de transférer des
     * informations entre le programme et l'électronique.
     */
    class IRobotInOut
    {
    public:


        /*!
         * \name Référence de pins
         * \{
         */
        static const ushort PIN0 = 0;
        static const ushort PIN1 = 1;
        static const ushort PIN2 = 2;
        static const ushort PIN3 = 3;
        static const ushort PIN4 = 4;
        static const ushort PIN5 = 5;
        static const ushort PIN6 = 6;
        static const ushort PIN7 = 7;
        /*! \} */




    protected:

        /*!
         * \brief Constructeur de la classe.
         */
        IRobotInOut()
        {
        }

    public:

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~IRobotInOut()
        {
        }

        //ADC

        //I2C

        //GPIO

        //DAC

        //SPI

        //FPGA



    };
}

#endif
