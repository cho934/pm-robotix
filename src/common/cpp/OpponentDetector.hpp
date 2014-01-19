/*!
 * \file
 * \brief Définition de la classe OpponentDetector (utilisation CMUCAM).
 * \deprecated
 */

#ifndef PMX_OPPONENTDETECTOR_HPP
#define	PMX_OPPONENTDETECTOR_HPP

#include "ARobotElement.hpp"
#include "Macro.hpp"
#include "IAction.hpp"
#include "ISensorListener.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe représente le dispositif qui permet de détecter l'adversaire.
     *
     */
    class OpponentDetector: public ARobotElement
    {
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref OpponentDetector.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::OpponentDetector");
            return instance;
        }

        /*!
         * \brief \c true si la commande d'execution du listener associée est active.
         */
        bool active_;

        /*!
         * \brief \c true lorsque ce listener doit être supprimé de la liste des listeners.
         */
        bool listenerStopped_;

        /*!
         * \brief m.
         */
        ushort m_;

        /*!
         * \brief
         */
        ushort shortDist_;

        ushort mediumDist_;

        ushort leftSide_;

        ushort rightSide_;

        /*!
         * \brief \c true si la donnée est actualisée.
         */
        bool received_;

        bool imminenteCollision_;


    public:

        /*!
         * \brief Constructeur de la classe.
         */
        OpponentDetector(pmx::Robot & robot, ushort dm, ushort shortDist, ushort mediumDist, ushort leftSide, ushort rightSide);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ OpponentDetector()
        {}
  
        inline bool active() const
        {
            return active_;
        }
        inline void active(bool active)
        {
            this->active_ = active;
        }

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

        inline ushort m() const
        {
            return m_;
        }

        inline ushort shortDist() const
        {
            return shortDist_;
        }

        inline ushort mediumDist() const
        {
            return mediumDist_;
        }

        inline ushort leftSide() const
        {
            return leftSide_;
        }

        inline ushort rightSide() const
        {
            return rightSide_;
        }

        inline bool received() const
        {
            return received_;
        }
        inline void received(bool value)
        {
            this->received_ = value;
        }

        inline bool imminenteCollision() const
        {
            return imminenteCollision_;
        }
        inline void imminenteCollision(bool value)
        {
            this->imminenteCollision_ = value;
        }

        /*!
         * \brief Ajout le listener de detection de l'adversaire.
         */
        virtual void addOpponentListener();

    };

    /*!
     * \brief Ce listener permet de lire la reception de la CMUCAM.
     *
     */
    class OpponentListener: public ISensorListener
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref OpponentListener.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::OpponentListener");
            return instance;
        }

        /*!
         * \brief Référence vers le contact associé.
         */
        OpponentDetector & opponent_;

    public:

        /*!
         * \brief Constructeur de la classe.
         * \param contact
         *        Reference vers le OpponentDetector associé.
         */
        OpponentListener(OpponentDetector & opponent);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ OpponentListener()
        {}

        virtual bool execute(IRobotIn * robotIn);
    };

};
#endif	/* PMX_OPPONENTDETECTOR_HPP */

