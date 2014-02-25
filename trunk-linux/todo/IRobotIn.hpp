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



    };
}

#endif
