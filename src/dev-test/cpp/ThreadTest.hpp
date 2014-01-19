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
    private:

    /*!
    * \brief Retourne le \ref Logger associé à la classe \ref ThreadTest.
    */
    static const utils::Logger & logger()
    {
        static const utils::Logger & instance = utils::LoggerFactory::logger("test::ThreadTest");
        return instance;
    }
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
         * \brief Test de la classe utils::Thread dans un environnement multi-threads (2).
         */
        void testDoubleThread();

        /*!
         * \brief Test de la classe utils::Thread dans un environnement multi-threads (3).
         */
        void testTripleThread();

        /*!
         * \brief Test de la classe utils::Thread dans un environnement multi-threads (4).
         */
        void testQuadThread();

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
        
        /*!
        * \brief Retourne le \ref Logger associé à la classe \ref TestThread.
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
         * \brief fonction.
         */
        virtual void simpleCount(std::string);
      
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
