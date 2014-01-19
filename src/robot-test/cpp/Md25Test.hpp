/*!
 * \file
 * \brief Définition de la classe Md25Test.
 */

#ifndef TEST_MD25TEST_HPP
#define	TEST_MD25TEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"
#include "Md25.hpp"

namespace test
{
    /*!
     * \brief Effectue un test de la carte MD25.
     */
    class Md25Test : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfInAdcTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::Md25Test");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        Md25Test() : pmx::RobotTest("MD25 : Md25Test : Use I2C on devLightV2 (as_devices)")
        {

        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~Md25Test()
        {
        }

        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);

    };
};



#endif	/* TEST_MD25TEST_HPP */

