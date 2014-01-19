/*!
 * \file
 * \brief Définition de la classe StateInit.
 */

#ifndef TEST_STATEINIT_HPP
#define	TEST_STATEINIT_HPP

#include "LoggerFactory.hpp"
#include "AAutomateState.hpp"

using namespace pmx;

namespace test
{
    /*!
     * \brief Implémente l'attente du commencement du jeu - goupille manuelle.
     */
    class StateInit : public AAutomateState
    {
    private:

        /*!
         * La trace associée à la classe StateInit.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::StateInit");
            return instance;
        }

    public:

        /*!
         * Constructeur de la classe.
         */
        StateInit()
        {
        }

        virtual std::string name()
        {
            return "StateInit";
        }

        /*!
         * Destructeur de la classe.
         */
        virtual ~StateInit()
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
