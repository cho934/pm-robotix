/*!
 * \file
 * \brief Définition de la classe LedAction.
 */

#ifndef PMX_LEDACTION_HPP
#define	PMX_LEDACTION_HPP

#include "IAction.hpp"

namespace pmx
{
    /*!
     * \brief Cette action envoie un code 255 sur le DM3.
     */
    class LedAction : public pmx::IAction
    {
    private:
        
        /*!
         * \brief Etat actuel de l'action.
         */
        bool stopped;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        LedAction();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ LedAction()
        {}
        
        /*!
         * \brief Execute l'action.
         */
        virtual bool execute(pmx::IRobotOut * out);
        
        /*!
         * \brief Stop l'action.
         */
        inline void stop()
        {
            this->stopped = true;
        }

        virtual inline std::string info()
        {
            return "LedAction";
        }
    };
}

#endif
