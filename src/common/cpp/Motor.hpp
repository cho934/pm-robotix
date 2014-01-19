/*!
 * \file
 * \brief Définition de la classe Motor.
 */

#ifndef PMX_MOTOR_HPP
#define PMX_MOTOR_HPP

#include "MotorLocation.hpp"
#include "MotorWay.hpp"
#include "Macro.hpp"
#include "ARobotElement.hpp"
#include "IAction.hpp"
#include "LoggerFactory.hpp"
#include "IInitialized.hpp"

namespace pmx
{   
    /*!
     * \brief Cette classe représente l'un des moteurs de type 919D GEARBOX SERIES du robot.
     * Cette classe représente le moteur ainsi que la roue qui y est attachée.
     *
     * La relation entre code-moteur et vitesse est approximée à une fonction affine y=ax+b, avec :
     * - x : code-moteur - configuredMotorCode()
     * - y : vitesse - configuredSpeed()
     * - a : gradient()
     * - b : yIntercept()
     */
    class Motor: public ARobotElement, public IInitialized
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref Motor.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Motor");
            return instance;
        }
        
        /*!
         *\brief Moteur rouge ou jaune.
         */
        MotorLocation location_;
        
        /*!
         *\brief Sens du moteur avant ou arrière.
         */
        MotorWay way_;

        /*!
         * \brief Booleen pour confirmer l'application du sens de marche.
         */
        bool wayApplied_;
        
        /*!
         * \brief Coefficient directeur de la fonction affine de conversion du code moteur en vitesse (mm/s).
         * \deprecated
         */
        double gradient_;
        
        /*!
         * \brief Ordonnée à l'origine de la fonction affine de conversion du code moteur en vitesse (mm/s).
         * \deprecated
         */
        double yIntersept_;
        
        /*!
         * \brief Vitesse de consigne associée du moteur (en mm/s).
         * \deprecated
         */
        double orderSpeed_;

        /*!
         * \brief Ordre de vitesse en tick entre 2 appels du SpeedManagerFusion.
         */
        int orderTick_;

        /*!
         * \brief Valeur précédente de l'ordre de vitesse en tick entre 2 appels du SpeedManagerFusion.
         */
        int oldOrderTick_;

        /*!
         * \brief Ordre de position en tick.
         */
        int orderPosition_;

        /*!
         * \brief Moteur désactivé.
         */
        bool disabled_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param robot Robot associé au moteur.
         * \param location Emplacement du moteur sur le robot.
         * \param sens du moteur.
         * \param gradient Coefficient directeur de la fonction de conversion du code moteur en vitesse en mm/s.
         * \param yIntersept Ordonnée à l'origine de la fonction de conversion du code moteur en vitesse en mm/s.
         */
        Motor(pmx::Robot & robot, const MotorLocation & location, MotorWay way, double gradient, double yIntersept); //!\todo Motor: gradient et yIntersept inutile
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ Motor()
        {}
        
        /*!
         * \brief Cette méthode retourne la position du moteur.
         */
        inline MotorLocation location() const
        {
            return this->location_;
        }
        
        /*!
         * \brief Cette méthode retourne la valeur interne du sens du moteur.
         */
        inline MotorWay way()
        {
            return this->way_;
        }

        /*!
         * \brief Cette méthode modifie la valeur interne du sens du moteur.
         */
        void way(MotorWay way)
        {
            this->way_ = way;
        }

        /*!
         * \brief Cette méthode retourne \c true si le sens du moteur a été appliqué.
         */
        inline bool wayApplied()
        {
            return this->wayApplied_;
        }
        /*!
         * \brief Cette méthode modifie la valeur d'application du sens du moteur.
         */
        void wayApplied(bool ok)
        {
            this->wayApplied_ = ok;
        }

        /*!
         * \brief Cette méthode indique si le moteur est désactivé (les actions ne sont plus envoyées).
         */
        inline bool disabled()
        {
            return this->disabled_;
        }

        /*!
         * \brief Cette méthode modifie l'activation du moteur.
         */
        void disabled(bool disabled)
        {
            this->disabled_ = disabled;
        }

        /*!
         * \brief Accesseur pour l'ordre de vitesse.
         */
        inline double orderSpeed()
        {
            return this->orderSpeed_;
        }

        /*!
         * \brief Accesseur pour l'ordre de tick.
         */
        inline int orderTick()
        {
            return this->orderTick_;
        }

        /*!
         * \brief Accesseur pour le précédent ordre de vitesse.
         */
        inline int oldOrderTick()
        {
            return this->oldOrderTick_;
        }

         /*!
         * \brief Accesseur pour l'ordre de position.
         */
        inline int orderPositionTick()
        {
            return this->orderPosition_;
        }

        /*!
         * \brief Modificateur pour l'ordre de vitesse associé au robot.
         *
         * \param pos
         *        L'ordre de position positif.
         */
        inline void orderPositionTick(int pos)
        {
            this->orderPosition_ = pos;
        }

        /*!
         * \brief Modificateur pour l'ordre de vitesse associé au robot.
         *
         * \param orderSpeed
         *        L'ordre de vitesse positif.
         */
        inline void orderSpeed(double orderSpeed)
        {
            this->orderSpeed_ = orderSpeed;
        }

        /*!
         * \brief Modificateur pour l'ordre de vitesse par tick associé au robot.
         *
         * \param orderTick
         *        L'ordre de vitesse positif (en tick par timeSpan).
         */
        inline void orderTick(int orderTick)
        {
            this->orderTick_ = orderTick;
        }

        /*!
         * \brief Modificateur pour le précédent ordre de vitesse associé au robot.
         *
         * \param oldOrderSpeed
         *        L'ordre de vitesse positif.
         */
        inline void oldOrderTick(double orderTick)
        {
            this->oldOrderTick_ = orderTick;
        }

        /*!
         * \brief Arrete le moteur.
         */
        void stop()
        {
            this->orderSpeed(0.0);
            this->orderTick(0);
            this->applyMotorCode(0);
            usleep(1000); //permettre aux autres threads de s'exécuter
        }

        /*!
         * \brief reset le moteur.
         */
        inline void resetMotor()
        {
            this->orderSpeed_ = 0.0;
            this->orderTick_ = 0;
            this->oldOrderTick_ = 0;
            this->orderPosition_ = 0;
            this->wayApplied_ = false;
            this->gradient_ = 0.0;
            this->yIntersept_ = 0.0;
        }
        
        /*!
         * \brief Applique un code moteur au moteur.
         * \param motorCode le code moteur à appliquer (doit être compris entre 0 et 1024).
         */
        void applyMotorCode(int motorCode);
        
        /*!
         * \brief Applique un sens de vitesse au moteur.
         * \param way le sens du moteur à appliquer.
         */
        void applyWay(const MotorWay way);
        
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration);

    };
    
    /*!
     * \brief Cette action permet de définir le code moteur d'un moteur.
     *
     * \bug Externaliser cette classe.
     */
    class MotorSpeedAction: public IAction
    {
    private:
        
        /*!
         * \brief Référence vers le moteur associé.
         */
        Motor & motor_;
        
        /*!
         * \brief Code moteur à appliquer.
         */
        uint speedMotorCode_;
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref MotorSpeedAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::MotorSpeedAction");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param motor
         *        Référence vers le moteur associé.
         * \param motorCode
         *        Valeur du code moteur à appliquer : 0 à 1024.
         */
        MotorSpeedAction(Motor & motor, uint motorCode): motor_(motor), speedMotorCode_(motorCode)
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ MotorSpeedAction()
        {}
        
        virtual bool execute(IRobotOut * out);
        
        virtual inline std::string info()
        {
            return "MotorSpeedAction";
        }
    };
    
    /*!
     * \brief Cette action permet de définir le sens d'un moteur.
     *
     * \bug Externaliser cette classe.
     */
    class MotorWayAction: public IAction
    {
    private:
        
        /*!
         * \brief Référence vers le moteur associé.
         */
        Motor & motor_;
        
        /*!
         * \brief Sens moteur à appliquer.
         */
        MotorWay wayToApply_;

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref MotorWayAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::MotorWayAction");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param motor
         *        Référence vers le moteur associé.
         * \param way
         *        Valeur du sens moteur à appliquer.
         */
        MotorWayAction(Motor & motor, MotorWay way): motor_(motor), wayToApply_(way)
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ MotorWayAction()
        {}
        
        virtual bool execute(IRobotOut * out);

        virtual inline std::string info()
        {
            return "MotorWayAction";
        }
    };
};

#endif
