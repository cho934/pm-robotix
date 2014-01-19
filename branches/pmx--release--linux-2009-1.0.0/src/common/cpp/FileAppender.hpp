#ifndef UTILS_FILEAPPENDER_H
#define	UTILS_FILEAPPENDER_H

#include <string>
#include <fstream>
#include "MemoryAppender.hpp"
#include "Thread.hpp"

namespace utils
{
    class FileAppender : public MemoryAppender, public Thread
    {
    private:
        
        std::ofstream ofs_;
        
        void printData();
        
    public:
        
        FileAppender(const std::string & filename);
        
        virtual ~ FileAppender();
        
        virtual void execute();
        
        virtual void flush();
    };
}

#endif
