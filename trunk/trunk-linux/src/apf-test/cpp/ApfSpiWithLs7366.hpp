/*!
 * \file
 * \brief Définition de la classe ApfSpiWithLs7366.
 */

#ifndef TEST_APFSPIWITH7366_HPP
#define TEST_APFSPIWITH7366_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test SPI.
     */
    class ApfSpiWithLs7366 : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfSpiWithLs7366.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfSpiWithLs7366");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfSpiWithLs7366() : pmx::ConsoleUnitTest("ApfSpiWithLs7366 : test SPI")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfSpiWithLs7366()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
