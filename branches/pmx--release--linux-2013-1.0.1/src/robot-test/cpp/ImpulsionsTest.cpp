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
#include "Md25.hpp"

using namespace test;

namespace test
{

    /*!
     * \brief Classe loggant les informations fournies par les sensors.
     */
    class LoggedSensorListener : public pmx::IEncoderListener
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
        
    public:
        /*!
         * \brief Nombre d'impulsions reçues sur le codeur gauche associé au
         * moteur gauche depuis le début du match.
         */
        long nbEncLeftMotor_;

        /*!
         * \brief Nombre d'impulsions reçues sur le codeur gauche indépendant
         * depuis le début du match.
         */
        long nbEncLeftFree_;

        /*!
         * \brief Nombre d'impulsions reçues sur le codeur droit associé au
         * moteur droit depuis le début du match.
         */
        long nbEncRightMotor_;

        /*!
         * \brief Nombre d'impulsions reçues sur le codeur droit indépendant
         * depuis le début du match.
         */
        long nbEncRightFree_;

    public:
        /*!
         * \brief Constructeur par défaut.
         */
        LoggedSensorListener() : nbEncLeftMotor_(0), nbEncLeftFree_(0), nbEncRightMotor_(0), nbEncRightFree_(0)
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
        void inline onLeftPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer)
        {

            nbEncLeftMotor_ += motorEncoderValue;
            nbEncLeftFree_ += freeEncoderValue;
            logger().info() << "MOTORLEFT : " << nbEncLeftMotor_ << " FREELEFT : " << nbEncLeftFree_ << utils::end; //<< " Way: " << (way == pmx::FORWARD ? "FORW" : "BACK")
        }

        /*!
         * \brief Action en cas de front sur le capteur droit.
         * Assure le comptage du nombre de front.
         *
         * \param value
         *        Type de front.
         */
        void inline onRightPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer)
        {
            nbEncRightMotor_ += motorEncoderValue;
            nbEncRightFree_ += freeEncoderValue;
            logger().info() << "MOTORRIGHT: " << nbEncRightMotor_ << " FREERIGHT: " << nbEncRightFree_ << utils::end;
        }
    };
}

void ImpulsionsTest::run(int, char *[])
{

    logger().info() << "Robot : Start (15 secondes)" << utils::end;
    pmx::Robot robot;
    //Désactivation des moteurs, permet de ne pas envoyer d'action (applyMotorCode).
    robot.base().motorLeft().disabled(false);
    robot.base().motorRight().disabled(false);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().pidPositionEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidSpeedEnabled(false);
    robot.base().pidSpeedDesactivate();

    //Ajout du listener dédié défini ci-dessus.
    test::LoggedSensorListener* listener = new test::LoggedSensorListener();
    robot.addListener(listener);
    //robot.addListener(new LoggedSensorListener());
    robot.start();
    robot.chronometerRobot().start();

    robot.base().pidSpeedStart(); //start le timer de gestion PID pour le compute
   
    //robot.base().motorLeft().applyMotorCode(120);
    //robot.base().motorRight().applyMotorCode(120);

    sleep(15); //pendant 15sec

    logger().info() << "Robot Stop()" << utils::end;
    robot.stop();
    robot.chronometerRobot().stop();

    logger().info() << "LoggedSensorListener : "
            << " Left : " << listener->nbEncLeftMotor_ << " ticks"
            << " Right: " << listener->nbEncRightMotor_ << " ticks"
            << utils::end;

    logger().info() << "Position odométrie : "
            << " x: " << robot.position().x() << " mm"
            << " y: " << robot.position().y() << " mm"
            << utils::end;

    logger().info() << "End-Of-PMX : "
            << robot.chronometerRobot().getElapsedTimeInMicroSec() << " us "
            << utils::end;
}
