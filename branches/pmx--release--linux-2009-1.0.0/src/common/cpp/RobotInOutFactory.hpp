#ifndef PMX_ROBOTINOUTFACTORY_H
#define	PMX_ROBOTINOUTFACTORY_H

#include "IRobotIn.hpp"
#include "IRobotOut.hpp"
#include "Mutex.hpp"

namespace pmx
{
    class RobotInOutFactory : public utils::Mutex
    {
    public:
        
        /*!
         * \brief Instance unique de la classe.
         */
        static RobotInOutFactory * instance();
        
    private:
        
        /*!
         * \brief Flux d'entrée du robot.
         */
        IRobotIn * in_;
        
        /*!
         * \brief Flux de sortie du robot.
         */
        IRobotOut * out_;
        
        /*!
         * \brief Constructeur de la classe.
         */
        RobotInOutFactory();
        
    public:
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ RobotInOutFactory()
        {}
        
        /*!
         * \brief Retourne un pointeur vers le flux d'entrée du robot.
         *
         * \return Le flux d'entrée du robot.
         */
        virtual inline IRobotIn * robotIn() const
        {
            return in_;
        }
        
        /*!
         * \brief Retourne un pointeur vers le flux de sortie du robot.
         *
         * \return Le flux de sortie du robot.
         */
        virtual inline IRobotOut * robotOut() const
        {
            return out_;
        }
    };
}

#endif
