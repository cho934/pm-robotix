/*!
 * \file
 * \brief Définition de la classe SpeedManagerFusion qui effectue le calcul de PID et
 * de positionnement des 2 moteurs.
 */

#ifndef PMX_SPEEDMANAGERFUSION_H
#define	PMX_SPEEDMANAGERFUSION_H

#include <ctime>
#include <cmath>
#include "IEncoderListener.hpp"
#include "LoggerFactory.hpp"
#include "Timer.hpp"
#include "PID.hpp"
#include "MotorWay.hpp"
#include "Chronometer.hpp"

namespace pmx
{
    class Base;
    /*!
     * \brief Classe abstraite pour la gestion PID.
     *
     */
    class SpeedManagerFusion : public pmx::IEncoderListener, utils::ITimerListener
    {
    public:

        /*!
         * \brief Période concernant la fréquence d'appel du PID (en millisecondes).
         */
        static const int PERIOD_PID = 100;

    private:

        /*!
         * \brief Trace associée à la classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::SpeedManagerFusion");
            return instance;
        }

        /*!
         * \brief Base associé à ce manager.
         */
        pmx::Base * base_;

        /*!
         * \brief Nombre de tick codeur Gauche depuis la création de l'instance.
         */
        long nbPulsesLeft_;

        /*!
         * \brief Nombre de tick codeur Droit depuis la création de l'instance.
         */
        long nbPulsesRight_;

        /*!
         * \brief Nombre de tick du codeur Gauche au dernier pointage.
         */
        long lastNbPulsesLeft_;

        /*!
         * \brief Nombre de tick du codeur Droit au dernier pointage.
         */
        long lastNbPulsesRight_;

        /*!
         * \brief Timer associé à cette instance.
         */
        utils::Timer timerSMF_;

        /*!
         * \brief PID du moteur Gauche associé à cette instance.
         */
        utils::PID pidLeft_;

        /*!
         * \brief PID du moteur Droit associé à cette instance.
         */
        utils::PID pidRight_;

        /*!
         * \brief PID position du moteur Gauche associé à cette instance.
         */
        utils::PID pidLeftP_;

        /*!
         * \brief PID position du moteur Droit associé à cette instance.
         */
        utils::PID pidRightP_;

        /*!
         * \brief PID du moteur Gauche associé à cette instance.
         */
        utils::PID pidLeftBack_;

        /*!
         * \brief PID du moteur Droit associé à cette instance.
         */
        utils::PID pidRightBack_;

        /*!
         * \brief Paramètre d'activation du Timer associé à cette instance.
         */
        bool ActiveSMF_;

        /*!
         * \brief phase du trapèze de gestion de position. Les valeurs sont
         * 0:arrêt
         * 1:accéleration.
         * 2:saturation vitesse maximum.
         * 3:décéleration.
         * 4:saturation vitesse minimum.
         */
        int rampPhase_;

        /*!
         * \brief Valeurs necessaires pour les calculs de ramp.
         */
        int distTickRampLeftOld_;
        int distTickRampRightOld_;
        int yrampLeft_;
        int yrampRight_;

        int motorCodePidPosLeftOld_;
        int motorCodePidPosRightOld_;
        
        int timeElapsed_;

        bool testPidPos_;

    public:

        /*!
         * \brief Constructeur de la classe.
         * \param base
         *        Base de motorisation associé.
         * \param pidL et pidR
         *        PID exploité pour les corrections de la vitesse moteur gauche et droit.
         */
        SpeedManagerFusion(pmx::Base * base, const utils::PID & pidL, const utils::PID & pidR);

    public:

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~SpeedManagerFusion()
        {
            timerSMF_.stopTimer();
        }

        virtual void onLeftPulse(int motorEncoderValue, int, utils::Chronometer)
        {
            nbPulsesLeft_ += motorEncoderValue;
        }

        virtual void onRightPulse(int motorEncoderValue, int, utils::Chronometer)
        {
            nbPulsesRight_ += motorEncoderValue;
        }

        virtual void initializeSpeedControler(MotorLocation location, const utils::PID & pid)
        {
            if (location == pmx::MLEFT)
            {
                this->pidLeft_ = pid;
            }
            if (location == pmx::MRIGHT)
            {
                this->pidRight_ = pid;
            }
        }

        virtual void initializeSpeedBackControler(MotorLocation location, const utils::PID & pid)
        {
            if (location == pmx::MLEFT)
            {
                this->pidLeftBack_ = pid;
            }
            if (location == pmx::MRIGHT)
            {
                this->pidRightBack_ = pid;
            }
        }

        virtual void initializePositionControler(MotorLocation location, const utils::PID & pid)
        {
            if (location == pmx::MLEFT)
            {
                this->pidLeftP_ = pid;
            }
            if (location == pmx::MRIGHT)
            {
                this->pidRightP_ = pid;
            }
        }

        virtual void startTimer()
        {
            printf(" Thread SPM Start. \n");
            timerSMF_.start();
        }

        virtual void activateSMF()
        {
            ActiveSMF_ = true;
        }

        virtual void desactivateSMF()
        {
            ActiveSMF_ = false;
        }

        virtual void stopTimer()
        {
            this->desactivateSMF();
            timerSMF_.stopTimer();
            logger().debug() << "while before: " << timerSMF_.state() << utils::end;
            while (!timerSMF_.finished())
            {
                logger().debug() << "While: " << timerSMF_.state() << utils::end;

                timerSMF_.stopTimer();
                usleep(20000);
            }
            logger().debug() << "while after: " << timerSMF_.state() << utils::end;
        }

        /*!
         * \brief Reset les variables de
         * PID et d'encodeurs SPM et variables de ramp.
         */
        virtual void reset()
        {
            this->pidLeft_.reset();
            this->pidRight_.reset();
            this->pidLeftP_.reset();
            this->pidRightP_.reset();
            this->pidLeftBack_.reset();
            this->pidRightBack_.reset();

            this->nbPulsesLeft_ = 0;
            this->nbPulsesRight_ = 0;
            this->lastNbPulsesLeft_ = 0;
            this->lastNbPulsesRight_ = 0;

            this->rampPhase_ = 0;
            this->distTickRampLeftOld_ = 3;
            this->distTickRampRightOld_ = 3;
            this->yrampLeft_ = 0;
            this->yrampRight_ = 0;
            this->motorCodePidPosLeftOld_ = 0;
            this->motorCodePidPosRightOld_ = 0;

        }

        void modeTestPidPos(bool value)
        {
            this->testPidPos_ = value;
        }

        /*!
         * \brief Méthode appelée en fonction du chronometer, à une fréquence donnée.
         * \param timeSpan
         *        Intervalle de temps depuis le dernier appel de cette méthode (en ms).
         */
        void onTimer(utils::Chronometer chrono);


        /*!
         * \brief Calcul un arrondi.
         * \todo créer une classe math
         */
        double round(double number)
        {
            return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
        }
    };
}
#endif
