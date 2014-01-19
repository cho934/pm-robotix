/*!
 * \file
 * \brief Définition de la classe StrategyTwo.
 */

#ifndef TEST_STRATEGYTWO_HPP
#define	TEST_STRATEGYTWO_HPP

#include "LoggerFactory.hpp"
#include "AAutomateState.hpp"
#include "AStrategy.hpp"
#include "StateDecisionMaker.hpp"

using namespace pmx;

namespace test
{
    /*!
     * \brief Implémente la stratégie 2.
     */
    class StrategyTwo : public AStrategy
    {
    private:

        /*!
         * La trace associée à la classe StateWaitForStart.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::StrategyTwo");
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
        StrategyTwo(StateDecisionMaker* decisionMaker)
        {
            this->addState("decisionMaker", decisionMaker);
        }

        virtual std::string name()
        {
            return "StrategyTwo";
        }

        /*!
         * Destructeur de la classe.
         */
        virtual ~StrategyTwo()
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

#endif
