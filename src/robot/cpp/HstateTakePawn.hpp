/*!
 * \file
 * \brief Définition de la classe HstateTakePawn (Homologation).
 */

#ifndef PMX_HSTATETAKEPAWN_HPP
#define	PMX_HSTATETAKEPAWN_HPP

#include "IAutomateState.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    namespace automate
    {
        class HstateTakePawn : public pmx::IAutomateState
        {
        private:

            static inline const utils::Logger & logger()
            {
                static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::automate::HstateTakePawn");
                return instance;
            }

        public:

            HstateTakePawn()
            {}

            virtual ~ HstateTakePawn()
            {}

            virtual IAutomateState* execute(Robot& robot);
        };
    }
}

#endif	/* PMX_HSTATETAKEPAWN_HPP */
