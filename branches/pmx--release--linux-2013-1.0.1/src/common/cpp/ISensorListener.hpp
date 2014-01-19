/*!
 * \file
 * \brief Définition de l'interface ISensorListener.
 */

#ifndef PMX_ISENSORLISTENER_HPP
#define PMX_ISENSORLISTENER_HPP

#include "IRobotIn.hpp"

namespace pmx
{
    /*!
     * \brief Cette interface représente un listener executée sur la base
     * électronique du moteur.
     */
    class ISensorListener
    {
    public:
        
        /*!
         * \brief Ecoute un listener.
         * \param robotIn
         *        Instance de IRobotIn.
         * \retval true
         *         Si l'éxecution doit être conservée.
         * \retval false
         *         Si le listener doit être supprimé après son execution.
         */
        virtual bool execute(IRobotIn * robotIn) = 0;
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ ISensorListener()
        {}
        
    protected:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ISensorListener()
        {}
    };
};

#endif
