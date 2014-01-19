/*!
 * \file
 * \brief Définition de la classe ApfInTest.
 */

#ifndef TEST_APFINTEST_HPP
#define TEST_APFINTEST_HPP

#include "RobotTest.hpp"
#include "LoggerFactory.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string>

namespace test
{
    /*!
     * \brief Effectue un test de clignotement de LED sur tous les pads de sorties de la carte DevLightV2.
     */
    class ApfInTest : public pmx::RobotTest
    {
    private:

        static std::string INPUT_PORT_PATH;
        static std::string INPUT_PORT_PATH2;
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfInTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfInTest");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfInTest() : pmx::RobotTest("APFIN  : ApfInTest : Read interruption on devLightV2 pad (with fstream)")
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfInTest()
        {
        }

        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);

    };
};

#endif
