/*!
 * \file
 * \brief Définition de la classe DISTANCEDETECTOR.
 * \deprecated
 */

#ifndef PMX_DISTANCEDETECTOR_HPP
#define	PMX_DISTANCEDETECTOR_HPP

#include "ARobotElement.hpp"
#include "Macro.hpp"
#include "IAction.hpp"
#include "ISensorListener.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe représente le GP2 surveillant l'adversaire.
     *
     */
    class DistanceDetector : public ARobotElement
    {
    private:
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref DistanceDetector.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::DistanceDetector");
            return instance;
        }
        
        /*!
         * \brief \c true si l'action du gp2 est active.
         */
        bool active_;
        
        /*!
         * \brief Multiplexeur récupérant la distance.
         */
        ushort mu_;
        
        /*!
         * \brief Démultiplexeur gérant l'activation WR.
         */
        ushort dm_;
        
        /*!
         * \brief Pin du démultiplexeur gérant l'activation WR.
         */
        ushort pin_;
        
        /*!
         * \brief Distance binaire donné par le CAN.
         */
        ushort distance_;
        
        /*!
         * \brief Distance mm donné par la conversion.
         */
        double distanceMm_;
        
        /*!
         * \brief \c true si la distance est actualisée.
         */
        bool received_;
        
        /*!
         * \brief \c true si le listener du GP2 est actif.
         */
        bool activeListener_;
        
        public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        DistanceDetector(pmx::Robot & robot, ushort mu, ushort dm, ushort pin);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ DistanceDetector()
        {}
        
        inline bool active() const
        {
            return active_;
        }
        
        inline void active(bool active)
        {
            this->active_ = active;
        }
        
        inline ushort dm() const
        {
            return dm_;
        }
        
        inline ushort pin() const
        {
            return pin_;
        }
        
        inline ushort mu() const
        {
            return mu_;
        }
        
        inline int distance() const
        {
            return distance_;
        }
        
        inline double distanceMm() const
        {
            return distanceMm_;
        }
        
        inline void distance(int distance)
        {
            this->distance_ = distance;
        }
        
        inline void distanceMm(int distanceMm)
        {
            this->distanceMm_ = distanceMm;
        }
        
        inline bool received() const
        {
            return received_;
        }
        
        inline void received(bool received)
        {
            this->received_ = received;
        }
        
        inline bool activeListener() const
        {
            return activeListener_;
        }
        
        inline void activeListener(bool activeListener)
        {
            this->activeListener_ = activeListener;
        }

    };
    
    /*!
     * \brief Cette action permet d'activer le GP2 (front sur WR).
     *
     * \bug Externaliser cette classe.
     */
    class DistanceDetectorAction: public IAction
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref DistanceDetectorAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::DistanceDetectorAction");
            return instance;
        }
        
        /*!
         * \brief Référence vers le distanceDetector associé.
         */
        DistanceDetector & distanceDetector_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param distanceDetector
         *        Reference vers le GP2 associé.
         */
        DistanceDetectorAction(DistanceDetector & distanceDetector);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ DistanceDetectorAction()
        {}
        
        virtual bool execute(IRobotOut * out);

        virtual inline std::string info()
        {
            return "DistanceDetectorAction";
        }
    };
    
     /*!
     * \brief Ce listener permet de lire le DistanceDetector.
     *
     */
    class DistanceDetectorListener: public ISensorListener
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref DistanceDetectorListener.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::DistanceDetectorListener");
            return instance;
        }
        
        /*!
         * \brief Référence vers le contact associé.
         */
        DistanceDetector & distanceDetector_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param contact
         *        Reference vers le DistanceDetector associé.
         */
        DistanceDetectorListener(DistanceDetector & distanceDetector);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ DistanceDetectorListener()
        {}
        
        virtual bool execute(IRobotIn * robotIn);   
    };
};

#endif











