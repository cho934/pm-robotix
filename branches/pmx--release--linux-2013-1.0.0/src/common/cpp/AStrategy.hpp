/*!
 * \file
 * \brief Définition de la classe AStrategy.
 */

#ifndef PMX_ISTRATEGY_HPP
#define PMX_ISTRATEGY_HPP

#include "IAutomateState.hpp"
#include "AAutomateState.hpp"

namespace pmx
{
    /*!
     * \brief Définit une stratégie pour le robot.
     */
    class AStrategy : public AAutomateState
    {
    public:

        /*!
         * \brief Calcul l'interet de cette stratégie.
         *
         * \param robot
         *        Le robot à manipuler.
         * \param data
         *        Les données associées à l'execution de l'automate.
         * \return L'interêt de la stratégie par rapport à l'état actuel du robot.
         */
        virtual int computeInterest(const pmx::Robot& robot, void * data) = 0;

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~AStrategy()
        {
        }

    protected:

        /*!
         * \brief Constructeur de la classe.
         */
        AStrategy()
        {
        }
    };
}

#endif
