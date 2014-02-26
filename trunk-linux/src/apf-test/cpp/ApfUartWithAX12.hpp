/*!
 * \file
 * \brief Définition de la classe ApfUartWithAX12.
 */

#ifndef TEST_APFUARTWITHAX12_HPP
#define TEST_APFUARTWITHAX12_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test pour contrôler les servomoteurs AX12.
     */
    class ApfUartWithAX12 : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfSpiWithLs7366.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfUartWithAX12");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfUartWithAX12() : pmx::ConsoleUnitTest("ApfUartWithAX12 : test AX12")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfUartWithAX12()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
