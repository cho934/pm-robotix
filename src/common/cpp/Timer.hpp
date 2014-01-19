/*!
 * \file
 * \brief Définition de la classe Timer (Minuteur).
 */

#ifndef PMX_TIMER_H
#define	PMX_TIMER_H

#include "sys/time.h"
#include <ctime>
#include "Chronometer.hpp"
#include "Thread.hpp"
#include "ITimerListener.hpp"
#include "LoggerFactory.hpp"

namespace utils
{
    /*!
     * \brief Cette classe permet de lancer des tâches sur une période donnée (thread utilisé).
     */
    class Timer: public utils::Thread
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
         * \brief Interval de temps du Minuteur.
         */
        int timeSpan_;

        /*!
         *\brief Chronomtètre lié au Minuteur.
         */
        Chronometer chrono_;
        
        ITimerListener* listener_;
        
        bool stop_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * Le chronomètre créé n'est pas lancé par le constructeur.
         */
        Timer(int timeSpan, ITimerListener* listener);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ Timer()
        {}
        
        void inline stopTimer()
        {
            this->stop_ = true;
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
