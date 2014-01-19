/*!
 * \file
 * \brief Définition de l'interface IRobotIn.
 */

#include "Macro.hpp"

#ifndef PMX_IROBOTIN_H
#define	PMX_IROBOTIN_H

namespace pmx
{
    class IRobotIn
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
        IRobotIn()
        {}
        
    public:
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ IRobotIn()
        {}
        
        /*!
         * \brief Retourne la valeur du pin du multiplexeur selectionné .
         * \param multiplexor
         *        Le multiplexeur à utiliser (Valeurs : RobotOut::M0 à RobotOut::M5).
         * \param pin
         *        Le pin du multiplexeur à lire (Valeurs : RobotOut::PIN0 à RobotOut::PIN7).
         */
        virtual bool getValue(ushort multiplexor, ushort pin) =0;
        
        /*!
         * \brief Retourne l'ensemble de l'octet de données d'un multiplexeur.
         * \param multiplexor
         *        Le multiplexeur à utiliser (Valeurs : RobotOut::M0 à RobotOut::M5).
         */
        virtual int getValues(ushort multiplexor) =0;
        
        /*!
         * \return Valeur actuelle du codeur droit.
         */
        virtual bool getImpRight() =0;
        
        /*!
         * \return Valeur actuelle du codeur gauche.
         */
        virtual bool getImpLeft() =0;
        
        /*!
         * \return Valeur du déphasage du codeur gauche.
         */
        virtual bool getImpLeftWay() =0;
        
        /*!
         * \return Valeur du déphasage du codeur gauche.
         */
        virtual bool getImpRightWay() =0;
    };
}


#endif
