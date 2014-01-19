/*!
 * \file
 * \brief Définition de la classe ServoMotor (2 positions).
 * \deprecated
 */

#ifndef PMX_ServoMotor_HPP
#define	PMX_ServoMotor_HPP

#include <vector>
#include "ARobotElement.hpp"
#include "Macro.hpp"
#include "IAction.hpp"
#include "LoggerFactory.hpp"
#include "Chronometer.hpp"
#include "IInitialized.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe représente l'un des servomoteurs fonctionnant en 2 positions du robot.
     *
     */
    class ServoMotor: public ARobotElement
    {
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ServoMotor.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotor");
            return instance;
        }
        
        /*!
         * \brief \c true si le servomoteur est actif.
         */
        bool active_;
        
        /*!
         * \brief Si \c true le servomoteur doit être en position ouvert.
         */
        bool state_;
        
        /*!
         * \brief Brochage DM.
         */
        ushort dm_;
        
        /*!
         * \brief Brochage pin du DM.
         */
        ushort pin_;
        
        /*!
         * \brief Tableau contenant les différentes valeurs des rapports cycliques (en millisecond).
         */
        std::vector<int> values_;
        
        /*!
         * \brief valeur courante (position du tableau : 0, 1, 2, etc).
         */
        int currentValue_;
        
        /*!
         * \brief vitesse de rotation (en millisecond de 5000ms à 300000ms).
         */
        int speed_;
                
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ServoMotor(pmx::Robot & robot, ushort dm, ushort pin, int speed);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ ServoMotor()
        {}
        
        inline bool active() const
        {
            return active_;
        }
        
        inline void active(bool active)
        {
            this->active_ = active;
        }
        
        inline bool state() const
        {
            return state_;
        }
        
        inline ushort dm() const
        {
            return dm_;
        }
        
        inline ushort pin() const
        {
            return pin_;
        }
        
        inline const std::vector<int> & values() const
        {
            return values_;
        }
        
        inline std::vector<int> & values()
        {
            return values_;
        }
        
        inline int currentValue() const
        {
            return currentValue_;
        }
        
        inline void currentValue(int currentValue)
        {
            this->currentValue_ = currentValue;
        }
        
        inline int speed() const
        {
            return speed_;
        }
        
        inline void GoPosition(int tabPosition)
        {
            this->currentValue_ = tabPosition;
            this->active_ = true;
            this->state_ = true;
            logger().debug() << "ServoMotor::GoPosition()" << utils::end;   
        }
        
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration);
    };
    
    /*!
     * \brief Cette action permet de definir le déplacement angulaire du servomoteur.
     *
     * \bug Externaliser cette classe.
     */
    class ServoMotorAction: public IAction
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotorAction");
            return instance;
        }
        
        /*!
         * \brief Référence vers le servomoteur associé.
         */
        const ServoMotor & servomotor_;
        
        utils::Chronometer chronometerServo_;
             
        /*!
         * \brief Si \c true Impulsion haute sur le servomoteur.
         */
        bool pulse_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param servomotor
         *        Reference vers le servomoteur associé.
         */
        ServoMotorAction(const ServoMotor & servomotor);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ ServoMotorAction()
        {}
        
        virtual bool execute(IRobotOut * out);

        virtual inline std::string info()
        {
            return "ServoMotorAction";
        }
    };
};

#endif

