#ifndef PMX_SIMPLESENSORLISTENER_HPP
#define	PMX_SIMPLESENSORLISTENER_HPP

#include "LoggerFactory.hpp"
#include "ISensorListener.hpp"
#include "SimpleSensor.hpp"

namespace pmx
{
    /*!
     * \brief Ce listener permet de récupérer en continue une valeur de type binaire depuis
     * le port de communication du robot.
     */
    class SimpleSensorListener: public ISensorListener
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref SimpleSensorListener.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::SimpleSensorListener");
            return instance;
        }
        
        /*!
         * \brief Référence vers le contact associé.
         */
        SimpleSensor & contact_;
        
        /*!
         * \brief L'état actuel du contact. Vaut \c true si le contact est activé, \c false sinon.
         */
        //bool state_;
        
        /*!
         * \brief Vaut true lorsque ce sensor listener doit être supprimer de la liste des listeners a suivre.
         */
        //bool stopped_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param contact
         *        Reference vers le contact associé.
         */
        SimpleSensorListener(SimpleSensor & contact);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ SimpleSensorListener()
        {
            //this->stop();
        }
        
        virtual bool execute(IRobotIn * robotIn);
        
        /*!
         * \brief Flag le listener comme devant être stoppé.
         */
        /*inline void stop()
        {
            this->stopped_ = true;
        }*/
        
        inline SimpleSensor & contact()
        {
            return this->contact_;
        }
        /*
        inline bool state()
        {
            return this->state_;
        }*/
    };
}

#endif
