/*!
 * \file
 * \brief Définition de la classe Thread.
 */

#ifndef UTILS_THREAD_HPP
#define UTILS_THREAD_HPP

#include <pthread.h>
#include "ThreadState.hpp"
#include <iostream>
#include <sys/types.h>
#include <sys/syscall.h>

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

        /*!
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
         * \brief l'état du thread.
         */
        ThreadState state_;

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
        virtual inline ~Thread()
        {
        }

        /*!
         * \brief Lancement du thread.
         *
         * Cette méthode initialise le thread et appelle la méthode ::execute().
         */
        bool start();

        /*!
         * \brief Cette méthode retourne l'état du thread.
         *
         * \return l'état du thread.
         */
        inline ThreadState state()
        {
            return state_;
        }

        /*!
         * \brief Indique si le thread est terminé ou pas démarré.
         *
         * \return \c true si le thread est terminé ou simplement créé.
         */
        inline bool finished()
        {
            printf("    finished()\n");
            return (this->state_ == utils::STOPPED || this->state_ == utils::CREATED);
        }


        void debugThread(const char * st)
        {

            pid_t tid;
            tid = syscall(SYS_gettid);
            std::cout << "Thread::"<< st <<":started:" << " : " << tid << std::endl;
        }
    };
}

#endif
