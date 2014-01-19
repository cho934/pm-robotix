#ifndef UTILS_CONFIGURATION_H
#define	UTILS_CONFIGURATION_H

#include <string>
#include <map>
#include "Exception.hpp"
#include "LoggerFactory.hpp"

namespace utils
{
    /*!
     * \brief Exception lancée si la configuration ne peut pas être chargée correctement.
     */
    class ConfigurationException : public Exception
    {
    public:
        ConfigurationException(const std::string & message) : Exception(message)
        {}
        
        virtual ~ ConfigurationException() throw()
        {}
    };
    
    /*!
     * \brief Charge un fichier de configuration.
     */
    class Configuration
    {
    private:
        
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("utils::Configuration");
            return instance;
        }
        
    private:
        
        std::map<std::string, std::string> values_;
        
    public:
        
        Configuration();
        
        virtual ~ Configuration()
        {}
        
        void load(const std::string & fileName);
        
        void set(const std::string & property, const std::string & value);
        
        void set(const std::string & property, double value);
        
        void set(const std::string & property, int value);
        
        std::string getString(const std::string & property);
        
        double getDouble(const std::string & property);
        
        int getInt(const std::string & property);
    };
}

#endif	/* UTILS_CONFIGURATION_H */

