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
        /**
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::SimpleSensor");
            return instance;
        }
        
        /*!
         * \brief Brochage M.
         */
        ushort mu_;
        
        /*!
         * \brief Brochage pin du M.
         */
        ushort pin_;
        
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
        
        inline ushort mu() const
        {
            return mu_;
        }
        
        inline ushort pin() const
        {
            return pin_;
        }
    };
}

#endif
