// -----------------------------------------------------------------------------
// depends_on.cpp 
// -----------------------------------------------------------------------------
// 
// (C) Copyright Ulf Ejlertsson 2010.
// 

#include <iostream>
#include <fstream>

template <typename T>
struct DependsOn
{
    DependsOn()
    {
        T::instance();
    }
};

class Logger
{
 public:
    static Logger& instance()
    {
        static Logger logger;
        return logger;
    }

    void log(const char* msg)
    {
        out_ << msg << std::endl;
    }

 private:
    Logger() : out_("depends_on.log") { }

    std::ofstream out_;
};

class Connection : DependsOn<Logger>
{
 public:
    static Connection& instance()
    {
        static Connection connection;
        return connection;
    }

 private:
    ~Connection()
    {
        Logger::instance().log("Connection closed");
    }
};

int main(int argc, char* argv[])
{
    Connection::instance();
}
