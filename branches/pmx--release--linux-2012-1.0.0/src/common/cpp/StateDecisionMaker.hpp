/*!
 * \file
 * \brief Définition de la classe StateDecisionMaker.
 */

#ifndef PMX_STATEDECISIONMAKER_HPP
#define	PMX_STATEDECISIONMAKER_HPP

#include "AAutomateState.hpp"
#include "Robot.hpp"
#include "AStrategy.hpp"
#include "PointerList.hpp"

namespace pmx
{
    /*!
     * \brief Définit la logique de réflexion pour la gestion du robot.
     */
    class StateDecisionMaker : public AAutomateState
    {
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref StateDecisionMaker.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::StateDecisionMaker");
            return instance;
        }

        /*!
         * \brief Liste des stratégies disponibles.
         */
        utils::PointerList <AStrategy*> strategies_;

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        StateDecisionMaker()
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        inline virtual ~StateDecisionMaker()
        {
        }

        /*!
         * \brief Traite l'état actuel et renvoie l'état suivant.
         *
         * Cette méthode doit être bloquante pour le processus et ne retourner
         * un résultat qu'une fois l'une de ses transitions actives.
         *
         * \param robot
         *        Le robot à manipuler.
         * \param data
         *        Les données associées à l'execution de l'automate.
         * \return L'état suivant ou \c NULL si la fin de l'automate est atteinte.
         */
        virtual IAutomateState* execute(Robot & robot, void * data);

        /*!
         * \brief Ajoute une stratégie.
         *
         * \param strategy La stratégie à ajouter
         */
        inline void addStrategy(AStrategy * strategy)
        {
            this->strategies_.push_back(strategy);
        }
       virtual std::string name()
        {
            return "StateDecisionMaker";
        }
    };
}

#endif
