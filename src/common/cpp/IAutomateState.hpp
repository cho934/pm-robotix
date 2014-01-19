#ifndef PMX_IAUTOMATESTATE_HPP
#define	PMX_IAUTOMATESTATE_HPP

namespace pmx
{
    class Robot;
    
    /*!
     * \brief Définit l'état d'un automate.
     *
     * Un état posséde une méthode execute() qui va effectuer la ou les opérations
     * associés à l'état de l'automate et retourner l'état suivant.
     *
     * \see pmx::Automate
     */
    class IAutomateState
    {
    public:
        
        /*!
         * \brief Traite l'état actuel et renvoie l'état suivant.
         *
         * Cette méthode doit être bloquante pour le processus et ne retourner
         * un résultat qu'une fois l'une de ses transitions actives.
         *
         * \param robot
         *        Le robot à manipuler.
         * \return L'état suivant ou \c NULL si la fin de l'automate est atteinte.
         */
        virtual IAutomateState* execute(Robot & robot) =0;
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ IAutomateState()
        {}
        
    protected:
        
        /*!
         * \brief Constructeur de la classe.
         */
        IAutomateState()
        {}
    };
}

#endif
