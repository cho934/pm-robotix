#include <sstream>
#include <fstream>
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
        throw new ConfigurationException("The file <" + fileName + "> can be used as a configuration file");
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
                logger().info() << "[property:" << property << "] [separator:" << separator << "] [value:" << value << "]" << utils::end;
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
    return this->values_.at(property);
}

double
utils::Configuration::getDouble(const std::string & property)
{
    double result;
    std::istringstream iss;
    iss.str(this->getString(property));
    iss >> result;
    
    return result;
}

int
utils::Configuration::getInt(const std::string & property)
{
    int result;
    std::istringstream iss;
    iss.str(this->getString(property));
    iss >> result;
    
    return result;
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
