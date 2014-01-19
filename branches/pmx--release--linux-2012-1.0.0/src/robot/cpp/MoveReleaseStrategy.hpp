/*!
 * \file
 * \brief Définition de la classe MoveReleaseStrategy.
 */

#ifndef PMX_MOVERELEASESTRATEGY_HPP
#define PMX_MOVERELEASESTRATEGY_HPP

#include "AAutomateState.hpp"
#include "AStrategy.hpp"
#include "StateDecisionMaker.hpp"

namespace pmx
{
    /*!
     * \brief Implémente une stratégie d'approche d'un point clef du plateau
     * et le dépôt d'un élément.
     */
    class MoveReleaseStrategy : public AStrategy
    {
    private:

        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::MoveReleaseStrategy");
            return instance;
        }
    public:

        /*!
         * \brief Constructeur de la classe.
         *
         * \param decisionMaker L'instance de décision à rappeler après action
         */
        MoveReleaseStrategy(StateDecisionMaker* decisionMaker)
        {
            this->addState("decisionMaker", decisionMaker);
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~MoveReleaseStrategy()
        {
        }
        virtual std::string name()
        {
            return "MoveReleaseStrategy";
        }
        /*!
         * \brief Calcul l'interet de cette stratégie.
         *
         * \param robot
         *        Le robot à manipuler.
         * \param data
         *        Les données associées à l'execution de l'automate.
         * \return L'interêt de la stratégie par rapport à l'état actuel du robot.
         */
        virtual int computeInterest(const Robot& robot, void * data);

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
    };
}

#endif
