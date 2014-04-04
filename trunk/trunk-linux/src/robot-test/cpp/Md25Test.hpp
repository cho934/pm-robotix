/*!
 * \file
 * \brief Définition de la classe Md25Test.
 */

#ifndef 	ROBOTTEST_MD25TEST_HPP
#define	ROBOTTEST_MD25TEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
    /*!
     * \brief Effectue un test.
     */
    class Md25Test : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref Md25Test.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::Md25Test");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        Md25Test() : pmx::ConsoleUnitTest("Md25Test : ")
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

#endif
