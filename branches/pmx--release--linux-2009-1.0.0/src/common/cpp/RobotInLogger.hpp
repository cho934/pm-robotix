#ifndef PMX_ROBOTINLOGGER_H
#define	PMX_ROBOTINLOGGER_H

#include "IRobotIn.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    class RobotInLogger : public IRobotIn
    {
    private:
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::RobotInLogger");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        RobotInLogger();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ RobotInLogger()
        {}
        
        virtual bool getValue(ushort multiplexor, ushort pin);
        
        virtual int getValues(ushort multiplexor);
        
        virtual bool getImpRight();
        
        virtual bool getImpLeft();
        
        virtual bool getImpLeftWay();
        
        virtual bool getImpRightWay();
    };
}

#endif
