/*!
 * \file
 * \brief Définition de la classe LedBar.
 */
#ifndef PMX_LEDBAR_HPP
#define	PMX_LEDBAR_HPP

#include "ARobotElement.hpp"
#include "LoggerFactory.hpp"
#include "LoggerFactory.hpp"
#include "IAction.hpp"
#include "Macro.hpp"
#include "Chronometer.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe permet d'interagir avec la série de 8 leds sur la
     * carte de demultiplexage.
     *
     */
    class LedBar : public ARobotElement
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref LedBar.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::LedBar");
            return instance;
        }
        /*!
         * \brief demultipexeur surlequel la ledbar est connectée.
         */
        ushort dm_;

        /*!
         * \brief Permet de stopper l'action et qu'elle se termine à la prochaine itération des actions.
         */
        bool actionStopped_;

        /*!
         * \brief Permet de savoir si une action est en cours.
         */
        bool actionRunning_;

        /*!
         * \brief Position de la led.
         */
        ushort position_;

        /*!
         * \brief Statut de la led a appliquer.
         */
        bool status_;

        /*!
         * \brief Nombre de clignotement à faire.
         */
        uint nb_;

        /*!
         * \brief Temps de pause (en us).
         */
        uint timeus_;

        /*!
         * \brief Première Valeur de clignotement.
         */
        uint hex_;

        /*!
         * \brief 2ème valeur de clignotement.
         */
        uint hexNext_;


        
    public:
        /*!
         * \brief Constructeur de la classe.
         */
        LedBar(pmx::Robot & robot, ushort dm);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~LedBar()
        {
        }

        inline ushort dm() const
        {
            return dm_;
        }
        
        inline void stop(bool value)
        {
            this->actionStopped_ = value;
        }
        inline bool stop() const
        {
            return actionStopped_;
        }
        inline void stopAndWait(bool value)
        {
            this->actionStopped_ = value;
            while(this->actionRunning_) {usleep(1000);}
        }

        inline void actionRunning(bool value)
        {
            this->actionRunning_ = value;
        }
        inline bool actionRunning() const
        {
            return actionRunning_;
        }

        inline void position(ushort value)
        {
            this->position_ = value;
        }
        inline ushort position() const
        {
            return position_;
        }

        inline void status(bool value)
        {
            this->status_ = value;
        }
        inline bool status() const
        {
            return status_;
        }

        inline void nb(uint value)
        {
            this->nb_ = value;
        }
        inline uint nb() const
        {
            return nb_;
        }

        inline void timeus(uint value)
        {
            this->timeus_ = value;
        }
        inline uint timeus() const
        {
            return timeus_;
        }

        inline void hexValue(uint value)
        {
            this->hex_ = value;
        }
        inline uint hexValue() const
        {
            return hex_;
        }

        inline void hexValueNext(uint value)
        {
            this->hexNext_ = value;
        }
        inline uint hexValueNext() const
        {
            return hexNext_;
        }

        /*!
         * \brief Change le statut d'une led.
         * 
         * \param position La position de la led (de 0 à 7).
         * \param status Le statut de la led.
         */
        void set(ushort position, bool status);

        /*!
         * \brief allume les leds à la "K2000".
         */
        void startK2Mil(uint nb, uint timeus, bool wait);

        /*!
         * \brief Allume toutes les leds.
         */
        void flash();

        /*!
         * \brief Allume les leds selon la valeur hexValue.
         */
        void flashValue(uint hexValue);

        /*!
         * \brief Clignote toutes les leds nb fois tous les timeus.
         */
        void startBlink(uint nb, uint timeus, bool wait);
        void startBlinkPin(int position, uint nb, uint timeus, bool wait);

        /*!
         * \brief Alterne les leds selon la valeur hexValue et hexValueNext.
         * Doit être stoppé par stop.
         */
        void startAlternate(uint nb, uint timeus, uint hexValue, uint hexValueNext, bool wait);

        /*!
         * \brief Eteint toutes les leds.
         */
        void reset();

        /*!
         * \brief Active une led spécifique.
         * \param position La position de la led (de 0 à 7).
         */
        inline void setOn(ushort position)
        {
            this->set(position, true);
        }

        /*!
         * \brief Désactive une led spécifique.
         * \param position La position de la led (de 0 à 7).
         */
        inline void setOff(ushort position)
        {
            this->set(position, false);
        }

    };

    /*!
     * \brief Cette action permet de definir les actions de la barre de leds.
     *
     */
    class LedBarAction : public IAction
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref LedBarAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::LedBarAction");
            return instance;
        }

        /*!
         * \brief Référence vers la pince associé.
         */
        LedBar & ledBar_;

        /*!
         * \brief libellé de l'action à exécuter.
         */
        LedBarActionName action_;

        utils::Chronometer chrono_;

        long lastTime_;

        uint i_;

        uint j_;

        uint k_;

        bool inc_;

    public:

        /*!
         * \brief Constructeur de la classe.
         * \param clamp
         *        Reference vers la pince associée.
         */
        LedBarAction(LedBar & ledBar, pmx::LedBarActionName action);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~LedBarAction()
        {}

        virtual bool execute(IRobotOut * out);

        virtual inline std::string info()
        {
            return "LedBarAction";
        }
    };

}

#endif	/* PMX_LEDBAR_HPP */

