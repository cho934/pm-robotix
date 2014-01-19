/*!
 * \file
 * \brief Définition de la classe Elevator (Ascenseur version 2011).
 */

#ifndef PMX_ELEVATOR_HPP
#define	PMX_ELEVATOR_HPP

#include "ARobotElement.hpp"
#include "LoggerFactory.hpp"
#include "IAction.hpp"
#include "Macro.hpp"
#include "Chronometer.hpp"

namespace pmx
{
    /*!
     * \brief Implémentation de l'ascenseur (version 2011) associé au robot.
     */
    class Elevator : public ARobotElement
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref Elevator.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Elevator");
            return instance;
        }

        /*!
         * \brief Démultiplexeur de communication.
         */
        ushort dm_;

        /*!
         * \brief Pin du démultiplexeur correspondant à l'activation du moteur de l'ascenseur.
         */
        ushort pinActive_;
        
        /*!
         * \brief Pin du démultiplexeur correspondant au sens de marche.
         */
        ushort pinWay_;

        /*!
         * \brief etat de l'ascenseur; HIGH, LOW, MIDDLE
         */
         ElevatorLocation state_;
         
        /*!
         * \brief Permet de stopper l'action et qu'elle se termine à la prochaine itération.
         */
        bool actionStopped_;

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        Elevator(pmx::Robot & robot, ushort dm, ushort pinactive, ushort pinway);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~Elevator()
        {
            //desactivation des pin de DM pour avoir un accès par les boutons poussoirs.
            this->noPosition();
        }

        inline void stop(bool value)
        {
            this->actionStopped_ = value;
        }
        inline bool stop() const
        {
            return actionStopped_;
        }

        inline ushort dm() const
        {
            return dm_;
        }

        inline ushort pinActive() const
        {
            return pinActive_;
        }
        
        inline ushort pinWay() const
        {
            return pinWay_;
        }

        inline void state(ElevatorLocation state)
        {
            this->state_ = state;
        }
        inline ElevatorLocation state() const
        {
            return state_;
        }

        /*!
         * \brief Monter l'ascenseur en position haute.
         */
        virtual void goHighPosition();

        /*!
         * \brief Monter l'ascenseur en position basse.
         */
        virtual void goLowPosition();

        /*!
         * \brief Monter l'ascenseur en position milieu.
         */
        virtual void goMiddlePosition();

        /*!
         * \brief Monter l'ascenseur en position juste pour que les GP2 puissent voir.
         */
        virtual void goLittlePosition();

        /*!
         * \brief relâche les commandes de l'ascenseur.
         */
        virtual void noPosition();


    };
    /*!
     * \brief Cette action permet de definir les actions de l'ascenseur.
     *
     */
    class ElevatorAction : public IAction
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ElevatorAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ElevatorAction");
            return instance;
        }

        /*!
         * \brief Référence vers la pince associé.
         */
        Elevator & elevator_;

        /*!
         * \brief libellé de l'action à exécuter.
         */
        ElevatorActionName action_;

        /*!
         * \brief chronomètre permettant de définir le temps de fonctionnement.
         */
        utils::Chronometer chrono_;

        /*!
         * \brief mode d'action
         */
        int mode_;

        /*!
         * \brief temps d'attente
         */
        int time_;

    public:

        /*!
         * \brief Constructeur de la classe.
         * \param elevator
         *        Reference vers l'ascenseur associée.
         */
        ElevatorAction(Elevator & elevator, pmx::ElevatorActionName action);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ElevatorAction()
        {  
        }

        virtual bool execute(IRobotOut * out);

        virtual inline std::string info()
        {
            return "ElevatorAction";
        }
    };
};

#endif	/* PMX_ELEVATOR_HPP */

