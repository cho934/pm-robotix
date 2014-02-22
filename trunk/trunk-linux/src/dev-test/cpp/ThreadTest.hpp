/*!
 * \file
 * \brief Définition de la classe ThreadTest.
 */

#ifndef TEST_THREADTEST_HPP
#define TEST_THREADTEST_HPP

#include <string>
#include "DevUnitTest.hpp"
#include "../../common/cpp/Thread.hpp"

namespace test
{
    /*!
     * \brief Tests unitaires de la classe utils::Thread.
     */
    class ThreadTest: public utils::DevUnitTest
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
        ThreadTest(): utils::DevUnitTest("ThreadTest")
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
    
   
};

#endif
