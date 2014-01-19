/*!
 * \file
 * \brief Implémentation de la classe ImpulsionsTest.
 * Permet d'afficher le compte des codeurs en live via le robot.
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
         * \brief Nombre d'impulsions reçues pour le codeur gauche depuis le début du match.
         */
        int nbImpLeft_;

        /*!
         * \brief Nombre d'impulsions reçues pour le codeur droit depuis le début du match.
         */
        int nbImpRight_;

    public:
        /*!
         * \brief Constructeur par défaut.
         */
        LoggedSensorListener() : nbImpLeft_(0), nbImpRight_(0)
        {
        }

        /*!
         * \brief Destructeur.
         */
        virtual inline ~LoggedSensorListener()
        {
        }

        /*!
         * \brief Action en cas de front sur le capteur gauche.
         * Assure le comptage du nombre de front.
         *
         * \param value
         *        Type de front.
         */
        void inline onLeftPulse(int value, utils::Chronometer, pmx::MotorWay way)
        {
            nbImpLeft_ += value;
            logger().info() << "LEFT : " << nbImpLeft_ << " Way: " << (way == pmx::FORWARD ? "FORW" : "BACK") << utils::end;
        }

        /*!
         * \brief Action en cas de front sur le capteur droit.
         * Assure le comptage du nombre de front.
         *
         * \param value
         *        Type de front.
         */
        void inline onRightPulse(int value, utils::Chronometer, pmx::MotorWay way)
        {
            nbImpRight_ += value;
            logger().info() << "RIGHT: " << nbImpRight_ << " Way: " << (way == pmx::FORWARD ? "FORW" : "BACK") << utils::end;
        }

    };
}

void ImpulsionsTest::run(int, char *[])
{
    logger().info() << "Robot : Start (10 secondes)" << utils::end;
    pmx::Robot robot;
    //Désactivation des moteurs, permet de ne pas envoyer d'action (applyMotorCode).
    robot.base().motorLeft().disabled(true);
    robot.base().motorRight().disabled(true);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().pidPositionEnabled(false);
    robot.base().pidSpeedEnabled(false);

    //Ajout du listener dédié défini ci-dessus.
    robot.addListener(new LoggedSensorListener());
    robot.start();

    sleep(10);

    logger().info() << "End" << utils::end;

    robot.stop();
}
