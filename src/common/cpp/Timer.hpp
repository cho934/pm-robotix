/*!
 * \file
 * \brief Définition de la classe Timer (Minuteur).
 * 
 * Cette classe permet de lancer des tâches sur une période donnée.
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
    class Timer: public utils::Thread
    {
    private:
                
        /*!
         * \brief Trace associée à la classe.
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
         *\brief Temps de départ.
         */
        timeval startTime_;
        
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
        
        void inline stop()
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
        
        void runTask();
    };
}

#endif
