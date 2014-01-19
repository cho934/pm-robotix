/*!
 * \file
 * \brief Définition de l'interface IRobotIn.
 */

#include "Macro.hpp"

#ifndef PMX_IROBOTIN_H
#define	PMX_IROBOTIN_H

namespace pmx
{
    /*!
     * \brief Représente les entrées du robot qui permettent de transférer des
     * informations entre le programme et l'électronique.
     */
    class IRobotIn
    {
    public:

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

        /*!
         * \name Signal digital pour les GP2
         * \{
         */
        static const ushort ADC_USE = 8;
        /*! \} */


    protected:

        /*!
         * \brief Constructeur de la classe.
         */
        IRobotIn()
        {
        }

    public:

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~IRobotIn()
        {
        }

        /*!
         * \brief Retourne la valeur du pin du multiplexeur selectionné (0-1) ou valeur en mV de l'ADC.
         * \param multiplexor
         *        Le multiplexeur à utiliser (Valeurs : RobotOut::M0 à RobotOut::M5 ou IRobotIn::ADC_USE).
         * \param pin
         *        Le pin du multiplexeur à lire (Valeurs : RobotOut::PIN0 à RobotOut::PIN7 à RobotOut::PIN6).
         */
        virtual int getValue(ushort multiplexor, ushort pin) = 0;

        /*!
         * \brief Retourne l'ensemble de l'octet de données d'un multiplexeur.
         * \param multiplexor
         *        Le multiplexeur à utiliser (Valeurs : RobotOut::M0 à RobotOut::M5).
         */
        virtual int getValues(ushort multiplexor) = 0;

        /*!
         * \return Valeur actuelle du codeur droit.
         *
         * \deprecated
         */
        virtual bool getImpRight() = 0;

        /*!
         * \return Valeur actuelle du codeur gauche.
         * \deprecated
         */
        virtual bool getImpLeft() = 0;

        /*!
         * \return Valeur du déphasage du codeur gauche.
         * \deprecated
         */
        virtual bool getImpLeftWay() = 0;

        /*!
         * \return Valeur du déphasage du codeur gauche.
         * \deprecated
         */
        virtual bool getImpRightWay() = 0;

    };
}

#endif
