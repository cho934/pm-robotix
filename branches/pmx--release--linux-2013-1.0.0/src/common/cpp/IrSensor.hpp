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
    public:

       
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

        void reset();
       
    };   
};

#endif
