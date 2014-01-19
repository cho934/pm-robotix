/*!
 * \file
 * \brief Définition de la classe Robot.
 */

#ifndef PMX_ROBOT_HPP
#define PMX_ROBOT_HPP

#include "IInitialized.hpp"
#include "Base.hpp"
#include "ServoMotor2p.hpp"
#include "ColumnElementLever.hpp"
#include "SimpleSensor.hpp"
#include "DistanceDetector.hpp"
#include "ActionManager.hpp"
#include "SensorManager.hpp"
#include "Stepper.hpp"
#include "IAutomateState.hpp"
#include "ServoMotor.hpp"
#include "MovementAction.hpp"

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
         * \brief Contact de démarrage.
         */
        pmx::SimpleSensor startContact_;
        
        /*!
         * \brief SimpleSensor de reboot.
         */
        pmx::SimpleSensor rebootContact_;
        
        /*!
         * \brief Détecteur de distance GP2 repérant l'adversaire devant le robot.
         */
        pmx::DistanceDetector frontDistanceOpponent_;
        
        /*!
         * \brief Détecteur de distance droit du robot.
         */
        pmx::DistanceDetector rightDistanceBorder_;
        
        /*!
         * \brief Détecteur de distance gauche du robot.
         */
        pmx::DistanceDetector leftDistanceBorder_;
        
        /*!
         * \brief Levier droit.
         */
        pmx::ColumnElementLever rightLever_;
        
        /*!
         * \brief Levier gauche.
         */
        pmx::ColumnElementLever leftLever_;
        
        /*!
         * \brief Moteur pas à pas.
         */
        pmx::Stepper stepper_;
        
        /*!
         * \brief Pelle du robot.
         */
        pmx::ServoMotor shovel_;
        
        /*!
         * \brief Element Droit à pousser.
         */
        pmx::ColumnElementLever rightPushElement_;
        
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
        virtual inline ~ Robot()
        {}
        
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
         * \brief Retourne la position du robot.
         */
        inline const pmx::Position & position() const
        {
            return base_.positionManager().position();
        }
        
        /*!
         * \brief Cette methode retourne l'objet de manipulation du contact présence balle dans le distributeur.
         * \return Le contact de présence balle dans le distributeur.
         */
        inline pmx::SimpleSensor & startContact()
        {
            return startContact_;
        }
        
        /*!
         * \brief Cette methode retourne l'objet de manipulation du contact présence balle dans le distributeur.
         * \return Le contact de présence balle dans le distributeur.
         */
        inline pmx::SimpleSensor & rebootContact()
        {
            return rebootContact_;
        }
        
        /*!
         * \brief Cette methode retourne l'objet de manipulation du détecteur de distance GP2 adversaire.
         * \return Le détecteur de distance frontal repérant l'adversaire.
         */
        inline pmx::DistanceDetector & frontDistanceOpponent()
        {
            return frontDistanceOpponent_;
        }
        
        /*!
         * \brief Cette methode retourne l'objet de manipulation du détecteur droit.
         * \return Le détecteur droit repérant la bordure.
         */
        inline pmx::DistanceDetector & rightDistanceBorder()
        {
            return rightDistanceBorder_;
        }
        
        /*!
         * \brief Cette methode retourne l'objet de manipulation du détecteur gauche.
         * \return Le détecteur gauche repérant la bordure.
         */
        inline pmx::DistanceDetector & leftDistanceBorder()
        {
            return leftDistanceBorder_;
        }
        
        /*!
         * \brief Cette methode retourne l'objet de manipulation du levier gauche d'élément de colonne.
         * \return Le levier gauche du robot.
         */
        inline pmx::ColumnElementLever & leftLever()
        {
            return leftLever_;
        }
        
        /*!
         * \brief Cette methode retourne l'objet de manipulation du levier droit d'élément de colonne.
         * \return Le levier droit du robot.
         */
        inline pmx::ColumnElementLever & rightLever()
        {
            return rightLever_;
        }
        
        /*!
         * \brief Cette methode retourne l'objet de manipulation du moteur pas à pas.
         * \return Le moteur pas à pas du robot.
         */
        inline pmx::Stepper & stepper()
        {
            return stepper_;
        }
        
        /*!
         * \brief Cette methode retourne l'objet de manipulation du levier droit d'élément de colonne.
         * \return Le levier droit du robot.
         */
        inline pmx::ServoMotor & shovel()
        {
            return shovel_;
        }
        
        inline pmx::ColumnElementLever & rightPushElement()
        {
            return rightPushElement_;
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
            actionManager_.addAction(action);
        }
        
        /*!
         * \brief Ajout d'un listener sur les Impulsions gauche et droite.
         * \param listener
         *        Le listener à ajouter.
         */
        inline void addListener(IMotorListener * listener)
        {
            sensorManager_.addListener(listener);
        }
        /*!
         * \brief Ajout d'un listener sur les capteurs.
         * \param listener
         *        Le listener à ajouter.
         */
        inline void addListener(ISensorListener * listener)
        {
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
        
        virtual void initialize(const std::string & prefix, utils::Configuration & configuration);
        
        void configure(const std::string & configurationFile);
        
        /*!
         * \brief Creer et execute un automate sur le robot.
         */
        void startAutomate(IAutomateState* first);
        
        //MovementAction* moveTo(double x, double y); //ne marche pas
    };
};

#endif
