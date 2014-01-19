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
#include "SpeedManager.hpp"
#include "PID.hpp"
#include "IInitialized.hpp"

namespace pmx
{
    class SpeedManager;
    
    /*!
     * \brief Cette classe représente l'un des moteurs du robot.
     *
     * Cette classe représente le moteur ainsi que la roue qui y est attachée.
     * Le capteur de vitesse est quant à lui géré par l'instance de SpeedManager associé au moteur.
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
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Motor");
            return instance;
        }
        
        /*!
         *\brief Moteur placé à droite ou à gauche.
         */
        MotorLocation location_;
        
        /*!
         *\brief Sens du moteur avant ou arrière.
         */
        MotorWay way_;
        
        /*!
         * \brief Coefficient directeur de la fonction affine de conversion du code moteur en vitesse (mm/s).
         */
        double gradient_;
        
        /*!
         * \brief Ordonnée à l'origine de la fonction affine de conversion du code moteur en vitesse (mm/s).
         */
        double yIntersept_;
        
        /*!
         * \brief Vitesse de consigne associée du moteur (en mm/s).
         */
        double orderSpeed_;
        
        /*!
         * \brief Manager associé au senseur du moteur.
         */
        pmx::SpeedManager * manager_;
        
        /*!
         * \brief \c true si la vitesse doit être corrigée en fonction de l'ordre.
         *
         * Si cette propriété vaut \c false, le speed manager ne fera que tracer les informations de vitesse.
         */
        bool speedCorrectionEnabled_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param robot Robot associé au moteur.
         * \param location Emplacement du moteur sur le robot.
         * \param sens du moteur.
         * \param gradient Coefficient directeur de la fonction de conversion du code moteur en vitesse en mm/s.
         * \param yIntersept Ordonnée à l'origine de la fonction de conversion du code moteur en vitesse en mm/s.
         * \param pid instance de utils::PID utilisée pour lisser les corrections de vitesse (voir pmx::SpeedManager).
         */
        Motor(pmx::Robot & robot, const MotorLocation & location, MotorWay way, double gradient, double yIntersept, const utils::PID & pid);
        
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
         * \brief Accesseur pour l'ordre de vitesse.
         */
        inline double orderSpeed()
        {
            return this->orderSpeed_;
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
         * \brief Modificateur pour l'ordre de vitesse associé au robot et du sens de marche en conséquence.
         *
         * \param orderSpeed
         *        L'ordre de vitesse.Peut être négatif.
         */
        inline void orderSpeedAndWay(double orderSpeed)
        {
            if(orderSpeed >= 0)
            {
                this->applyWay(pmx::FORWARD);
                this->orderSpeed_ = orderSpeed;
            }else
            {
                this->applyWay(pmx::BACK);
                this->orderSpeed_ = -orderSpeed;
            }
        }
        
        inline bool speedCorrectionEnabled() const
        {
            return this->speedCorrectionEnabled_;
        }
        
        inline void speedCorrectionEnabled(bool speedCorrectionEnabled)
        {
            this->speedCorrectionEnabled_ = speedCorrectionEnabled;
        }
        
        void speedCorrectionEnabled(double P, double I, double D);
        
        /*!
         * \brief Arrete le moteur.
         */
        inline void stop()
        {
            this->orderSpeed(0.0);
            this->applyMotorCode(0);
        }
        
        /*!
         * \brief Convertie un code moteur en la vitesse équivalente (en mm/s).
         * \param motorCode Code moteur à convertir.
         * \return Vitesse associée au code moteur en mm/s.
         */
        double convertToSpeed(int motorCode);
        
        /*!
         * \brief Convertie une vitesse dans le code moteur associé.
         * Le code moteur retourné sera arrondi et garder dans l'intervalle de référence [0, 255].
         *
         * \param speed Vitesse à convertir en mm/s.
         * \return Code moteur associé à la vitesse.
         */
        int convertToMotorCode(double speed);
        
        /*!
         * \brief Applique un code moteur au moteur.
         * \param motorCode le code moteur à appliquer (doit être compris entre 0 et 255).
         */
        void applyMotorCode(int motorCode);
        
        void applyWay(const MotorWay way);
        
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration); 

    private:
        
        /*!
         * \brief Accesseur retournant le manager associé à ce moteur.
         */
        inline pmx::SpeedManager * manager() const
        {
            return manager_;
        }
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
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
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
         *        Valeur du code moteur à appliquer.
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
        MotorWay way_;
        
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
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
        MotorWayAction(Motor & motor, MotorWay way): motor_(motor), way_(way)
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
