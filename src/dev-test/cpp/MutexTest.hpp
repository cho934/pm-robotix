/*!
 * \file
 * \brief Définition de la classe MutexTest.
 */

#ifndef TEST_MUTEXTEST_H
#define	TEST_MUTEXTEST_H

#include "../../common/cpp/LoggerFactory.hpp"
#include "DevUnitTest.hpp"
#include "../../common/cpp/Thread.hpp"
#include "../../common/cpp/Mutex.hpp"

namespace test
{
    /*!
     * \brief Teste la classe \ref utils::Mutex.
     */
    class MutexTest : public utils::DevUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref MutexTest.
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
        MutexTest() : utils::DevUnitTest("MutexTest")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~MutexTest()
        {
        }

        /*!
         * \brief Teste la classe \ref utils::Mutex dans un environnement simple.
         */
        void testSimpleThread();

        /*!
         * \brief Teste la classe \ref utils::Mutex dans un environnement multi-threads.
         */
        void testDoubleThread();

         /*!
         * \brief Execute les tests associés à la classe \ref MutexTest.
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

            /*!
            * \brief Retourne le \ref Logger associé à la classe \ref Counter.
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
            {
            }

            /*!
             * \brief Destructeur de la classe.
             */
            virtual inline ~Counter()
            {
            }

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
            TestThread(Counter * counter, bool implicitLock) : counter_(counter), implicitLock_(implicitLock)
            {
            }

            /*!
             * \brief Destructeur de la classe.
             */
            virtual inline ~TestThread()
            {
            }
        };
    }
};

#endif
