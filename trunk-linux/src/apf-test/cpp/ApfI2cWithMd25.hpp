/*!
 * \file
 * \brief Définition de la classe ApfI2cWithMd25.
 */

#ifndef TEST_APFI2CWITHMD25_HPP
#define TEST_APFI2CWITHMD25_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test pour contrôler la carte de motorisation MD25..
     */
    class ApfI2cWithMd25 : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfSpiWithLs7366.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfI2cWithMd25");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfI2cWithMd25() : pmx::ConsoleUnitTest("ApfI2cWithMd25 : test MD25")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfI2cWithMd25()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
