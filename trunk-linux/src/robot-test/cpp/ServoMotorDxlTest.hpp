/*!
 * \file
 * \brief Définition de la classe ServoMotorDxlTest.
 */

#ifndef ROBOTTEST_SERVOMOTORDXLTEST_HPP
#define	ROBOTTEST_SERVOMOTORDXLTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
    /*!
     * \brief Effectue un test avec les servo AX12.
     */
    class ServoMotorDxlTest : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorDxlTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::ServoMotorDxlTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ServoMotorDxlTest() : pmx::ConsoleUnitTest("ServoMotorDxlTest : AX12")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ServoMotorDxlTest()
        {
        }

        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
