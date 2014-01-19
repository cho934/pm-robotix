/*!
 * \file
 * \brief Définition de la classe ColumnElementLever.
 * \deprecated
 */

#ifndef PMX_COLUMNELEMENTLEVER_HPP
#define	PMX_COLUMNELEMENTLEVER_HPP

#include "ARobotElement.hpp"
#include "Macro.hpp"
#include "IAction.hpp"
#include "LoggerFactory.hpp"
#include "Chronometer.hpp"
#include "IInitialized.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe représente les leviers d'élément de colonne du robot.
     */
    class ColumnElementLever: public ARobotElement, public IInitialized
    {
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ColumnElementLever.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ColumnElementLever");
            return instance;
        }
        
        /*!
         * \brief \c true si le servomoteur est actif.
         */
        bool active_;
        
        /*!
         * \brief Position du levier; 0:rentré (angle minimum); 1:sortie (angle maximum).
         */
        int state_;
        
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
        ColumnElementLever(pmx::Robot & robot, ushort dm, ushort pin, int angleMin, int angleMax, int speed);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ ColumnElementLever()
        {}
        
        inline bool active() const
        {
            return active_;
        }
        
        inline void active(bool active)
        {
            this->active_ = active;
        }
        
        inline int state() const
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
        
        inline void returnCentralePosition()
        {
            this->active_ = true;
            this->state_ = 0;
            logger().debug() << "ColumnElementLever::returnCentralePosition()" << utils::end;
        }
        
        inline void stackElement()
        {
            this->active_ = true;
            this->state_ = 1;
            logger().debug() << "ColumnElementLever::stackElement()" << utils::end;
        }
        
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration);
    };
    
    /*!
     * \brief Cette action permet de definir le déplacement angulaire du levier.
     *
     * \bug Externaliser cette classe.
     */
    class ColumnElementLeverAction: public IAction
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ColumnElementLeverAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ColumnElementLeverAction");
            return instance;
        }
        
        /*!
         * \brief Référence vers le levier associé.
         */
        const ColumnElementLever & lever_;
        
        utils::Chronometer chronometer_;
        
        /*!
         * \brief Si \c true Impulsion haute sur le levier(servomoteur).
         */
        bool pulse_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param lever
         *        Reference vers le ColumnElementLever associé.
         */
        ColumnElementLeverAction(const ColumnElementLever & lever);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ ColumnElementLeverAction()
        {}
        
        virtual bool execute(IRobotOut * out);

        virtual inline std::string info()
        {
            return "ColumnElementLeverAction";
        }
    };
};

#endif	/* PMX_COLUMNELEMENTLEVER_HPP */

