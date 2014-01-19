#ifndef UTILS_MUTEX_H
#define	UTILS_MUTEX_H

#include "pthread.h"

namespace utils
{
    class Mutex
    {
    private:
        
        /*!
         * \brief Reference du mutex associé.
         */
        pthread_mutex_t mutex_;
        
    protected:
        
        /*!
         * \brief Constructeur de la classe.
         */
        Mutex();
        
    public:
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ Mutex()
        {
            pthread_mutex_destroy(& mutex_);
        }
        
        /*!
         * \brief Verrouille le mutex.
         * Cette méthode doit être appelée avant d'utiliser la ressource associée.
         * Si le mutex est déjà verrouillée, cette méthode attend qu'il se libère.
         */
        void lock();
        
        /*!
         * \brief Déverrouille le mutex.
         * Cette méthode doit être appelée après avoir utiliser la ressource associée.
         */
        void unlock();
        
        /*!
         * \brief Essaie de verrouiller le mutex.
         * \return \c true si le lock a pu être posée.
         */
        bool tryLock();
    };
}

#endif
