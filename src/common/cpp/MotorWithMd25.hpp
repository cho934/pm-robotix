/*!
 * \file
 * \brief Définition de la classe MotorWithMd25.
 */

#ifndef PMX_MOTORWITHMD25_HPP
#define	PMX_MOTORWITHMD25_HPP

#include "MotorLocation.hpp"
#include "Macro.hpp"
#include "ARobotElement.hpp"
#include "IAction.hpp"
#include "LoggerFactory.hpp"
#include "IInitialized.hpp"

namespace pmx
{

    /*!
     * \brief Cette classe représente l'un des moteurs de motorisation associé à la carte MD25.
     *
     * Cette classe représente le moteur ainsi que la roue qui y est attachée.
     * Le capteur de vitesse est quant à lui géré par l'instance de SpeedManagerFusion associé au moteur.
     *
     * La relation entre code-moteur et vitesse est approximée à une fonction affine y=ax+b, avec :
     * - x : code-moteur - configuredMotorCode()
     * - y : vitesse - configuredSpeed()
     * - a : gradient()
     * - b : yIntercept()
     */
    class MotorWithMd25: public ARobotElement, public IInitialized
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref Motor.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::MotorWithMd25");
            return instance;
        }

        /*!
         *\brief Moteur placé à droite ou à gauche.
         */
        MotorLocation location_;

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
        int orderPositionTick_;

        /*!
         * \brief Moteur désactivé.
         */
        bool disabled_;

        /*!
         * \brief Code moteur à appliquer.
         */
        int speedMotorCode_;

    public:

        /*!
         * \brief Constructeur de la classe.
         * \param robot Robot associé au moteur.
         * \param location Emplacement du moteur sur le robot.
         */
        MotorWithMd25(pmx::Robot & robot, const MotorLocation & location);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ MotorWithMd25()
        {}

        /*!
         * \brief Cette méthode retourne la position du moteur.
         */
        inline MotorLocation location() const
        {
            return this->location_;
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
         * \deprecated
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
            return this->orderPositionTick_;
        }

        /*!
         * \brief Modificateur pour l'ordre de vitesse associé au robot.
         *
         * \param pos
         *        L'ordre de position (positif).
         */
        inline void orderPositionTick(int pos)
        {
            this->orderPositionTick_ = pos;
        }

        /*!
         * \brief Modificateur pour l'ordre de vitesse associé au robot.
         *
         * \param orderSpeed
         *        L'ordre de vitesse (positif).
         */
        inline void orderSpeed(double orderSpeed)
        {
            this->orderSpeed_ = orderSpeed;
        }

        /*!
         * \brief Modificateur pour l'ordre de vitesse par timeSpan associé au robot.
         *
         * \param orderTick
         *        L'ordre de vitesse (positif) en tick par timeSpan.
         */
        inline void orderTick(int orderTick)
        {
            this->orderTick_ = orderTick;
        }

        /*!
         * \brief Modificateur pour le précédent ordre de vitesse associé au robot.
         *
         * \param oldOrderSpeed
         *        L'ordre de vitesse précédent.
         */
        inline void oldOrderTick(double orderTick)
        {
            this->oldOrderTick_ = orderTick;
        }



        inline void speedMotorCode(int speed)
        {
            this->speedMotorCode_ = speed;
        }

        inline int speedMotorCode()
        {
            return this->speedMotorCode_;
        }

        /*!
         * \brief Stop le moteur.
         */
        void stop()
        {
            this->orderSpeed(0.0);
            this->orderTick(0);
            this->applyMotorCode(0);
        }

        /*!
         * \brief Reset les valeurs d'ordre moteur.
         */
        inline void resetMotor()
        {
            this->orderSpeed_ = 0.0;
            this->orderTick_ = 0;
            this->oldOrderTick_ = 0;
            this->orderPositionTick_ = 0;
        }

        /*!
         * \brief Applique un code moteur au moteur.
         * \param motorCode le code moteur à appliquer (doit être compris entre -128 et 127).
         */
        void applyMotorCode(int motorCode);

        virtual void initialize(const std::string& prefix, utils::Configuration& configuration);

    };

    /*!
     * \brief Cette action permet de définir le code moteur d'un moteur.
     *
     * \bug Externaliser cette classe.
     */
    class MotorWithMd25SpeedAction: public IAction
    {
    private:

        /*!
         * \brief Référence vers le moteur associé.
         */
        MotorWithMd25 & motor_;

        

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref MotorWithMd25SpeedAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::MotorWithMd25SpeedAction");
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
        MotorWithMd25SpeedAction(MotorWithMd25 & motor, int motorCode): motor_(motor)
        {
            motor.speedMotorCode(motorCode);
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ MotorWithMd25SpeedAction()
        {}

        virtual bool execute(IRobotOut * out);

        virtual inline std::string info()
        {
            return "MotorWithMd25SpeedAction";
        }
    };
};

#endif	/* PMX_MOTORWITHMD25_HPP */

