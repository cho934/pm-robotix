/*!
 * \file
 * \brief Définition de la classe IRSENSORSGROUP.
 */

#ifndef PMX_IRSENSORSGROUP_HPP
#define	PMX_IRSENSORSGROUP_HPP

#include "ARobotElement.hpp"
#include "IrSensor.hpp"
#include "Macro.hpp"
#include "IAction.hpp"
#include "LoggerFactory.hpp"
#include "Timer.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe représente un ensemble de composant IR.
     *
     */
    class IrSensorsGroup : public ARobotElement, utils::ITimerListener
    {
    public:

        /*!
         * \brief Période (en millisecondes).
         */
        static const int PERIOD_IR = 100;
        
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref IrSensorsGroup.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::IrSensorsGroup");
            return instance;
        }
       
        /*!
         * \brief Timer associé à cette instance (un pour tous les IrSensor).
         */
        utils::Timer timerIrSensorGroup_;

        /*!
         * \brief \c true quand le temps d'initialisation a été atteint.
         */
        bool initDone_;

        /*!
         * \brief Capteur gauche de type \ref IrSensor.
         */
        pmx::IrSensor irLeft_;

        /*!
         * \brief capteur centre de type \ref IrSensor.
         */
        pmx::IrSensor irCenter_;

        /*!
         * \brief Capteur droit de type \ref IrSensor.
         */
        pmx::IrSensor irRight_;

        /*!
         * \brief capteur centre de type \ref IrSensor.
         */
        pmx::IrSensor irRearCenter_;

        
        public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        IrSensorsGroup(pmx::Robot & robot);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ IrSensorsGroup()
        {
            timerIrSensorGroup_.stopTimer();
        }

        /*!
         * \brief change la fréquence de la detection IR.
         *
         * \param value période en millisecondes.
         */
        inline void changeTimeSpan(int value)
        {
            timerIrSensorGroup_.changeTimeSpan(value);
        }

        inline pmx::IrSensor irRight()
        {
            return irRight_;
        }
        inline pmx::IrSensor irLeft()
        {
            return irLeft_;
        }
        inline pmx::IrSensor irCenter()
        {
            return irCenter_;
        }
        inline pmx::IrSensor irRearCenter()
        {
            return irRearCenter_;
        }


        /*!
         * \brief Méthode appelée en fonction du chronometer, àla fréquence du \ref Timer utilisé.
         * \param chrono chonomètre permettant de déterminer  l'interval de temps depuis le dernier appel de cette méthode.
         */
        void onTimer(utils::Chronometer chrono);

        void onTimerEnd(utils::Chronometer chrono);


        /*!
         * \brief conversion en mm du voltage donné par le GP2.
         */
        double gp2Convert(int type, int value);

        void startTimer();

        void stopTimer();

        void waitSensors();

        void getValues(pmx::IRobotIn * robotIn, pmx::IrSensor * irSensor);

    };  
};

#endif
