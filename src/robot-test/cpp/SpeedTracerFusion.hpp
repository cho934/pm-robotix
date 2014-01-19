/*!
 * \file
 * \brief Définition de la classe SpeedTracerFusion.
 */

#ifndef TEST_SPEEDTRACERFUSION_H
#define	TEST_SPEEDTRACERFUSION_H

#include "IEncoderListener.hpp"
#include "LoggerFactory.hpp"
#include "ITimerListener.hpp"
#include "Motor.hpp"
#include "Base.hpp"
#include "Chronometer.hpp"
#include "MotorWay.hpp"

namespace test
{
    /*!
     * \brief Trace les informations de vitesse des moteurs.
     *
     * De plus, cette classe calcule et conserve une moyenne des vitesses pour chaque code moteur.
     * Permet de déterminer la courbe vitesse/codemoteur y=ax+b
     */
    class SpeedTracerFusion : public pmx::IEncoderListener, utils::ITimerListener
    {
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref SpeedTracerFusion.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::SpeedTracerFusion");
            return instance;
        }

        /*!
         * \brief Fréquence de la trace (en millisecondes).
         * Mettre la même période que la boucle du programme RobotMoveByIncrementTest.
         */
        static const int PERIOD_TIMER = 50;
        
    private:
        
        /*!
         * \brief Base associé à ce manager.
         */
        pmx::Base * base_;
        
        /*!
         * \brief Cumul de temps (en microsecondes) depuis la trace.
         */
        int lastTimeUp_;
        
        /*!
         * \brief Chronometre : compteur de temps passé associé à cette instance.
         */
        utils::Chronometer chronoTime_;
        
        /*!
         * \brief Nombre d'impulsions depuis la création de l'instance.
         */
        long nbPulsesLeft_;

        long nbPulsesRight_;
        
        /*!
         * \brief Nombre d'impulsions au dernier pointage.
         */
        long lastNbPulsesLeft_;

        long lastNbPulsesRight_;
        
        /*!
         * \brief Timer associé à cette instance.
         */
        utils::Timer timerStf_;
        
        /*!
         * \brief Le code moteur actuellement appliqué sur le moteur.
         */
        ushort currentMotorCodeLeft_;
        
        ushort currentMotorCodeRight_;

        /*!
         * \brief Les vitesses moyennes pour chaque code moteur.
         */
        double averageSpeedLeft_[128];
        double averageSpeedRight_[128];

        /*!
         * \brief Le nombre de vitesses enregistrées pour un motorCode pour le calcul de la moyenne.
         */
        ushort numberSpeedLeft_[128];
        ushort numberSpeedRight_[128];

    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param motor
         *        Moteur associé.
         */
        SpeedTracerFusion(pmx::Base * base);
        
    public:
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ SpeedTracerFusion()
        {
            timerStf_.stopTimer();
            chronoTime_.stop();
        }
        
        inline ushort currentMotorCodeLeft() const
        {
            return this->currentMotorCodeLeft_;
        }
        
        inline void currentMotorCodeLeft(ushort currentMotorCode)
        {
            this->currentMotorCodeLeft_ = currentMotorCode;
        }

        inline ushort currentMotorCodeRight() const
        {
            return this->currentMotorCodeRight_;
        }

        inline void currentMotorCodeRight(ushort currentMotorCode)
        {
            this->currentMotorCodeRight_ = currentMotorCode;
        }
        
        inline void onLeftPulse(int motorEncoderValue, int, utils::Chronometer)
        {
            nbPulsesLeft_+=motorEncoderValue;
        }
        
        inline void onRightPulse(int motorEncoderValue, int, utils::Chronometer)
        {
            nbPulsesRight_+=motorEncoderValue;
        }

        /*!
         * \brief Méthode appelée en fonction du chronometer, à une fréquence donnée.
         * \param timeSpan
         *        Intervalle de temps depuis le dernier appel de cette méthode (en ms).
         */
        void onTimer(utils::Chronometer chrono);
        
        /*!
         *\brief Méthode pour calculer les coefficients a et b de la droite y=ax+b du rapport Vitesse/Code moteur.
         */
        void computeApproximation(const utils::Logger & logger);
    };
}

#endif	/* _SPEEDTRACERFUSION_H */

