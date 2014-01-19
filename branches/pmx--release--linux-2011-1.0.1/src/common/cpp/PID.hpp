#ifndef PMX_PID_H
#define	PMX_PID_H

#include <iostream>
#include "LoggerFactory.hpp"
namespace utils
{
    /*!
     * \brief Cette classe regroupe les éléments propres au calcul d'un PID
     */
    class PID
    {
    private:
        
        /*!
         * \brief Trace associée à la classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("utils::PID");
            return instance;
        }
        
    private:
        
        /*!
         *\brief Composante proportionnelle.
         */
        double kP_;
        
        /*!
         *\brief Composante intégrale.
         */
        double kI_;
        
        /*!
         *\brief Composante dérivée.
         */
        double kD_;
        
        /*!
         *\brief Dernière erreur constatée.
         */
        double lastError_;
        
        /*!
         *\brief Somme des erreurs constatées depuis le début.
         */
        double errSum_;
        
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        PID();
        
        /*!
         * \brief Constructeur initialisé.
         * \param kP Composante proportionnelle.
         * \param kI Composante intégrale.
         * \param kD Composante dérivée.
         */
        PID(double kP, double kI, double kD);
        
        /*!
         * \brief Constructeur initialisé à partir de valeurs entières.
         * \param kP Composante proportionnelle.
         * \param kI Composante intégrale.
         * \param kD Composante dérivée.
         */
        PID(int kP, int kI, int kD);
        
        /*!
         * \brief Constructeur par recopie.
         * \param pid Le pid a copier.
         */
        PID(const PID& pid);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ PID()
        {}
        
    public:
        
        inline double getkP() const
        {
            return kP_;
        }
        
        inline double getkI() const
        {
            return kI_;
        }
        
        inline double getkD() const
        {
            return kD_;
        }
        
        double ComputePID(int error);
        
        void reset();
    };
}

#endif
