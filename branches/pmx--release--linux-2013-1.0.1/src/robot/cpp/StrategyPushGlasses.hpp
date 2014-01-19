/*!
 * \file
 * \brief Définition de la classe StrategyPushGlasses.
 */

#ifndef PMX_STRATEGYPUSHGLASSES_HPP
#define	PMX_STRATEGYPUSHGLASSES_HPP

#include "LoggerFactory.hpp"
#include "AAutomateState.hpp"
#include "AStrategy.hpp"
#include "StateDecisionMaker.hpp"


namespace pmx
{
    /*!
     * \brief Implémente la stratégie 1.
     */
    class StrategyPushGlasses : public AStrategy
    {
    private:

        /*!
         * La trace associée à la classe StateOne.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::StrategyPushGlasses");
            return instance;
        }

    public:

        /*!
         * Constructeur de la classe.
         */
        /*!
         * \brief Constructeur de la classe.
         *
         * \param decisionMaker L'instance de décision à rappeler après action
         */
        StrategyPushGlasses(StateDecisionMaker* decisionMaker)
        {
            this->addState("decisionMaker", decisionMaker);
        }

        virtual std::string name()
        {
            return "StrategyPushGlasses";
        }
        /*!
         * Destructeur de la classe.
         */
        virtual ~StrategyPushGlasses()
        {
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
         * \brief Attend le lancement du jeu.
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
        virtual IAutomateState* execute(Robot& robot, void * data);
    };
}


#endif	/* _STRATEGYPUSHGLASSES_HPP */

