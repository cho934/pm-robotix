/*!
 * \file
 * \brief Définition de la classe Chronometer.
 */

#ifndef PMX_CHRONOMETER_H
#define	PMX_CHRONOMETER_H

#include "sys/time.h"
#include <ctime>

namespace utils
{
    /*!
     * \brief Gestion d'un chronomètre.
     *
     * Cette précision de ce chronomètre est de l'ordre de la microseconde.
     * Son fonctionnement est 'basique' :
     * - il est lancé via la méthode start(),
     * - il est arrété via la méthode stop().
     * - Les méthodes getElapsedTimeXXX() retournent le temps associé au compteur.
     *
     * Remarques :
     * Les appels successifs à start() réinitialise le chronomètre.
     * Le constructeur initialise un chronomètre mais ne le lance pas.
     *
     * \todo Renommer en Chronometer.
     */
    class Chronometer
    {
    public:
        static timeval getTime();   
        
    private:
        /*!
         * \brief Stop Flag.
         */
        int stopped_;
        
        /*!
         * \brief Variable de comptage de début.
         */
        timeval startCount_;
        
        /*!
         * \brief Variable de comptage de fin.
         */
        timeval endCount_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * Le chronomètre créé n'est pas lancé par le constructeur.
         */
        Chronometer();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ Chronometer()
        {}
        
        /*!
         * \return \c true si le chronometer est démarré.
         */
        inline bool started()
        {
            return ! stopped_;
        }
        
        /*!
         * \brief Lance le chronomètre.
         */
        void start();
        
        /*!
         * \brief Arrete le chronomètre.
         */
        void stop();
        
        /*!
         * \brief Un alias pour la méthode getElapsedTimeInSec().
         * \return Le temps en seconde.
         */
        double getElapsedTime();
        
        /*!
         * \return Le temps du chronomètre en seconde.
         */
        double getElapsedTimeInSec();
        
        /*!
         * \return Le temps du chronomètre en milliseconde.
         */
        double getElapsedTimeInMilliSec();
        
        /*!
         * \return Le temps du chronomètre en microseconde.
         */
        long getElapsedTimeInMicroSec();
    };
}
#endif
