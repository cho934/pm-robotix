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

namespace pmx
{
    /*!
     * \brief Cette classe représente un composant Infrarouge de type SHARP GP2.
     *
     */
    class IrSensor : public ARobotElement
    {
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
        
        public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        IrSensor(pmx::Robot & robot, ushort adcPin, int type);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ IrSensor()
        {}

        inline void reset()
        {
            this->voltage_ = 0;
            this->distanceMm_ = 2000000.0;
            this->received_ = false;
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

        /*!
         * \brief Flag le listener comme devant être stoppé.
         */
        inline void stop(bool value)
        {
            this->listenerStopped_ = value;
        }
        inline bool stop() const
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

        /*!
         * \brief Ajout le listener de detection d'un objet.
         */
        virtual void getObjectDistance();
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











