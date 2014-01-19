/*!
 * \file
 * \brief Définition de l'interface IAction.
 */

#ifndef PMX_IACTION_HPP
#define PMX_IACTION_HPP

#include <string>
#include "IRobotOut.hpp"

namespace pmx
{
    /*!
     * \brief Cette interface représente une action executée sur la base
     * électronique du moteur.
     */
    class IAction
    {
    public:
        
        /*!
         * \brief Execute une action.
         * \param out
         *        Instance de IRobotOut permettant de fixer les valeurs de
         *        référence du robot.
         * \retval true
         *         Si l'éxecution doit être conservée.
         * \retval false
         *         Si l'action doit être supprimée après son execution.
         */
        virtual bool execute(IRobotOut * out) = 0;
        
        /*!
         * \brief Getter sur les infos permettant d'identifier l'action.
         */
        virtual std::string info() = 0;
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ IAction()
        {}
        
    protected:
        
        /*!
         * \brief Constructeur de la classe.
         */
        IAction()
        {}
    };
};

#endif
