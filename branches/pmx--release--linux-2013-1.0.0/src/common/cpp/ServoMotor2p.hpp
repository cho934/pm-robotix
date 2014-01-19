/*!
 * \file
 * \brief Définition de la classe ServoMotor2p (2 positions).
 * \deprecated
 */

#ifndef PMX_SERVOMOTOR2P_HPP
#define	PMX_SERVOMOTOR2P_HPP

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
    class ServoMotor2p: public ARobotElement
    {
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ServoMotor2p.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotor2p");
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
         * \brief Angle minimum (en millisecond).
         */
        int angleMin_;
        
        /*!
         * \brief Angle maximum (en millisecond).
         */
        int angleMax_;
        
        /*!
         * \brief vitesse de rotation (en millisecond de 5000ms à 300000ms).
         */
        int speed_;
                
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ServoMotor2p(pmx::Robot & robot, ushort dm, ushort pin, int angleMin, int angleMax, int speed);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ ServoMotor2p()
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
        
        inline int angleMin() const
        {
            return angleMin_;
        }
        
        inline int angleMax() const
        {
            return angleMax_;
        }
        
        inline int speed() const
        {
            return speed_;
        }
        
        inline void open()
        {
            this->active_ = true;
            this->state_ = true;
            logger().debug() << "ServoMotor2p::open()" << utils::end;   
        }
        
        inline void close()
        {
            this->active_ = true;
            this->state_ = false;
            logger().debug() << "ServoMotor2p::close()" << utils::end;   
        }
        
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration);
    };
    
    /*!
     * \brief Cette action permet de definir le déplacement angulaire du servomoteur.
     *
     * \bug Externaliser cette classe.
     */
    class ServoMotor2pAction: public IAction
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ServoMotor2pAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotor2pAction");
            return instance;
        }
        
        /*!
         * \brief Référence vers le servomoteur associé.
         */
        const ServoMotor2p & servomotor_;
        
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
        ServoMotor2pAction(const ServoMotor2p & servomotor);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ ServoMotor2pAction()
        {}
        
        virtual bool execute(IRobotOut * out);
    };
};

#endif

