/*!
 * \file
 * \brief Définition de la classe HstateMoveToPawn (Homologation).
 */

#ifndef PMX_HSTATEMOVETOPAWN_HPP
#define	PMX_HSTATEMOVETOPAWN_HPP

#include "IAutomateState.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    namespace automate
    {
        class HstateMoveToPawn : public pmx::IAutomateState
        {
        private:
            
            static inline const utils::Logger & logger()
            {
                static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::automate::HstateMoveToPawn");
                return instance;
            }
            
        public:
            
            HstateMoveToPawn()
            {}
            
            virtual ~ HstateMoveToPawn()
            {}
            
            virtual IAutomateState* execute(Robot& robot);
        };
    }
}

#endif
