#ifndef PMX_AUTOMATE_H
#define	PMX_AUTOMATE_H

#include "IAutomateState.hpp"
#include "Robot.hpp"

namespace pmx
{
    /*!
     * \brief Gere un automate simple.
     *
     * Un automate "simple" ne possede au plus qu'un état actif. Il n'est donc
     * pas possible de gérer un enbranchement avec cette classe.
     */
    class Automate
    {
    private:
        
        /*!
         * Etat courant de l'automate.
         */
        IAutomateState* current_;
        
    public:
        /*!
         * \brief Constructeur de la classe.
         */
        Automate();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ Automate()
        {
            this->current(NULL);
        }
        
        /*!
         * \brief Lance l'automate.
         *
         * L'automate n'est PAS lancé sur un nouveau thread, cette méthode est
         * donc bloquante pour le processus actuel.
         *
         * \param robot
         *        Le robot à manipuler.
         * \param first
         *        Etat initial de l'automate.
         */
        void run(Robot& robot, IAutomateState* first);
        
    protected:
        
        inline IAutomateState* current() const
        {
            return this->current_;
        }
        
        inline void current(IAutomateState* current)
        {
            if (this->current_ != NULL)
            {
                delete this->current_;
            }
            this->current_ = current;
        }
    };
}

#endif
