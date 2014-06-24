/*!
 * \file
 * \brief Définition de la classe ApfOutDacTest.
 */

#ifndef TEST_APFDACOUTTEST_HPP
#define TEST_APFDACOUTTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace test
{
    /*!
     * \brief Effectue un test du DAC MAX5821 via le module as_devices de la carte DevLightV2.
     */
    class ApfDacOut : public pmx::ConsoleUnitTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfOutDacTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfDacOut");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfDacOut() : pmx::ConsoleUnitTest("ApfDacOut : Increment DAC [A] & [B] Output on devLightV2 (as_devices)")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfDacOut()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
