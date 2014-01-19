/*!
 * \file
 * \brief Définition de la classe IRSENSOR.
 */

#ifndef PMX_IRSENSOR_HPP
#define	PMX_IRSENSOR_HPP

#include "ARobotElement.hpp"
#include "Macro.hpp"
#include "IAction.hpp"
#include "ISensorListener.hpp"
#include "LoggerFactory.hpp"
#include "Timer.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe représente un composant Infrarouge de type SHARP GP2.
     *
     */
    class IrSensor : public ARobotElement, utils::ITimerListener
    {
    public:

        /*!
         * \brief Période (en millisecondes).
         */
        static const int PERIOD_IR = 100;
        
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref IrSensor.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::IrSensor");
            return instance;
        }
        
        /*!
         * \brief \c true si la commande d'execution du listener associée est active.
         */
        bool active_;

        /*!
         * \brief \c true lorsque ce listener doit être supprimé de la liste des listeners.
         */
        bool listenerStopped_;

        /*!
         * \brief Pin de l'ADC (0 à 6).
         */
        ushort adcPin_;
        
        /*!
         * \brief type de sensor (30cm, 80cm, 150cm).
         */
        int type_;

        /*!
         * \brief Voltage donné par le composant.
         */
        int voltage_;
        
        /*!
         * \brief Distance mm donné par la conversion.
         */
        double distanceMm_;

        /*!
         * \brief \c true si la donnée est actualisée.
         */
        bool received_;

        /*!
         * \brief \c true si la donnée est actualisée.
         */
        bool freq_;

        /*!
         * \brief \c true quand le capteur a donné au moins une position
         */
        bool initDone;
        
        /*!
         * \brief Timer associé à cette instance.
         */
        utils::Timer timerIrSensor_;
        
        
        public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        IrSensor(pmx::Robot & robot, ushort adcPin, int type);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ IrSensor()
        {
            timerIrSensor_.stopTimer();
        }

        inline void reset()
        {
            logger().info() << "              !! reset !! " << utils::end;
            this->voltage_ = 0;
            this->distanceMm_ = 2000000.0;
            this->received_ = false;
            this->initDone=false;
        }
        
        inline bool active() const
        {
            return active_;
        }
        inline void active(bool active)
        {
            if(!active)
            {
                this->reset();
            }
            this->active_ = active;
        }
        void waitSensor()
        {
            while(!initDone){
                usleep(10*1000);
            }
            initDone=true;
        }

        inline void startTimer()
        {
            this->reset();
            printf(" Thread IrSensor Start. \n");
            this->timerIrSensor_.start();
            //printf("Wait sensor\n");
            logger().info() << "              !! Wait sensor !! " << utils::end;
            this->waitSensor();
            logger().info() << "              !! Wait sensor done !! " << utils::end;
            //printf("Wait sensor done\n");
        }

        inline void stopTimer()
        {
            this->timerIrSensor_.stopTimer();
        }

        /*!
         * \brief Flag le listener comme devant être stoppé.
         */
        inline void stopListener(bool value)
        {
            this->listenerStopped_ = value;
        }
        inline bool stopListener() const
        {
            return listenerStopped_;
        }

        inline int type() const
        {
            return type_;
        }
        
        inline ushort adcPin() const
        {
            return adcPin_;
        }
        
        inline int voltage() const
        {
            return voltage_;
        }
        inline void voltage(int voltage)
        {
            this->voltage_ = voltage;
        }

        inline double distanceMm() const
        {
            return distanceMm_;
        } 
        inline void distanceMm(int distanceMm)
        {
            initDone=true;
            this->distanceMm_ = distanceMm;
        }

        inline bool received() const
        {
            return received_;
        }
        inline void received(bool value)
        {
            this->received_ = value;
        }

        inline int frequency() const
        {
            return freq_;
        }
        /*!
         * \brief change la fréquence de la detection IR.
         *
         * \param value fréquence en millisecondes.
         */
        inline void changeFrequency(int value)
        {
            this->freq_ = value;
            timerIrSensor_.changeTimeSpan(value);
        }

        /*!
         * \brief Ajout le listener de detection d'un objet.
         */
        virtual void getObjectDistance();

        /*!
         * \brief Méthode appelée en fonction du chronometer, à une fréquence donnée.
         * \param timeSpan
         *        Intervalle de temps depuis le dernier appel de cette méthode (en ms).
         */
        void onTimer(utils::Chronometer chrono);


        /*!
         * \brief conversion en mm du voltage donné par le GP2.
         */
        double gp2Convert(int type, int value);
        
    };
    
    
     /*!
     * \brief Ce listener permet de lire la donnée d'un composant Sharp GP2.
     *
     */
    class IrSensorListener: public ISensorListener
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref IrSensorListener.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::IrSensorListener");
            return instance;
        }
        
        /*!
         * \brief Référence vers le contact associé.
         */
        IrSensor & irSensor_;

        /*!
         * \brief nb d'itération.
         */
        int nb_;

    public:     

        /*!
         * \brief Constructeur de la classe.
         * \param contact
         *        Reference vers le IrSensor associé.
         */
        IrSensorListener(IrSensor & irSensor);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ IrSensorListener()
        {}
        
        virtual bool execute(IRobotIn * robotIn);   
    };
};

#endif











