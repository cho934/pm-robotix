#include "ConfigurationTest.hpp"
#include "dirent.h"

void
test::ConfigurationTest::suite()
{
    this->testLoad();
}

void
test::ConfigurationTest::testLoad()
{
    char currentPath[PATH_MAX];
    getcwd(currentPath, PATH_MAX); 
    
    logger().debug() << "Current directory:" << currentPath << utils::end;
    
    utils::Configuration configuration;
    try
    {
        configuration.load("notexisting.txt");
        this->fail("Configuration.load() doit levée une exception si le fichier demandé n'existe pas");
    }
    catch(utils::ConfigurationException* exception)
    {
        // Do nothing: L'exception doit être générée pour que le test réussisse.
    }
    
    try
    {
        configuration.load("dist/test-configuration-ok.txt");
    }
    catch(std::exception* exception)
    {
        std::ostringstream oss;
        oss << "Erreur fatale durant le chargement de la configuration <" << exception->what() << ">";
        this->fail(oss.str());
    }
    
    this->assert(configuration.getString("first") == "firstValue", "The first value (normal string) is not read properly");
    this->assert(configuration.getString("second") == "second", "The second value (string with spaces) is not read properly");
    this->assert(configuration.getDouble("third") == 0.001, "The third value (double) is not read properly");
}
