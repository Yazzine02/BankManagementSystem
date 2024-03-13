#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <ctime>

//I was feeling lazy to relearn how to manipulate files in c++, thank you so much chatgpt <3

class Logger {
private:
    std::ofstream errorLog;
    std::ofstream successLog;

public:
    Logger(const std::string &errorFilename, const std::string &successFilename);
    ~Logger();

    void logError(const std::string &message);
    void logSuccess(const std::string &message);

private:
    void logMessage(std::ofstream &logFile, const std::string &message);
};

#endif // LOGGER_H
