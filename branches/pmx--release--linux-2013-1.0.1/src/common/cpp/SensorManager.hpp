/*!
 * \file
 * \brief Définition de la classe SensorManager.
 */

#ifndef PMX_SENSOR_MANAGER_HPP
#define PMX_SENSOR_MANAGER_HPP

#include "IEncoderListener.hpp"
#include "ISensorListener.hpp"
#include "PointerList.hpp"
#include "Thread.hpp"
#include "LoggerFactory.hpp"
#include "Chronometer.hpp"
#include "Mutex.hpp"

namespace pmx
{
    /*!
     * \brief Classe de gestion des capteurs du robot.
     *
     * Actuellement La classe SensorManager assure la récupération des 'fronts'
     * sur les capteurs associés aux moteurs. A chaque fois qu'un front est
     * détecté, la méthode onXXXPulse() de tous les listeners associés est
     * appelée.
     */
    class SensorManager: public utils::Thread
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref SensorManager.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::SensorManager");
            return instance;
        }
        
        /*!
         * \brief Cette liste contient l'ensemble des listeners enregistrés (impulsions du moteur).
         */
        utils::PointerList <IEncoderListener*> encoderListeners_;
        
        /*!
         * \brief Cette liste contient l'ensemble des listeners enregistrés (capteurs).
         */
        utils::PointerList <ISensorListener*> sensorListeners_;
               
        
        /*!
         * \brief Vaut true si le système doit s'arréter.
         * \sa ::stop()
         */
        bool stop_;

        /*!
         * \brief Activation du signal de notification concernant les impulsions.
         */
        bool firePulseEnabled_;

        /*!
         * \brief Chronometre de debuggage.
         */
        utils::Chronometer chrono_;

    protected:
        
        /*!
         * \brief Choisi la méthode de gestion des capteurs enregistrées :
         * blocante ou non blocante.
         *
         * Cette méthode est exécutée lors du lancement du thread associé à
         * l'objet.
         */
        virtual void execute();

        /*!
         * \brief Assure la gestion des capteurs enregistrées dans le cas
         * d'utilisation du port parallèle, lecture de données non blocante
         * (pour les capteurs enregistrés).
         *
         */
        virtual void executeWithNoBlockingRead();

        
        /*!
         * \brief Cette méthode signale à tous les listeners qu'une ou plusieurs impulsions
         * a été reçue venant des codeurs gauche.
         *
         * \param value La valeur du nb d'impulsions du codeur gauche lié au moteur.
         * \param value La valeur du nb d'impulsions du codeur gauche lié au sol et indépendant des moteurs.
         * \param chono Temps de référence en microsecondes.
         */
        void fireLeftPulse(int motorEncoderValue, int freeEncoderValue,  utils::Chronometer chrono);
        
        /*!
         * \brief Cette méthode signale à tous les listeners qu'une ou plusieurs impulsions
         * a été reçue venant des codeurs droit.
         *
         * \param value La valeur du nb d'impulsions du codeur droit lié au moteur.
         * \param value La valeur du nb d'impulsions du codeur droit lié au sol et indépendant des moteurs.
         * \param chrono Temps de référence en microsecondes.
         */
        void fireRightPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer chrono);
        
    public:
        /*!
         * Constructeur de la classe.
         */
        SensorManager();
        
        /*!
         * Destructeur de la classe.
         */
        inline virtual ~ SensorManager()
        {}
        
        /*!
         * \brief Ajout d'un listener sur le sensorManager.
         * \param listener
         *        Listener à ajouter.
         */
        inline void addListener(IEncoderListener * listener)
        {
            logger().debug("A new listener is added");
            lock();
            this->encoderListeners_.push_back(listener);
            unlock();
        }
        
        /*!
         * \brief Ajout d'un listener sur les capteurs.
         * \param listener
         *        Listener à ajouter.
         */
        inline void addListener(ISensorListener * listener)
        {
            logger().debug("A new ISensorListener is added");
            lock();
            this->sensorListeners_.push_back(listener);
            unlock();
        }
        
        /*!
         * \brief L'appelle à cette méthode signale au thread qu'il doit
         * s'arrêter (proprement).
         *
         * L'utilisation de la méthode ::finished() permet de savoir si le
         * thread associé est arrêté.
         */
        inline void stop()
        {
            this->stop_ = true;
        }

        /*!
         * affecte la valeur.
         */
        inline void firePulseEnabled(bool value)
        {
            this->firePulseEnabled_ = value;
        }

        /*!
         * retourne la valeur.
         */
        inline bool firePulseEnabled()
        {
            return this->firePulseEnabled_;
        }
    };
}

#endif
