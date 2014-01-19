/*!
 * \file
 * \brief Définition de la classe SpeedManager.
 */

#ifndef PMX_SPEEDMANAGER_H
#define	PMX_SPEEDMANAGER_H

#include <ctime>
#include "IMotorListener.hpp"
#include "LoggerFactory.hpp"
#include "Motor.hpp"
#include "Timer.hpp"
#include "PID.hpp"
#include "IInitialized.hpp"
#include "MotorWay.hpp"

namespace pmx
{
    class Motor;
    
    /*!
     * \brief Classe abstraite pour le conversion "code moteur - vitesse".
     *
     * Cette classe se base sur les données fournies par les capteurs pour
     * définir le code moteur le plus adapté pour la vitesse actuellement
     * programmée.
     */
    class SpeedManager : public pmx::IMotorListener, utils::ITimerListener, IInitialized
    {
    public:
        
        /*!
         * \brief Distance parcourue par le robot entre deux fronts montants (en millimètre).
         * \todo Regrouper cette constante et celle présente dans la classe PositionManager.
         */
        static const double DISTANCE_PER_UP_PULSE = 1.325343;
        
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
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::SpeedManager");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Initialise une nouvelle instance de cette classe pour un moteur donné.
         *
         * \param motor
         *        Moteur de référence.
         * \param pid
         *        PID à utiliser pour ce moteur.
         * \return Une nouvelle instance de la classe.
         */
        static SpeedManager* createInstance(pmx::Motor * motor, const utils::PID & pid);
        
    private:
        
        /*!
         * \brief Moteur associé à ce manager.
         */
        pmx::Motor * motor_;
        
        /*!
         * \brief Temps de référence du dernier front montant (en microsecondes).
         */
        int lastUp_;
        
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
         * \brief PID associé à cette instance.
         */
        utils::PID pid_;
        
    protected:
        
        /*!
         * \brief Constructeur de la classe.
         * \param motor
         *        Moteur associé.
         * \param pid
         *        PID exploité pour lisser les corrections de la vitesse.
         */
        SpeedManager(pmx::Motor * motor, const utils::PID & pid);
        
    public:
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ SpeedManager()
        {
            timer_.stop();
        }
        
        virtual void onLeftPulse(bool value, int time, int nbTests, MotorWay way) = 0;
        
        virtual void onRightPulse(bool value, int time, int nbTests, MotorWay way) = 0;
        
        virtual void initializeSpeedControler(const utils::PID & pid)
        {
            this->pid_ = pid;
        }
        
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration); 

        /*!
         * \brief Méthode globale de gestion des pulsations.
         * \param value
         *        Type de front.
         * \param time
         *        Temps de référence en microsecondes.
         * \param nbTests
         *        Nombre de tests réalisés depuis le dernier appel.
         */
        void onPulse(bool value, int time, int nbTests, MotorWay way);

        /*!
         * \brief Méthode appelée en fonction du chronometer, à une fréquence donnée.
         * \param timeSpan
         *        Intervalle de temps depuis le dernier appel de cette méthode (en ms).
         */
        void onTimer(int timeSpan);
    };
    
    /*!
     * \brief Classe implémentant la gestion du temps pour le moteur gauche.
     */
    class SpeedManagerLeft : public SpeedManager
    {
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        inline SpeedManagerLeft(pmx::Motor * motor, const utils::PID & pid) : SpeedManager(motor, pid)
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ SpeedManagerLeft()
        {}
        
        virtual inline void onLeftPulse(bool value, int time, int nbTests, MotorWay way)
        {
            onPulse(value, time, nbTests, way);
        }
        
        virtual inline void onRightPulse(bool, int, int, MotorWay)
        {}
    };
    
    /*!
     * \brief Classe implémentant la gestion du temps pour le moteur droit.
     */
    class SpeedManagerRight : public SpeedManager
    {
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        inline SpeedManagerRight(pmx::Motor * motor, const utils::PID & pid) : SpeedManager(motor, pid)
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ SpeedManagerRight()
        {}
        
        virtual inline void onLeftPulse(bool, int, int, MotorWay)
        {}
        
        virtual inline void onRightPulse(bool value, int time, int nbTests, MotorWay way)
        {
            onPulse(value, time, nbTests, way);
        }
    };
}
#endif
