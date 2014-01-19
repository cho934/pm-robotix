/*!
 * \file
 * \brief Définition de la classe HstateMoveToSquare.
 */

#ifndef PMX_HSTATEMOVETOSQUARE_HPP
#define	PMX_HSTATEMOVETOSQUARE_HPP

#include "IAutomateState.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    namespace automate
    {
        class HstateMoveToSquare : public pmx::IAutomateState
        {
        private:

            static inline const utils::Logger & logger()
            {
                static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::automate::HstateMoveToSquare");
                return instance;
            }

        public:

            HstateMoveToSquare()
            {}

            virtual ~ HstateMoveToSquare()
            {}

            virtual IAutomateState* execute(Robot& robot);
        };
    }
}

#endif	/* PMX_HSTATEMOVETOSQUARE_HPP */

