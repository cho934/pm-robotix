/*!
 * \file
 * \brief Implémentation de la classe TestM4.
 */

#include <iostream>
#include "ImpulsionsTest.hpp"
#include "Robot.hpp"
#include "LoggerFactory.hpp"
#include "MotorWay.hpp"

using namespace test;

namespace test
{
    /*!
     * \brief Classe loggant les informations fournies par les sensors.
     */
    class LoggedSensorListener : public pmx::IMotorListener
    {
    private:
        
        /*!
         * \return Trace associé à la classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::LoggedSensorListener");
            return instance;
        }
        
        /*!
         * \brief Nombre d'impulsions reçues pour le capteur gauche.
         */
        uint nbImpLeft_;
        
        /*!
         * \brief Nombre d'impulsions reçues pour le capteur droit.
         */
        uint nbImpRight_;
        
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        LoggedSensorListener() : nbImpLeft_(0), nbImpRight_(0)
        {}
        
        /*!
         * \brief Destructeur.
         */
        virtual inline ~ LoggedSensorListener()
        {}
        
        /*!
         * \brief Action en cas de front sur le capteur gauche.
         * Assure le comptage du nombre de front.
         *
         * \param value
         *        Type de front.
         */
        void inline onLeftPulse(bool value, int, int, pmx::MotorWay way)
        {
            if (value) //uniquement les fronts montants
            {
                nbImpLeft_++;
                logger().info() << "LEFT: " << nbImpLeft_  << " Way: " << (way == pmx::FORWARD ? "FORWARD" : "BACK") << utils::end;
            }
        }
        
        /*!
         * \brief Action en cas de front sur le capteur droit.
         * Assure le comptage du nombre de front.
         *
         * \param value
         *        Type de front.
         */
        void inline onRightPulse(bool value, int, int, pmx::MotorWay way)
        {
            if(value) //uniquement les fronts montants
            {
                nbImpRight_++;
                logger().info() << "RIGHT: " << nbImpRight_ << " Way: " << (way == pmx::FORWARD ? "FORWARD" : "BACK") << utils::end;
            }
        }
    };
}

void ImpulsionsTest::run(int, char *[])
{
    logger().info() << "test::ImpulsionsTest: Start (30 secondes)" << utils::end;
    pmx::Robot robot;
    robot.addListener(new LoggedSensorListener());
    
    robot.start();
    
    time_t start = time(NULL);
    //test pendant 30 secondes
    while(start + 30 > time(NULL))
    {
        pthread_yield();
    }
    logger().info() << "test::ImpulsionsTest: End" << utils::end;
    robot.stop();
}
