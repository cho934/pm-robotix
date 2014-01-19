/*!
 * \file
 * \brief Définition de la classe ThreadTest.
 */

#ifndef TEST_THREADTEST_HPP
#define TEST_THREADTEST_HPP

#include <string>

#include "UnitTest.hpp"
#include "Thread.hpp"

namespace test
{
    /*!
     * \brief Tests unitaires de la classe utils::Thread.
     */
    class ThreadTest: public utils::UnitTest
    {
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        ThreadTest(): utils::UnitTest("ThreadTest")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ ThreadTest()
        {}
        
        /*!
         * \brief Test de la classe utils::Thread dans un environnement simple.
         */
        void testSimpleThread();
        
        /*!
         * \brief Test de la classe utils::Thread dans un environnement multi-threads.
         */
        void testDoubleThread();
        
        /*!
         * \brief Exécution des tests.
         */
        virtual void suite();
    };
    
    /*!
     * \brief Classe implémentant un thread pour la réalisation des tests
     * unitaires.
     */
    class TestThread : public utils::Thread
    {
    private:
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::TestThread");
            return instance;
        }
        
        /*!
         * \brief Le nom de ce thread.
         */
        std::string name_;
        
    protected:
        
        /*!
         * \brief Code exécuté par le thread de test lorsqu'il est actif.
         */
        virtual void execute();
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param name
         *        Nom associé au thread créé.
         */
        TestThread(const std::string & name): name_(name)
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ TestThread()
        {}
        
        /*!
         * \return Nom du thread.
         */
        inline const std::string & name() const
        {
            return name_;
        }
    };
};

#endif
