/*!
 * \file
 * \brief Définition de la classe SimpleSensor.
 */

#ifndef PMX_SIMPLESENSOR_HPP
#define	PMX_SIMPLESENSOR_HPP

#include "Macro.hpp"
#include "ARobotElement.hpp"
#include "ISensorListener.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe représente un contact du robot.
     *
     */
    class SimpleSensor: public ARobotElement
    {
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref SimpleSensor.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::SimpleSensor");
            return instance;
        }
        
        /*!
         * \brief \c true lorsque ce listener doit être supprimé de la liste des listeners.
         */
        bool listenerStopped_;
        
        /*!
         * \brief Brochage M.
         */
        ushort mu_;
        
        /*!
         * \brief Brochage pin du M.
         */
        ushort pin_;
        
        /*!
         * \brief L'état actuel du contact. Vaut \c true si le contact est activé, \c false sinon.
         */
        bool state_;

        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        SimpleSensor(pmx::Robot & robot, ushort mu, ushort pin);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ SimpleSensor()
        {}

        /*!
         * \brief Flag le listener comme devant être stoppé.
         */
        inline void stop(bool value)
        {
            this->listenerStopped_ = value;
        }

        inline bool stop() const
        {
            return listenerStopped_;
        }
        
        inline ushort mu() const
        {
            return mu_;
        }
        
        inline ushort pin() const
        {
            return pin_;
        }

        inline bool state()
        {
            return this->state_;
        }

        inline void state(bool value)
        {
            this->state_ = value;
        }

        /*!
         * \brief Lancement du listener.
         */
        virtual void wait();
    };
}

#endif
