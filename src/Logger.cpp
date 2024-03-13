#include "Logger.h"

//excellent work chatgpt

Logger::Logger(const std::string &errorFilename, const std::string &successFilename)
    : errorLog(errorFilename, std::ios::trunc), successLog(successFilename, std::ios::trunc) {

    if (!errorLog.is_open() || !successLog.is_open()) {
        std::cerr << "Error opening log files." << std::endl;
    }
}

Logger::~Logger() {
    if (errorLog.is_open()) {
        errorLog.close();
    }
    if (successLog.is_open()) {
        successLog.close();
    }
}

void Logger::logError(const std::string &message) {
    if (errorLog.is_open()) {
        logMessage(errorLog, message);
    } else {
        std::cerr << "Error log file is not open." << std::endl;
    }
}

void Logger::logSuccess(const std::string &message) {
    if (successLog.is_open()) {
        logMessage(successLog, message);
    } else {
        std::cerr << "Success log file is not open." << std::endl;
    }
}

void Logger::logMessage(std::ofstream &logFile, const std::string &message) {
    // Get the current date and time
    std::time_t now = std::time(nullptr);
    char timestamp[100];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    // Log the message with timestamp
    logFile << "[" << timestamp << "] " << message << std::endl;
}
