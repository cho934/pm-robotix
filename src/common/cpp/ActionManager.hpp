/*!
 * \file
 * \brief Définition de la classe ActionManager.
 */

#ifndef PMX_ACTION_MANAGER_HPP
#define PMX_ACTION_MANAGER_HPP

#include "IAction.hpp"
#include "PointerList.hpp"
#include "Thread.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    /*!
     * \brief Classe de gestion des actions du robot.
     */
    class ActionManager: public utils::Thread
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ActionManager.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ActionManager");
            return instance;
        }

        /*!
         * \brief Liste des actions à executer.
         */
        utils::PointerList <IAction*> actions_;
        
        /*!
         * \brief Vaut \c true si le système doit s'arréter.
         * \sa ::stop()
         */
        bool stop_;
        
    protected:
        
        /*!
         * \brief Execute l'ensemble des actions enregistrées.
         */
        virtual void execute();
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ActionManager();
        
        /*!
         * \brief Destructeur de la classe.
         */
        inline virtual ~ ActionManager()
        {}
        
        /*!
         * \brief Retourne le nombre d'actions.
         */
        inline int count() const
        {
            return this->actions_.size();
        }
        
        /*!
         * \brief Ajout d'une action.
         * \param action
         *        L'action à ajouter.
         */
        inline void addAction(IAction * action)
        {
            actions_.push_back(action);
        }

        /*!
         * \brief Vide la liste des actions actuellement enregistrées.
         */
        inline void clearActions()
        {
            actions_.clear();
        }
        
        /*!
         * \brief L'appel à cette méthode signale au thread qu'il doit s'arrêter
         * (proprement).
         *
         * L'utilisation de la méthode ActionManager::finished() permet de
         * savoir si le thread associé est arrêté.
         */
        inline void stop()
        {
            this->stop_ = true;
        }
        
        /*!
         * \brief Affiche via le logger les différentes actions en cours.
         */
        void debug();
    };
};

#endif
