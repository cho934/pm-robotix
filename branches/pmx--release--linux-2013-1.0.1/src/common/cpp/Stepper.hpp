/*!
 * \file
 * \brief Définition de la classe Stepper.
 * \deprecated
 */

#ifndef PMX_STEPPER_HPP
#define	PMX_STEPPER_HPP

#include "ARobotElement.hpp"
#include "Macro.hpp"
#include "IAction.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe représente l'un des moteurs pas-pas du robot.
     *
     */
    class Stepper: public ARobotElement
    {
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref Stepper.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Stepper");
            return instance;
        }
        
        /*!
         * \brief \c true si le moteur pas à pas est actif.
         */
        bool active_;
        
        /*!
         * \brief Brochage DM.
         */
        ushort dm_;
        
        /*!
         * \brief Etape en cours.
         */
        ushort step_;
                
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        Stepper(pmx::Robot & robot, ushort dm);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ Stepper()
        {}
        
        ushort values_[8] ;
        
        
        inline bool active() const
        {
            return active_;
        }
        
        inline void active(bool active)
        {
            this->active_ = active;
        }
        
        inline ushort step() const
        {
            return step_;
        }
        
        inline void step(ushort step)
        {
            this->step_ = step;
        }
                
        inline ushort dm() const
        {
            return dm_;
        }
        
        inline void turn()
        {
            this->active_ = true;
            logger().debug() << "Stepper::turn()" << utils::end;   
        }
        
        inline void stop()
        {
            this->active_ = false;
            logger().debug() << "Stepper::stop()" << utils::end;   
        }
        
        
    };
    
    /*!
     * \brief Cette action permet de definir la rotation d'un moteur pas à pas.
     *
     * \bug Externaliser cette classe.
     */
    class StepperAction: public IAction
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref StepperAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::StepperAction");
            return instance;
        }
        
        /*!
         * \brief Référence vers le stepper associé.
         */
        Stepper & stepper_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param stepper
         *        Reference vers le stepper associé.
         */
        StepperAction(Stepper & stepper);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ StepperAction()
        {}
        
        virtual bool execute(IRobotOut * out);
    };
};

#endif	/* PMX_STEPPER_HPP */

