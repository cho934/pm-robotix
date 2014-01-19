/*!
 * \file
 * \brief Définition de la classe MutexTest.
 */

#ifndef TEST_MUTEXTEST_H
#define	TEST_MUTEXTEST_H

#include "LoggerFactory.hpp"
#include "UnitTest.hpp"
#include "Thread.hpp"
#include "Mutex.hpp"

namespace test
{
    /*!
     * \brief Tests unitaires de la classe utils::Mutex.
     */
    class MutexTest : public utils::UnitTest
    {
    private:
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::MutexTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        MutexTest(): utils::UnitTest("MutexTest")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ MutexTest()
        {}
        
        /*!
         * \brief Test de la classe utils::Mutex dans un environnement simple.
         */
        void testSimpleThread();
        
        /*!
         * \brief Test de la classe utils::Mutex dans un environnement multi-threads.
         */
        void testDoubleThread();
        
        /*!
         * \brief Exécution des tests.
         */
        virtual void suite();
    };
    
    namespace mutex
    {
        /*!
         * \brief Classe utilisée dans les tests des Mutex.
         *
         * Cette classe représente un compteur prévue pour être utilisé
         * dans un contexte multi-thread.
         * Elle possède deux méthodes d'incrémentation du compteur :
         * - addWithLock() qui est garantie comme thread-safe,
         * - addWithoutLock() qui nécessite d'exploiter les locks du mutex.
         */
        class Counter : public utils::Mutex
        {
        private:
            
            /**
             * \brief Cette méthode retourne le logger associé à cette classe.
             * \return Le logger de cette classe.
             */
            static const utils::Logger & logger()
            {
                static const utils::Logger & instance = utils::LoggerFactory::logger("test::mutex::Counter");
                return instance;
            }
            
        private:
            
            /*!
             * \brief Valeur du compteur.
             */
            int value_;
            
        public:
            
            /*!
             * \brief Constructeur par défaut.
             *
             * Le compteur est initialisé à zéro.
             */
            Counter() : value_(0)
            {}
            
            /*!
             * \brief Destructeur de la classe.
             */
            virtual inline ~ Counter()
            {}
            
            /*!
             * \brief Incrémente le compteur (thread-safe).
             */
            void addOneWithLock()
            {
                logger().debug("addOneWithLock");
                this->lock();
                value_ = value_ + 1;
                this->unlock();
            }
            
            /*!
             * \brief Incrémente le compteur (non thread-safe).
             */
            void addOneWithoutLock()
            {
                logger().debug("addOneWithoutLock");
                value_ = value_ + 1;
            }
            
            /*!
             * \brief Accesseur à la valeur du compteur.
             *
             * \return Valeur du compteur.
             */
            inline int value() const
            {
                return value_;
            }
        };
        
        /*!
         * \brief Classe implémentant un thread pour la réalisation des tests
         * unitaires.
         */
        class TestThread : public utils::Thread
        {
        private:
            
            /*!
             * \brief Compteur associé au thread.
             */
            Counter * counter_;
            
            /*!
             * \brief \c true si la méthode addWithLock() doit être utilisée.
             */
            bool implicitLock_;
            
        protected:
            
            /*!
             * \brief Code exécuté par le thread de test lorsqu'il est actif.
             * Ajoute 1 au compteur.
             */
            virtual void execute();
            
        public:
            
            /*!
             * \brief Constructeur de la classe.
             * \param counter
             *        Compteur associé au thread.
             * \param implicitLock
             *        \c true si la méthode addWithLock() doit être utilisée.
             */
            TestThread(Counter * counter, bool implicitLock): counter_(counter), implicitLock_(implicitLock)
            {}
            
            /*!
             * \brief Destructeur de la classe.
             */
            virtual inline ~ TestThread()
            {}
        };
    }
};

#endif
