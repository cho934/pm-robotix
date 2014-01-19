/*!
 * \file
 * \brief Définition de la classe SpeedManagerFusion qui effectue le calcul de PID et
 * de positionnement des 2 moteurs.
 */

#ifndef PMX_SPEEDMANAGERFUSION_H
#define	PMX_SPEEDMANAGERFUSION_H

#include <ctime>
#include "IMotorListener.hpp"
#include "LoggerFactory.hpp"
#include "Base.hpp"
#include "Timer.hpp"
#include "PID.hpp"
#include "IInitialized.hpp"
#include "MotorWay.hpp"
#include "Chronometer.hpp"

namespace pmx
{
    class Base;
    
    /*!
     * \brief Classe abstraite pour la gestion PID.
     *
     */
    class SpeedManagerFusion : public pmx::IMotorListener, utils::ITimerListener, IInitialized
    {
    public:
        
        /*!
         * \brief Période concernant la fréquence d'appel du PID (en millisecondes).
         */
        static const int PERIOD_PID = 150;
        
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
         * \brief Temps de référence du dernier front montant (en microsecondes).
         */
        //int lastUp_;
        
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
        virtual inline ~ SpeedManagerFusion()
        {
            timerSMF_.stopTimer();
        }
        
        virtual void onLeftPulse(int value, utils::Chronometer, MotorWay)
        {
            nbPulsesLeft_ += value;
        }

        virtual void onRightPulse(int value, utils::Chronometer, MotorWay)
        {
            nbPulsesRight_ += value;
        }
        
        virtual void initializeSpeedControler(MotorLocation location, const utils::PID & pid)
        {
            if(location == pmx::LEFT)
            {
                this->pidLeft_ = pid;
            }
            if(location == pmx::RIGHT)
            {
                this->pidRight_ = pid;
            }
        }

        virtual void initializeSpeedBackControler(MotorLocation location, const utils::PID & pid)
        {
            if(location == pmx::LEFT)
            {
                this->pidLeftBack_ = pid;
            }
            if(location == pmx::RIGHT)
            {
                this->pidRightBack_ = pid;
            }
        }
        
        virtual void initializePositionControler(MotorLocation location, const utils::PID & pid)
        {
            if(location == pmx::LEFT)
            {
                this->pidLeftP_ = pid;
            }
            if(location == pmx::RIGHT)
            {
                this->pidRightP_ = pid;
            }
        }

       virtual void startTimer()
        {
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
            printf("\nwhile before ");
            while(!timerSMF_.finished())
            {
                //logger().debug() << "While: " << timerSMF_.state() << utils::end;

                timerSMF_.stopTimer();
            }
            logger().debug() << "while after: " << timerSMF_.state() << utils::end;
            printf("\nwhile after ");
        }

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

        }

        /*!
         * \brief Méthode appelée pour prendre les configuration du fichier de configuration.
         * \deprecated
         * \param prefix
         * \param configuration
         */
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration);

        /*!
         * \brief Méthode appelée en fonction du chronometer, à une fréquence donnée.
         * \param timeSpan
         *        Intervalle de temps depuis le dernier appel de cette méthode (en ms).
         */
        void onTimer(utils::Chronometer chrono);
    };
}
#endif
