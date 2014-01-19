/*!#include "LoggerFactory.hpp"
 * \file
 * \brief Définition de la classe DistanceDetectorTest.
 */

#ifndef TEST_DISTANCEDETECTORTEST_HPP
#define	TEST_DISTANCEDETECTORTEST_HPP


#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Test du GP2 de détection de l'adversaire.
     */
    class DistanceDetectorTest : public pmx::RobotTest
    {
    private:
        
        /*!
         * \return Trace associé à la classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::DistanceDetectorTest");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        DistanceDetectorTest() : pmx::RobotTest("Test d'un détecteur de distance GP2")
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ DistanceDetectorTest()
        {}
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
        
    };
};

#endif
