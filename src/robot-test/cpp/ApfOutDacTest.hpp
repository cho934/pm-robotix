/*!
 * \file
 * \brief Définition de la classe ApfOutDacTest.
 */

#ifndef TEST_APFOUTDACTEST_HPP
#define TEST_APFOUTDACTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"



namespace test
{
    /*!
     * \brief Effectue un test du DAC MAX5821 via le module as_devices de la carte DevLightV2.
     */
    class ApfOutDacTest : public pmx::RobotTest
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfOutDacTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfOutDacTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfOutDacTest() : pmx::RobotTest("APFOUT : ApfOutDacTest : Use DAC [A] & [B] Output on devLightV2 (as_devices)")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfOutDacTest()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);
    };
};

#endif
