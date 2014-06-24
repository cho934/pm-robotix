/*!
 * \file
 * \brief Définition de la classe StateWaitForStart.
 */

#ifndef PMX_STATEWAITFORSTART_HPP
#define	PMX_STATEWAITFORSTART_HPP

#include "LoggerFactory.hpp"
#include "AAutomateState.hpp"

namespace pmx
{
    /*!
     * \brief Implémente l'attente du commencement du jeu - goupille manuelle.
     */
    class StateWaitForStart : public AAutomateState
    {
    private:

        /*!
         * La trace associée à la classe StateWaitForStart.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::StateWaitForStart");
            return instance;
        }

    public:

        /*!
         * Constructeur de la classe.
         */
        StateWaitForStart()
        {
        }
 virtual std::string name()
        {
            return "StateWaitForStart";
        }
        /*!
         * Destructeur de la classe.
         */
        virtual ~StateWaitForStart()
        {
        }

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
