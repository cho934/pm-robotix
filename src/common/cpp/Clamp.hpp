/*!
 * \file
 * \brief Définition de la classe Clamp (Pince).
 */

#ifndef PMX_CLAMP_HPP
#define	PMX_CLAMP_HPP

#include "ARobotElement.hpp"
#include "LoggerFactory.hpp"
#include "IAction.hpp"
#include "Configuration.hpp"
#include "IInitialized.hpp"
#include "Macro.hpp"
#include "Chronometer.hpp"

namespace pmx
{
    /*!
     * \brief Implémentation de la pince (version 2011) associée au robot.
     */
    class Clamp : public ARobotElement, public IInitialized
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ActionManager.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Clamp");
            return instance;
        }

        /*!
         * \brief Position de la pince; 0:fermée; 1:ouverte.
         */
        int stateOpened_;

        int clampLeftWideOpened_;
        int clampRightWideOpened_;

        int clampLeftMediumOpened_;
        int clampRightMediumOpened_;

        int clampLeftLittleOpened_;
        int clampRightLittleOpened_;

        int clampLeftClosed_;
        int clampRightClosed_;

        /*!
         * \brief Permet de stopper l'action et qu'elle se termine à la prochaine itération.
         */
        bool actionStopped_;

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        Clamp(pmx::Robot & robot);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~Clamp()
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

        inline int stateOpened() const
        {
            return stateOpened_;
        }
        inline void stateOpened(int stateOpened)
        {
            this->stateOpened_ = stateOpened;
        }

        inline int clampLeftWideOpened() const
        {
            return clampLeftWideOpened_;
        }
        inline void clampLeftWideOpened(int clampLeftWideOpened)
        {
            this->clampLeftWideOpened_ = clampLeftWideOpened;
        }

        inline int clampRightWideOpened() const
        {
            return clampRightWideOpened_;
        }

        inline void clampRightWideOpened(int clampRightWideOpened)
        {
            this->clampRightWideOpened_ = clampRightWideOpened;
        }

        inline int clampLeftClosed() const
        {
            return clampLeftClosed_;
        }
        inline void clampLeftClosed(int clampLeftClosed)
        {
            this->clampLeftClosed_ = clampLeftClosed;
        }

        inline int clampRightClosed() const
        {
            return clampRightClosed_;
        }
        inline void clampRightClosed(int clampRightClosed)
        {
            this->clampRightClosed_ = clampRightClosed;
        }

        /*!
         * \brief Initialise les paramètres du robot via un fichier de configuration.
         */
        virtual void initialize(const std::string & prefix, utils::Configuration & configuration);

        /*!
         * \brief Ouvrir en grand les pinces.
         */
        virtual void openWidePosition();

        /*!
         * \brief Ouvre la pince sur une position intermédiaire.
         */
        virtual void openMediumPosition();

        /*!
         * \brief Dessérer les bras de la pince.
         */
        virtual void openLittlePosition();

        /*!
         * \brief Fermer la pince en gardant le maintien.
         */
        virtual void keepClose();

        /*!
         * \brief Fermer la pince sans garder le maintien.
         */
        virtual void close();

    };
    /*!
     * \brief Cette action permet de definir les actions de la pince.
     *
     */
    class ClampAction : public IAction
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ClampAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ClampAction");
            return instance;
        }

        /*!
         * \brief Référence vers la pince associé.
         */
        Clamp & clamp_;

        /*!
         * \brief libellé de l'action à exécuter.
         */
        ClampActionName action_;

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
        ClampAction(Clamp & clamp, pmx::ClampActionName action);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ClampAction()
        {}

        virtual bool execute(IRobotOut * out);

        virtual inline std::string info()
        {
            return "ClampAction";
        }
    };
};

#endif	/* PMX_CLAMP_HPP */

