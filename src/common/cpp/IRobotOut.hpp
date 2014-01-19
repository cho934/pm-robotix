/*!
 * \file
 * \brief Définition de l'interface IRobotOut.
 */

#include "Macro.hpp"

#ifndef PMX_IROBOTOUT_H
#define	PMX_IROBOTOUT_H

namespace pmx
{
    class IRobotOut
    {
    public:
        
        /*!
         * \name Démultiplexeurs
         * \{
         */
        static const ushort DM0 = 0;
        static const ushort DM1 = 1;
        static const ushort DM2 = 2;
        static const ushort DM3 = 3;
        static const ushort DM4 = 4;
        static const ushort DM5 = 5;
        static const ushort DM6 = 6;
        static const ushort DM7 = 7;
        /*! \} */
        
        /*!
         * \name Multiplexeurs
         * \{
         */
        static const ushort M0 = 0;
        static const ushort M1 = 1;
        static const ushort M2 = 2;
        static const ushort M3 = 3;
        static const ushort M4 = 4;
        static const ushort M5 = 5;
        /*! \} */
        
        /*!
         * \name Référence des pates d'un démultiplexeur
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
        IRobotOut()
        {}
        
    public:
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ IRobotOut()
        {}
        
        
        /*!
         * \brief Définit une valeur en fonction du demultiplexeur et de la
         * patte (pin) à mettre à jour.
         * \param demultiplexor
         *        Le demultiplexeur à utiliser (Valeurs : RobotOut::DM0 à RobotOut::DM7).
         * \param pin
         *        La patte (pin) du demultiplexeur à modifier (Valeurs : RobotOut::PIN0 à RobotOut::PIN7).
         * \param state
         *        La nouvelle valeur associée à cette patte (pin).
         */
        virtual void setValue(ushort demultiplexor, ushort pin, bool state) =0;
        
        /*!
         * \brief Définit l'ensemble des valeurs d'un demultiplexeur.
         * \param demultiplexor
         *        Le demultiplexeur à utiliser (Valeurs : RobotOut::DM0 à RobotOut::DM7).
         * \param value
         *        Un octet contenant les valeurs à appliquer au démultiplexeur.
         */
        virtual void setValues(ushort demultiplexor, ushort value) =0;
    };
}

#endif
