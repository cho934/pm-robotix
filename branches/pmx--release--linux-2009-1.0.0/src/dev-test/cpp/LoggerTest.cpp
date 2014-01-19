/*!
 * \file
 * \brief Implémentation de la classe LoggerTest.
 */

#include "LoggerTest.hpp"

void test::LoggerTest::testLogger()
{
    const utils::Logger & logger = utils::LoggerFactory::logger("test::VisualValidation");
    
    //! \todo Transformer ces affichages en test unitaire.
    logger.debug("debug - message de test classique");
    logger.info("info - message de test classique");
    logger.warn("warn - message de test classique");
    logger.error("error - message de test classique");
    
    logger.debug() << "debug - message de test en flux" << utils::end;
    logger.info()  << "info - message de test en flux"  << utils::end;
    logger.warn()  << "warn - message de test en flux"  << utils::end;
    logger.error() << "error - message de test en flux" << utils::end;
}

void test::LoggerTest::suite()
{
    testLogger();
}
