/*!
 * \file
 * \brief Définition de la classe Fork (Fourchette).
 */

#ifndef PMX_FORK_HPP
#define	PMX_FORK_HPP

#include "ARobotElement.hpp"
#include "LoggerFactory.hpp"
#include "IAction.hpp"
#include "Configuration.hpp"
#include "IInitialized.hpp"
#include "Chronometer.hpp"
#include "Macro.hpp"

namespace pmx
{
    /*!
     * \brief Implémentation de la fourchette (version 2012) associée au robot.
     */
    class Fork : public ARobotElement, public IInitialized
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref Clamp.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Fork");
            return instance;
        }

        /*!
         * \brief Numéro du servomotor utilisé.
         */
        int servoNum_;

        /*!
         * \brief Position de la pince; 0:départ; 1:arrivée.
         */
        int state_;

        /*!
         * \brief Valeur servomotor forkHighPosition issue du fichier de configuration.
         */
        int forkHighPosition_;

        /*!
         * \brief Valeur servomotor forkLowPosition issue du fichier de configuration.
         */
        int forkLowPosition_;



        /*!
         * \brief Permet de stopper l'action et qu'elle se termine à la prochaine itération.
         */
        bool actionStopped_;

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        Fork(pmx::Robot & robot, int servoNum);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~Fork()
        {
        }

        inline void stop(bool value)
        {
            this->actionStopped_ = value;
        }

        inline bool stop() const
        {
            return actionStopped_;
        }

        inline int state() const
        {
            return state_;
        }

        inline void state(int state)
        {
            this->state_ = state;
        }

        inline int servoNum() const
        {
            return servoNum_;
        }

        inline void servoNum(int servoNum)
        {
            this->servoNum_ = servoNum;
        }

        inline int forkHighPosition() const
        {
            return forkHighPosition_;
        }

        inline void forkHighPosition(int forkHighPosition)
        {
            this->forkHighPosition_ = forkHighPosition;
        }

        inline int forkLowPosition() const
        {
            return forkLowPosition_;
        }

        inline void forkLowPosition(int forkLowPosition)
        {
            this->forkLowPosition_ = forkLowPosition;
        }



        /*!
         * \brief Initialise les paramètres du robot via un fichier de configuration.
         */
        virtual void initialize(const std::string & prefix, utils::Configuration & configuration);

        /*!
         * \brief Lever la fourchette.
         */
        virtual void goHighPosition();


        /*!
         * \brief Lever la fourchette avec maintien.
         */
        virtual void keepHighPosition();

        /*!
         * \brief Baisser la fourchette.
         */
        virtual void goLowPosition();

        /*!
         * \brief Baisser la fourchette avec maintien.
         */
        virtual void keepLowPosition();
        void waitPositionReached();
    };
    /*!
     * \brief Cette action permet de definir les actions de la pince.
     *
     */
    class ForkAction : public IAction
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ClampAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ForkAction");
            return instance;
        }

        /*!
         * \brief Référence vers la pince associé.
         */
        Fork & fork_;

        /*!
         * \brief libellé de l'action à exécuter.
         */
        ForkActionName action_;

        /*!
         * \brief chronomètre de la pince permettant de définir le temps d'ouverture/fermeture.
         */
        utils::Chronometer chrono_;

        /*!
         * \brief dernier temps issu du chronometre.
         */
        long lastTime_;

        /*!
         * \brief mode d'action
         */
        int mode_;

    public:

        /*!
         * \brief Constructeur de la classe.
         * \param clamp
         *        Reference vers la pince associée.
         */
        ForkAction(Fork & fork, pmx::ForkActionName action);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ForkAction()
        {
        }

        virtual bool execute(IRobotOut * out);

        virtual inline std::string info()
        {
            return "ForkAction";
        }
    };
};

#endif	/* PMX_FORK_HPP */

