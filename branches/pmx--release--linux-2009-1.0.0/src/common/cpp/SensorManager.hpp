/*!
 * \file
 * \brief Définition de la classe SensorManager.
 */

#ifndef PMX_SENSOR_MANAGER_HPP
#define PMX_SENSOR_MANAGER_HPP

#include "IMotorListener.hpp"
#include "ISensorListener.hpp"
#include "PointerList.hpp"
#include "Thread.hpp"
#include "LoggerFactory.hpp"
#include "Chronometer.hpp"

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
        
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::SensorManager");
            return instance;
        }
        
        /*!
         * \brief Cette liste contient l'ensemble des listeners enregistrés (impulsions du moteur).
         */
        utils::PointerList <IMotorListener*> motorListeners_;
        
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
         * \brief Dernier état connu de la pulsation gauche.
         */
        bool leftPulseState_;
        
        /*!
         * \brief Dernier état connu de la pulsation droite.
         */
        bool rightPulseState_;
        
        /*!
         * \brief Objet servant pour le chronométrage des impulsions.
         */
        utils::Chronometer chronometer_;
        
    protected:
        
        /*!
         * \brief Assure la gestion des capteurs enregistrées.
         *
         * Cette méthode est exécuter lors du lancement du thread associé à
         * l'objet.
         */
        virtual void execute();
        
        /**
         * \brief Cette méthode signale à tous les listeners qu'une pulsation
         * a été reçue pour le moteur gauche.
         * \param value La valeur de la pulsation.
         * \param time Temps de référence en microsecondes.
         * \param nbTests Nombre de tests réalisés depuis le dernier appel.
         */
        void fireLeftPulse(bool value, int time, int nbTests, MotorWay way);
        
        /**
         * \brief Cette méthode signale à tous les listeners qu'une pulsation
         * a été reçue pour le moteur droit.
         * \param value La valeur de la pulsation.
         * \param time Temps de référence en microsecondes.
         * \param nbTests Nombre de tests réalisés depuis le dernier appel.
         */
        void fireRightPulse(bool value, int time, int nbTests, MotorWay way);
        
    public:
        /*!
         * Constructeur de la classe.
         */
        SensorManager();
        
        /**
         * Destructeur de la classe.
         */
        inline virtual ~ SensorManager()
        {}
        
        /*!
         * \brief Ajout d'un listener sur les impulsions des moteurs.
         * \param listener
         *        Listener à ajouter.
         */
        inline void addListener(IMotorListener * listener)
        {
            logger().debug("A new listener is added");
            this->motorListeners_.push_back(listener);
        }
        
        /*!
         * \brief Ajout d'un listener sur les capteurs.
         * \param listener
         *        Listener à ajouter.
         */
        inline void addListener(ISensorListener * listener)
        {
            logger().debug("A new ISensorListener is added");
            this->sensorListeners_.push_back(listener);
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
    };
}

#endif
