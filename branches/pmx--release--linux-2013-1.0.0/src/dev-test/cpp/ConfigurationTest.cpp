/*!
 * \file
 * \brief Implémentation de la classe ConfigurationTest.
 */

#include <dirent.h>
#include "ConfigurationTest.hpp"

void
test::ConfigurationTest::suite()
{
    this->testLoad();
    this->testGetString();
    this->testGetDouble();
    this->testGetInt();
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
        logger().debug() << "load notexisting.txt" << utils::end;
        configuration.load("notexisting.txt");
        this->fail("Configuration.load() doit levée une exception si le fichier demandé n'existe pas");
    }
    catch (utils::ConfigurationException* exception)
    {
        // Do nothing: L'exception doit être générée pour que le test réussisse.
    }

    this->expectedError("utils::Configuration ERROR The file <notexisting.txt> cannot be used as a configuration file");

    try
    {
        logger().debug() << "load test-configuration-ok.txt" << utils::end;
        configuration.load("test-configuration-ok.txt");
    }
    catch (std::exception* exception)
    {
        std::ostringstream oss;
        oss << "Erreur fatale durant le chargement de la configuration <" << exception->what() << ">";
        this->fail(oss.str());
    }

    this->assert(configuration.getString("first") == "firstValue", "The first value (normal string) is not read properly");
    this->assert(configuration.getString("second") == "second", "The second value (string with spaces) is not read properly");
    this->assert(configuration.getDouble("third") == 0.001, "The third value (double) is not read properly");
}

void
test::ConfigurationTest::testGetString()
{
    utils::Configuration configuration;
    configuration.load("test-configuration-ok.txt");

    this->assert(configuration.getString("first") == "firstValue", "The first value (normal string) is not read properly");
    try
    {
        configuration.getString("notexisting");
        this->fail("Configuration.getString() doit levée une exception si la variable demandée n'existe pas");
    }
    catch (std::exception* exception)
    {
        // Do nothing: L'exception doit être générée pour que le test réussisse.
    }
}

void
test::ConfigurationTest::testGetDouble()
{
    utils::Configuration configuration;
    configuration.load("test-configuration-ok.txt");

    this->assert(configuration.getDouble("third") == 0.001, "The third value (double) is not read properly");
    try
    {
        configuration.getDouble("notexisting");
        this->fail("Configuration.getDouble() doit levée une exception si la variable demandée n'existe pas");
    }
    catch (std::exception* exception)
    {
        // Do nothing: L'exception doit être générée pour que le test réussisse.
    }

    try
    {
        configuration.getDouble("first");
        this->fail("Configuration.getDouble() doit levée une exception si la variable demandée existe mais n'est pas un double");
    }
    catch (std::exception* exception)
    {
        // Do nothing: L'exception doit être générée pour que le test réussisse.
    }
}

void
test::ConfigurationTest::testGetInt()
{
    utils::Configuration configuration;
    configuration.load("test-configuration-ok.txt");

    this->assert(configuration.getInt("int") == 10, "The int value is not read properly");
    try
    {
        configuration.getInt("notexisting");
        this->fail("Configuration.getInt() doit levée une exception si la variable demandée n'existe pas");
    }
    catch (std::exception* exception)
    {
        // Do nothing: L'exception doit être générée pour que le test réussisse.
    }

    try
    {
        configuration.getInt("first");
        this->fail("Configuration.getInt() doit levée une exception si la variable demandée existe mais n'est pas un int");
    }
    catch (std::exception* exception)
    {
        // Do nothing: L'exception doit être générée pour que le test réussisse.
    }
}
