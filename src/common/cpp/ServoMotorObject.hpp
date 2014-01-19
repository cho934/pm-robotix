/*!
 * \file
 * \brief Définition de la classe ServoMotorObject (n positions).
 * \deprecated
 */

#ifndef PMX_SERVOMOTOROBJECT_HPP
#define	PMX_SERVOMOTOROBJECT_HPP

#include "ARobotElement.hpp"
#include "Macro.hpp"
#include "IAction.hpp"
#include "LoggerFactory.hpp"
#include "Chronometer.hpp"
#include "IInitialized.hpp"
#include "ServoMotorApf.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe représente l'un des servomoteurs fonctionnant en 3 positions du robot.
     *
     */
    class ServoMotorObject: public ARobotElement
    {
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorObject.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotorObject");
            return instance;
        }
        /*!
         * \brief Position de la pince; 0:fermée; 1:ouverte.
         */
        int stateOpened_;

        /*!
         * \brief Permet de stopper l'action et qu'elle se termine à la prochaine itération.
         */
        bool actionStopped_;
        
        /*!
         * \brief Brochage du servomoteur.
         */
        int id_;
         
        /*!
         * \brief Angle minimum (en millisecond).
         */
        int valMin_;

        /*!
         * \brief Angle minimum (en millisecond).
         */
        int valMed_;
        
        /*!
         * \brief Angle maximum (en millisecond).
         */
        int valMax_;
        
        /*!
         * \brief vitesse de rotation (en millisecond de 5000ms à 300000ms).
         */
        int valSpeed_;


        
                
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        ServoMotorObject(pmx::Robot & robot, int servoId);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ ServoMotorObject()
        {}
        
       inline void stop(bool value)
        {
            this->actionStopped_ = value;
        }
        inline bool stop() const
        {
            return actionStopped_;
        }
        
        inline int id() const
        {
            return id_;
        }
        
        inline int stateOpened() const
        {
            return stateOpened_;
        }
        inline void stateOpened(int stateOpened)
        {
            this->stateOpened_ = stateOpened;
        }
        
        inline int min() const
        {
            return valMin_;
        }
        inline void min(int min)
        {
            this->valMin_ = min;
        }

        inline int med() const
        {
            return valMed_;
        }
        inline void med(int med)
        {
            this->valMed_ = med;
        }

        inline int max() const
        {
            return valMax_;
        }
        inline void max(int max)
        {
            this->valMax_ = max;
        }

        
        
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration);

        /*!
         * \brief Positionne le servomotor sur sa position min.
         */
        virtual void turnMin(bool freewheeling);
         /*!
         * \brief Positionne le servomotor sur sa position medium.
         */
        virtual void turnMed(bool freewheeling);
         /*!
         * \brief Positionne le servomotor sur sa position max.
         */
        virtual void turnMax(bool freewheeling);

        virtual void freeWheeling(bool freewheeling);
    };
    
    /*!
     * \brief Cette action permet de definir le déplacement angulaire du servomoteur.
     *
     * \bug Externaliser cette classe.
     */
    class ServoMotorObjectAction: public IAction
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorObjectAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotorObjectAction");
            return instance;
        }
        
        /*!
         * \brief Référence vers le servomoteur associé.
         */
        ServoMotorObject & servomotor_;
        
       /*!
         * \brief libellé de l'action à exécuter.
         */
        ServoMotorObjectActionName action_;

        /*!
         * \brief chronomètre de la pince permettant de définir le temps d'ouverture/fermeture.
         */
        utils::Chronometer chrono_;

        /*!
         * \brief dernier temps issu du chronometre.
         */
        long lastTime_;

        /*!
         * \brief mode d'action.
         */
        int mode_;

        /*!
         * \brief définit si la puissance du servomotor doit être maintenue.
         */
        bool freewheeling_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param servomotor
         *        Reference vers le servomoteur associé.
         */
        ServoMotorObjectAction(ServoMotorObject & servomotor, pmx::ServoMotorObjectActionName action, bool freewheeling);
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ServoMotorObjectAction()
        {}

        virtual bool execute(IRobotOut * out);

        virtual inline std::string info()
        {
            return "ServoMotorObjectAction";
        }
    };
};

#endif

