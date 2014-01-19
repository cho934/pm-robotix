#include <sstream>
#include <fstream>
#include <stdexcept>
#include "Configuration.hpp"
#include "regex.h"

utils::Configuration::Configuration() : values_()
{}

void
utils::Configuration::load(const std::string & fileName)
{
    std::ifstream ifs;
    ifs.open(fileName.c_str());
    if (!ifs)
    {
        logger().error() << "The file <" << fileName << "> cannot be used as a configuration file" << utils::end;
        throw new ConfigurationException("The file <" + fileName + "> cannot be used as a configuration file");
    }
    std::string line;
    while(std::getline(ifs, line))
    {
        if (! line.empty())
        {
            std::string property, separator, value;
            std::istringstream iss;
            
            iss.str(line);
            iss >> property;
            iss >> separator;
            iss >> value;
            
            if (separator.compare(":") != 0)
            {
                logger().error() << "The configuration is invalid [property:" << property << "] [separator:" << separator << "] [value:" << value << "]" << utils::end;
                throw new ConfigurationException("The configuration for <" + property + "> is invalid");
            }
            else
            {
                this->values_[property] = value;
            }
        }
    }
    
    ifs.close();
}

std::string
utils::Configuration::getString(const std::string & property)
{
    try
    {
        return this->values_.at(property);
    }
    catch(const std::out_of_range& exception)
    {
        throw new ConfigurationException("The property <"+ property +"> doesn't exist");
    }
}

double
utils::Configuration::getDouble(const std::string & property)
{
    double result;
    std::istringstream iss;
    iss.str(this->getString(property));
    iss >> result;

    if (iss.eof())
    {
        return result;
    }
    else
    {
        throw new ConfigurationException("The property <"+ property +"> is not a double");
    }
}

int
utils::Configuration::getInt(const std::string & property)
{
    int result;
    std::istringstream iss;
    iss.str(this->getString(property));
    iss >> result;

    if (iss.eof())
    {
        return result;
    }
    else
    {
        throw new ConfigurationException("The property <"+ property +"> is not a int");
    }
}

void
utils::Configuration::set(const std::string & property, const std::string & value)
{
    this->values_.at(property) = value;
}

void
utils::Configuration::set(const std::string & property, double value)
{
    std::string s;
    std::ostringstream oss;
    oss << value;
    s = oss.str();
    
    this->set(property, s);
}

void
utils::Configuration::set(const std::string & property, int value)
{
    std::string s;
    std::ostringstream oss;
    oss << value;
    s = oss.str();
    
    this->set(property, s);
}
