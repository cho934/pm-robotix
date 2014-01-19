/*!
 * \file
 * \brief Définition de la classe Thread.
 */

#ifndef UTILS_THREAD_HPP
#define UTILS_THREAD_HPP

#include "pthread.h"

namespace utils
{
    /*!
     * \brief Cette classe encapsule l'implémentation des threads.
     *
     * \todo Ajouter les méthodes join() et kill().
     */
    class Thread
    {
    protected:
        
        /**
         * \brief Cette méthode sert de point d'entrée pour l'appel à
         * pcreate_thread.
         *
         * \param object
         *        Instance de Thread qui doit être lancé.
         */
        static void *entryPoint(void *object);
        
    private:
        
        typedef pthread_t ThreadId;
        
        /*!
         * \brief Identifiant du thread lié.
         */
        ThreadId threadId_;
        
        /*!
         * \brief Si \c true le thread est terminé.
         */
        bool finished_;
        
    protected:
        
        /*!
         * \brief Constructeur de la classe.
         */
        Thread();
        
        /*!
         * \brief Cette méthode libère le controle du thread et permet au processus
         * appelant de traiter un autre thread.
         */
        void yield();
        
        /*!
         * \brief L'implementation de cette méthode détaille le traitement
         * réalisé par ce thread.
         */
        virtual void execute() = 0;
        
    public:
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ Thread()
        {}
        
        /*!
         * \brief Lancement du thread.
         *
         * Cette méthode initialise le thread et appelle la méthode ::execute().
         */
        void start();
        
        /*!
         * \brief Cette méthode retourne \c true si le thread associé à cet
         * objet est arrété.
         *
         * \return \c true le thread est terminé.
         */
        inline bool finished()
        {
            return finished_;
        }
    };
}

#endif
