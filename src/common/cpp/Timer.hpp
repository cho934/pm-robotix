/*!
 * \file
 * \brief Définition de la classe Timer (Minuteur).
 */

#ifndef PMX_TIMER_H
#define	PMX_TIMER_H

#include <ctime>
#include <sys/time.h>
#include "Chronometer.hpp"
#include "Thread.hpp"
#include "ITimerListener.hpp"
#include "LoggerFactory.hpp"

namespace utils
{
    /*!
     * \brief Cette classe permet de lancer des tâches sur une période donnée (thread utilisé).
     */
    class Timer: public utils::Thread //!\todo utiliser un seul thread pour tous les minuteurs Timer
    {
    private:
                
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref Timer.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("utils::Timer");
            return instance;
        }

    private:
        /*!
         * \brief Interval de temps d'exécution du Minuteur (en ms).
         */
        int timeSpan_;

        /*!
         * \brief Interval minimum de temps du Minuteur (en ms) permettant une interruption.
         * Doit être un multiple de timeSpan_ pour le moment.
         *
         */
        int timeSpanMin_;

        /*!
         *\brief Chronomètre lié au Minuteur.
         */
        Chronometer chrono_;

        /*!
         *\brief Listener lié au Minuteur.
         */
        ITimerListener* listener_;
        
        bool stop_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * Le chronomètre créé n'est pas lancé par le constructeur.
         *
         * \param timeSpanMax Interval de temps d'exécution (en ms).
         * \param timeSpanMin Interval de temps (en ms) permettant une interruption, doit
         * être un multiple de timeSpan_ pour le moment.
         */
        Timer(int timeSpanMax, int timeSpanMin, ITimerListener* listener);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ Timer()
        {}
        
        void inline stopTimer()
        {
            this->stop_ = true;
        }

        /*!
         * \brief Change la fréquence d'appelle du Timer.
         *
         * \param value timeSpan en millisecondes.
         */
        void inline changeTimeSpan(int value)
        {
            this->timeSpan_ = value;
        }
        
    protected:
        /*!
         * \brief Assure le suivi du temps.
         *
         * Cette méthode est exécuter lors du lancement du thread associé à
         * l'objet.
         */
        virtual void execute();
        
        void runTask(Chronometer chrono);
    };
}

#endif
