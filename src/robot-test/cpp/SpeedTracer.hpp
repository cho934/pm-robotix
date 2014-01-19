/*!
 * \file
 * \brief Définition de la classe SpeedTracer.
 */

#ifndef TEST_SPEEDTRACER_H
#define	TEST_SPEEDTRACER_H

#include "IMotorListener.hpp"
#include "LoggerFactory.hpp"
#include "ITimerListener.hpp"
#include "Motor.hpp"
#include "Chronometer.hpp"
#include "MotorWay.hpp"

namespace test
{
    /*!
     * \brief Trace les informations de vitesse des moteurs.
     *
     * De plus, cette classe calcule et conserve une moyenne des vitesses pour chaque code moteur.
     */
    class SpeedTracer : public pmx::IMotorListener, utils::ITimerListener
    {
    private:
        
        /*!
         * \brief Fréquence de la trace (en millisecondes).
         */
        static const int PERIOD_TIMER = 75;
        
    private:
        
        /*!
         * \brief Moteur associé à ce manager.
         */
        pmx::Motor * motor_;
        
        /*!
         * \brief Temps de référence du dernier front montant (en microsecondes).
         */
        //int lastUp_;
        
        /*!
         * \brief Cumul de temps (en microsecondes) depuis la trace.
         */
        int lastTimeUp_;
        
        /*!
         * \brief Timer compteur de temps passé associé à cette instance.
         */
        utils::Chronometer chronoTime_;
        
        /*!
         * \brief Nombre d'impulsions depuis la création de l'instance.
         */
        unsigned long nbPulses_;
        
        /*!
         * \brief Nombre d'impulsions au dernier pointage.
         */
        unsigned long lastNbPulses_;
        
        /*!
         * \brief Timer associé à cette instance.
         */
        utils::Timer timer_;
        
        /*!
         * \brief Le code moteur actuellement appliqué sur le moteur.
         */
        ushort currentMotorCode_;
        
        /*!
         * \brief Les vitesses moyennes pour chaque code moteur.
         */
        double averageSpeed_[256];
        
        /*!
         * \brief Le nombre de vitesses enregistrées pour le calcul de la moyenne.
         */
        ushort numberSpeed_[256];
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param motor
         *        Moteur associé.
         */
        SpeedTracer(pmx::Motor * motor);
        
    public:
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ SpeedTracer()
        {
            timer_.stop();
            chronoTime_.stop();
        }
        
        inline ushort currentMotorCode() const
        {
            return this->currentMotorCode_;
        }
        
        inline void currentMotorCode(ushort currentMotorCode)
        {
            this->currentMotorCode_ = currentMotorCode;
        }
        
        inline void onLeftPulse(bool value, int time, int nbTests, pmx::MotorWay)
        {
            if(this->motor_->location() == pmx::LEFT)
            {
                onPulse(value, time, nbTests);
            }
        }
        
        inline void onRightPulse(bool value, int time, int nbTests, pmx::MotorWay)
        {
            if(this->motor_->location() == pmx::RIGHT)
            {
                onPulse(value, time, nbTests);
            }
        }
        
        
        /*!
         * \brief Méthode globale de gestion des pulsations.
         * \param value
         *        Type de front.
         * \param time
         *        Temps de référence en microsecondes.
         * \param nbTests
         *        Nombre de tests réalisés depuis le dernier appel.
         */
        void onPulse(bool value, int time, int nbTests);
        
        /*!
         * \brief Méthode appelée en fonction du chronometer, à une fréquence donnée.
         * \param timeSpan
         *        Intervalle de temps depuis le dernier appel de cette méthode (en ms).
         */
        void onTimer(int timeSpan);
        
        /*!
         *\brief Méthode pour calculer les coefficients a et b de la droite y=ax+b du rapport Vitesse/Code moteur.
         */
        void computeApproximation(const utils::Logger & logger);
    };
}

#endif	/* _SPEEDTRACER_H */

