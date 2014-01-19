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
#include "IrSensor.hpp"
#include "Clamp.hpp"
#include "LedBar.hpp"
#include "Elevator.hpp"
#include "Chronometer.hpp"
#include "RobotColor.hpp"
#include "OpponentDetector.hpp"
#include "Fork.hpp"

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
         * \brief Base roulante du robot.
         */
        pmx::Base base_;

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
         * \brief Capteur bas gauche pour détecter les pions.
         */
        //pmx::IrSensor pawnLeftIrSensor_;

        /*!
         * \brief Capteur bas droit pour détecter les pions.
         */
        //pmx::IrSensor pawnRightIrSensor_;

        /*!
         * \brief Barre de LED.
         */
        pmx::LedBar ledBar_;

        /*!
         * \brief Fourchette du milieu.
         */
        pmx::Fork forkCenter_;
        pmx::Fork forkRight_;
        pmx::Fork forkLeft_;
        pmx::Fork turnForkRight_;
        pmx::Fork turnForkLeft_;

        /*!
         * \brief Pince.
         */
        //pmx::Clamp clamp_;

        /*!
         * \brief Ascenseur.
         */
        //pmx::Elevator elevator_;

        /*!
         * \brief Ascenseur.
         */
        //pmx::OpponentDetector opponent_;

        /*!
         * \brief Capteur bas droit pour détecter les pions.
         */
        pmx::IrSensor opponentIrSensorLeft_;
        pmx::IrSensor opponentIrSensorRight_;
        pmx::IrSensor opponentIrSensorCenter_;

        /*!
         * \brief Détecteur de distance GP2 repérant l'adversaire devant le robot.
         */
        //pmx::DistanceDetector frontDistanceOpponent_;

        /*!
         * \brief Détecteur de distance droit du robot.
         */
        //pmx::DistanceDetector rightDistanceBorder_;

        /*!
         * \brief Détecteur de distance gauche du robot.
         */
        //pmx::DistanceDetector leftDistanceBorder_;

        /*!
         * \brief Levier droit.
         */
        //pmx::ColumnElementLever rightLever_;

        /*!
         * \brief Levier gauche.
         */
        //pmx::ColumnElementLever leftLever_;

        /*!
         * \brief Moteur pas à pas.
         */
        //pmx::Stepper stepper_;

        /*!
         * \brief Pelle du robot.
         */
        //pmx::ServoMotor shovel_;

        /*!
         * \brief Element Droit à pousser.
         */
        //pmx::ColumnElementLever rightPushElement_;

        /*!
         * \brief chronometerRobot.
         */
        utils::Chronometer chronometerRobot_;

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
         * \brief Cette methode retourne le capteur IR bas gauche.
         * \return Le capteur IR bas gauche.
         */
        /*
                inline pmx::IrSensor & pawnLeftIrSensor()
                {
                    return pawnLeftIrSensor_;
                }
         */
        /*!
         * \brief Cette methode retourne le capteur IR bas droit.
         * \return Le capteur IR bas droit.
         */
        /*
                inline pmx::IrSensor & pawnRightIrSensor()
                {
                    return pawnRightIrSensor_;
                }
         */

        /*!
         * \brief Cette methode retourne le capteur IR bas droit.
         * \return Le capteur IR bas droit.
         */

        inline pmx::IrSensor & opponentIrSensorLeft()
        {
            return opponentIrSensorLeft_;
        }

        inline pmx::IrSensor & opponentIrSensorRight()
        {
            return opponentIrSensorRight_;
        }
        
        inline pmx::IrSensor & opponentIrSensorCenter()
        {
            return opponentIrSensorCenter_;
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
         * \brief Cette methode retourne la fourchette.
         *
         * \return La pince.
         */
        inline pmx::Fork & forkCenter()
        {
            return forkCenter_;
        }

        /*!
         * \brief Cette methode retourne la fourchette.
         *
         * \return La pince.
         */
        inline pmx::Fork & forkRight()
        {
            return forkRight_;
        }

        /*!
         * \brief Cette methode retourne la fourchette.
         *
         * \return La pince.
         */
        inline pmx::Fork & forkLeft()
        {
            return forkLeft_;
        }

        /*!
         * \brief Cette methode retourne la fourchette.
         *
         * \return La pince.
         */
        inline pmx::Fork & turnForkRight()
        {
            return turnForkRight_;
        }

        /*!
         * \brief Cette methode retourne la fourchette.
         *
         * \return La pince.
         */
        inline pmx::Fork & turnForkLeft()
        {
            return turnForkLeft_;
        }

        /*!
         * \brief Cette methode retourne la pince.
         * \return La pince.
         */
/*
        inline pmx::Clamp & clamp()
        {
            return clamp_;
        }
*/

        /*!
         * \brief Cette methode retourne l'ascenseur.
         * \return La pince.
         */
        /*
                inline pmx::Elevator & elevator()
                {
                    return elevator_;
                }
         */
        /*!
         * \brief Cette methode retourne le detecteur adverse.
         * \return La detecteur adverse.
         */
        /*
                inline pmx::OpponentDetector & opponentDetector()
                {
                    return opponent_;
                }
         */

        /*!
         * \brief Active ou désactive la détection des valeurs des encodeurs moteurs.
         */
        inline void firePulseEnabled(bool value)
        {
            if (!value)
            {
                usleep(500); //!\todo pourquoi ?
            }
            sensorManager_.firePulseEnabled(value);
        }

        /*!
         * \brief Cette methode retourne l'objet de manipulation du détecteur de distance GP2 adversaire.
         * \return Le détecteur de distance frontal repérant l'adversaire.
         */
        /*
        inline pmx::DistanceDetector & frontDistanceOpponent()
        {
            return frontDistanceOpponent_;
        }*/

        /*!
         * \brief Cette methode retourne l'objet de manipulation du détecteur droit.
         * \return Le détecteur droit repérant la bordure.
         */
        /*inline pmx::DistanceDetector & rightDistanceBorder()
        {
            return rightDistanceBorder_;
        }*/

        /*!
         * \brief Cette methode retourne l'objet de manipulation du détecteur gauche.
         * \return Le détecteur gauche repérant la bordure.
         */
        /*inline pmx::DistanceDetector & leftDistanceBorder()
        {
            return leftDistanceBorder_;
        }*/

        /*!
         * \brief Cette methode retourne l'objet de manipulation du levier gauche d'élément de colonne.
         * \return Le levier gauche du robot.
         */
        /*inline pmx::ColumnElementLever & leftLever()
        {
            return leftLever_;
        }*/

        /*!
         * \brief Cette methode retourne l'objet de manipulation du levier droit d'élément de colonne.
         * \return Le levier droit du robot.
         */
        /*inline pmx::ColumnElementLever & rightLever()
        {
            return rightLever_;
        }*/

        /*!
         * \brief Cette methode retourne l'objet de manipulation du moteur pas à pas.
         * \return Le moteur pas à pas du robot.
         */
        /*inline pmx::Stepper & stepper()
        {
            return stepper_;
        }*/

        /*!
         * \brief Cette methode retourne l'objet de manipulation du levier droit d'élément de colonne.
         * \return Le levier droit du robot.
         */
        /*inline pmx::ServoMotor & shovel()
        {
            return shovel_;
        }
        
        inline pmx::ColumnElementLever & rightPushElement()
        {
            return rightPushElement_;
        }*/

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
         * \brief Initialise les paramètres du robot via un fichier de configuration.
         */
        virtual void initialize(const std::string & prefix, utils::Configuration & configuration);
        /*!
         * \brief Lance l'initialisation par fichier de configuration
         */
        void configure(const std::string & configurationFile);

      void  goTo(double x, double y);

      void  goToTeta(double x, double y, BaseWay way, double teta);
    };
}

#endif
