/*!
 * \file
 * \brief Définition de la classe Robot.
 */

#ifndef PMX_ROBOT_HPP
#define PMX_ROBOT_HPP

#include "IInitialized.hpp"
#include "Base.hpp"
#include "ActionManager.hpp"
#include "SensorManager.hpp"
#include "SimpleSensor.hpp"
#include "LedBar.hpp"
#include "Chronometer.hpp"
#include "RobotColor.hpp"
#include "IrSensorsGroup.hpp"
#include "Clamp.hpp"
#include "ServoMotorObject.hpp"


namespace pmx
{
    /*!
     * \brief Cette classe représente le robot.
     *
     * Cette classe maitresse de l'application représente le robot et permet
     * d'accéder à l'ensemble de ses éléments.
     */
    class Robot : public IInitialized
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref Robot.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Robot");
            return instance;
        }

        /*!
         * \brief Assure la gestion des actions du robot.
         */
        pmx::ActionManager actionManager_;

        /*!
         * \brief Assure la gestion des capteurs du robot.
         */
        pmx::SensorManager sensorManager_;

        /*!
         * \brief chronometerRobot.
         */
        utils::Chronometer chronometerRobot_;

       /*!
         * \brief Base roulante du robot.
         */
        pmx::Base base_;

         /*!
         * \brief Assure la gestion du timer des IR.
         */
        pmx::IrSensorsGroup irSensorsGroup_;

        /*!
         * \brief Couleur du robot.
         */
        pmx::RobotColor myColor_;

        /*!
         * \brief Mode de match (matches ou homologation).
         */
        pmx::RobotMode runMode_;

        /*!
         * \brief Contact de démarrage.
         */
        pmx::SimpleSensor startContact_;

        /*!
         * \brief SimpleSensor de reboot.
         */
        pmx::SimpleSensor rebootContact_;

        /*!
         * \brief SimpleSensor de choix de couleur.
         */
        pmx::SimpleSensor colorContact_;

        /*!
         * \brief Contact de démarrage.
         */
        pmx::SimpleSensor leftBackContact_;

        /*!
         * \brief Contact de démarrage.
         */
        pmx::SimpleSensor rightBackContact_;

        /*!
         * \brief Barre de LED.
         */
        pmx::LedBar ledBar_;

        /*!
         * \brief Le tri des balles par couleur.
         */
        pmx::ServoMotorObject servoColorSorting_;

        /*!
         * \brief Le gonfleur de ballon.
         */
        pmx::ServoMotorObject servoBalloonInflate_;

        /*!
         * \brief Pince.
         */
        pmx::Clamp clamp_;

        pmx::ServoMotorObject servoLevier_;

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        Robot();

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~Robot()
        {
        }

        /*!
         * \brief Cette méthode retourne l'objet de manipulation de la base
         * roulante du robot.
         * \return La base roulante du robot.
         */
        inline pmx::Base & base()
        {
            return base_;
        }

        /*!
         * \brief Retourne la couleur du robot.
         */
        inline pmx::RobotColor myColor() const
        {
            return myColor_;
        }

        /*!
         * \brief Enregistre la couleur du robot.
         */
        inline void myColorIs(pmx::RobotColor color)
        {
            this->myColor_ = color;
        }

        /*!
         * \brief Retourne le mode de match du robot.
         */
        inline pmx::RobotMode myRunningMode() const
        {
            return runMode_;
        }

        /*!
         * \brief Enregistre le mode de match du robot.
         */
        inline void runMode(pmx::RobotMode mode)
        {
            this->runMode_ = mode;
        }

        /*!
         * \brief Retourne la position du robot depuis son depart.
         */
        inline pmx::Position & position()
        {
            return base_.positionManager().position();
        }

        /*!
         * \brief Cette methode retourne l'objet de manipulation du contact start.
         * \return Le contact de start.
         */
        inline pmx::SimpleSensor & startContact()
        {
            return startContact_;
        }

        /*!
         * \brief Cette methode retourne l'objet de manipulation du contact arrière gauche.
         * \return Le contact arrière gauche.
         */
        inline pmx::SimpleSensor & leftBackContact()
        {
            return leftBackContact_;
        }

        /*!
         * \brief Cette methode retourne l'objet de manipulation du contact arrière droit.
         * \return Le contact arrière droit.
         */
        inline pmx::SimpleSensor & rightBackContact()
        {
            return rightBackContact_;
        }

        /*!
         * \brief Cette methode retourne l'objet de manipulation du contact de reboot.
         * \return Le contact de reboot.
         */
        inline pmx::SimpleSensor & rebootContact()
        {
            return rebootContact_;
        }

        /*!
         * \brief Cette methode retourne l'objet de manipulation du contact présence balle dans le distributeur.
         * \return Le contact de présence balle dans le distributeur.
         */
        inline pmx::SimpleSensor & colorContact()
        {
            return colorContact_;
        }

        /*!
         * \brief Cette methode retourne le groupe de capteurs IR.
         * \return Le groupe capteur IR.
         */
        inline pmx::IrSensorsGroup & irSensorsGroup()
        {
            return irSensorsGroup_;
        }

        /*!
         * \brief Cette methode retourne la barre de led.
         *
         * \return La barre de led.
         */
        inline pmx::LedBar & ledBar()
        {
            return ledBar_;
        }



        /*!
         * \brief Cette methode retourne la pince.
         * \return La pince.
         */
        inline pmx::ServoMotorObject & servoColorSorting()
        {
            return  servoColorSorting_;
        }

        /*!
         * \brief Cette methode retourne la pince.
         * \return La pince.
         */
        inline pmx::ServoMotorObject & servoBalloonInflate()
        {
            return servoBalloonInflate_;
        }

        /*!
         * \brief Cette methode retourne la pince.
         * \return La pince.
         */
        inline pmx::Clamp & clamp()
        {
            return clamp_;
        }

        inline pmx::ServoMotorObject & servoLevier()
        {
            return  servoLevier_;
        }

        /*!
         * \brief Active ou désactive la détection des valeurs des encodeurs moteurs.
         */
        inline void firePulseEnabled(bool value)
        {
            /*if (!value)
            {
                usleep(500); //!\todo pourquoi ?
            }*/
            sensorManager_.firePulseEnabled(value);
        }

        /*!
         * \brief Cette methode retourne l'objet de manipulation du chronometer.
         * \return Le chronometer.
         */
        inline utils::Chronometer & chronometerRobot()
        {
            return chronometerRobot_;
        }

        /*!
         * \brief Ajout d'une action.
         * \param action
         *        L'action à ajouter.
         */
        inline void addAction(IAction * action)
        {
            logger().debug() << "Robot addAction" << utils::end;
            actionManager_.addAction(action);
        }

        /*!
         * \brief Ajout d'un listener sur les Impulsions gauche et droite.
         * \param listener
         *        Le listener à ajouter.
         */
        inline void addListener(IEncoderListener * listener)
        {
            logger().debug() << "IEncoderListener addListener" << utils::end;
            sensorManager_.addListener(listener);
        }

        /*!
         * \brief Ajout d'un listener sur les capteurs.
         * \param listener
         *        Le listener à ajouter.
         */
        inline void addListener(ISensorListener * listener)
        {
            logger().debug() << "ISensorListener addListener" << utils::end;
            sensorManager_.addListener(listener);
        }

        /*!
         * \brief Active le robot.
         *
         * Cette méthode lance les différents threads associés et initialise
         * le système.
         */
        void start();

        /*!
         * \brief Arrete le robot et libère les ressources associés.
         */
        void stop();

        /*!
         * \brief Arrete le thread sensorManager et actionManager.
         */
        void stopManagers();

         /*!
         * \brief Arrete les composant du robot.
         */
        void stopDevices();

        /*!
         * \brief Initialise les paramètres du robot via un fichier de configuration.
         */
        virtual void initialize(const std::string & prefix, utils::Configuration & configuration);
        /*!
         * \brief Lance l'initialisation par fichier de configuration
         */
        void configure(const std::string & configurationFile);

      void  goTo(double x, double y, BaseWay way, bool detection);

      void  goToTeta(double x, double y, double teta, BaseWay way, bool detection);
    };
}

#endif
