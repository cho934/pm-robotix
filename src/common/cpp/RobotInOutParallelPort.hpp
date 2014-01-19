/*!
 * \file
 * \brief Définition de la classe RobotInOutParallelPort.
 */

#include "sys/io.h"
#include "IRobotIn.hpp"
#include "IRobotOut.hpp"
#include "Mutex.hpp"
#include <iostream>

#ifndef PMX_ROBOTOUTPARALLELPORT_H
#define	PMX_ROBOTOUTPARALLELPORT_H

namespace pmx
{
    /*!
     * \brief Cette classe implemente les interfaces pmx::IRobotIn et
     * pmx::IRobotOut pour une communication sur le port parallèle.
     *
     * \sa pmx::IRobotIn
     * \sa pmx::IRobotOut
     */
    class RobotInOutParallelPort : public IRobotIn, public IRobotOut, public utils::Mutex
    {
    public:

        /*!
         * Adresse de référence pour le port parallèle.
         */
        static const int DATA_ADDR = 0x0378;

        /*!
         * \brief Constructeur par défaut.
         */
        RobotInOutParallelPort();

        /*!
         * \brief Destructeur par défaut.
         */
        virtual ~RobotInOutParallelPort()
        {
        }

        virtual bool getImpRight();

        virtual bool getImpLeft();

        virtual bool getImpLeftWay();

        virtual bool getImpRightWay();

        virtual bool * getImp();

        virtual void setValue(ushort demultiplexor, ushort pin, bool state);

        virtual void setValues(ushort demultiplexor, ushort value);

        virtual int getValue(ushort multiplexor, ushort pin);

        virtual int getValues(ushort multiplexor);

    protected:

        /*!
         * \brief Equivalent non-threadsafe de la méthode setValue(ushort, ushort, bool).
         */
        virtual void setValueInternal(ushort demultiplexor, ushort pin, bool state);

        /*!
         * \brief Retourne l'adresse de référence pour le bloc de données.
         */
        virtual inline int getDataAddress()
        {
            return DATA_ADDR;
        }

        /*!
         * \brief Retourne l'adresse de référence pour le bloc d'état.
         */
        inline int getStatusAddress()
        {
            return getDataAddress() + 1;
        }

        /*!
         * \brief Retourne l'adresse de référence pour le bloc de contrôle.
         */
        inline int getControlAddress()
        {
            return getDataAddress() + 2;
        }

        /*!
         * \brief Cette méthode doit être surchargée pour effectuer la mise à
         * jour d'une information.
         *
         * \param value
         *        Valeur à utiliser.
         * \param addr
         *        Adresse physique à mettre à jour.
         */
        inline void setValue(ushort value, int addr)
        {
            if (addr == getDataAddress())
            {
                outb(value, addr);
            }

            else if (addr == getControlAddress())
            {
                outb(value ^ 0X0B, addr);
            }
            else
            {
                // Effectuer au moins une trace dans ce cas.
            }
        }

        /*!
         * \brief Retourne la valeur du bloc STATUS du port parallele.
         * \return La valeur retournée est toujours < 32 (le bloc STATUS a 5 bits).
         */
        inline ushort getValues()
        {
            return (inb(getStatusAddress()) ^ 0x80) >> 3;
        }

        /*!
         * \brief Retourne la valeur du bloc CONTROL du port parallele en entier.
         * \return ushort indiquant la valeur retournée en tenant compte des inversions.
         */
        inline ushort getValuesCTRL()
        {
            return (inb(getControlAddress()) ^ 0x0B);
        }

        /*!
         * \brief Retourne un bit de la valeur du port STATUS du port parallele.
         * \param mask Masque de l'entrée à obtenir.
         * \return Booléen indiquant si l'entrée est active ou non.
         */
        inline bool getValue(ushort mask)
        {
            ushort temp = getValues() & mask;

            //inversion true/false à cause de l'ajout de l'optocoupleur
            return !(temp == mask);
        }

    private:

        inline void desactivateE1E2()
        {
            //Mise à 1 de E1 et E2 en laissant les autres pins.
            ushort inbtemp = getValuesCTRL() & 0x0F; //lecture du LSnibble
            ushort temp = (inbtemp | 0x03) ^ 0x0B; //applique le filtre d'inversion après avoir désactivé E1 et E2
            outb(temp, getControlAddress());
        }

        inline void activateE1()
        {
            //mise à zero de E1
            ushort inbtemp = getValuesCTRL() & 0x0F; //lecture du LSnibble
            ushort temp = (inbtemp & 0x0E) ^ 0x0B; //applique le filtre d'inversion après avoir activé E1
            outb(temp, getControlAddress());
        }

        inline void activateE2()
        {
            //mise à zero de E2
            ushort inbtemp = getValuesCTRL() & 0x0F; //lecture du LSnibble
            ushort temp = (inbtemp & 0x0D) ^ 0x0B; //applique le filtre d'inversion après avoir activé E2
            outb(temp, getControlAddress());
        }

        inline void activateCTRL_C3()
        {
            //mise à 1 de C3
            ushort inbtemp = getValuesCTRL() & 0x0F; //lecture du LSnibble
            ushort temp = (inbtemp | 0x08) ^ 0x0B;
            outb(temp, getControlAddress());
        }

        inline void desactivateCTRL_C3()
        {
            //mise à 1 de C3
            ushort inbtemp = getValuesCTRL() & 0x0F; //lecture du LSnibble
            ushort temp = (inbtemp & 0x07) ^ 0x0B;
            outb(temp, getControlAddress());
        }

        inline bool getValuesCTRL_C3()
        {
            ushort temp = getValuesCTRL() & 8;

            //inversion true/false à cause de l'ajout du 74LS04.
            return !(temp == 8);
        }
    };
}

#endif
