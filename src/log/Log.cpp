#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "log/Log.hpp"

bool Log::debug = false;

Log::Log(const std::string &level) : level(level) {
    filePath = "";
}

Log::~Log() {
    flush();
}

Log &Log::info() {
    static Log instance("INFO");

    return instance;
}

Log &Log::warn() {
    static Log instance("WARN");

    return instance;
}

Log &Log::error() {
    static Log instance("ERROR");

    return instance;
}

Log &Log::line() {
    static Log instance("LINE");

    instance << std::endl;
    return instance;
}

Log &Log::operator<<(std::ostream &(*manip)(std::ostream &)) {
    buffer << manip;
    if (manip == static_cast<std::ostream &(*)(std::ostream &)>(std::endl)) {
        flush();
    }
    return *this;
}

void Log::setDebug(bool value) {
    debug = value;
}

void Log::flushInFile(const std::string &logMessage,
    const std::string &filePath) {
    std::ofstream outFile(filePath, std::ios::app);

    if (outFile.is_open()) {
        outFile << logMessage;
        outFile.close();
    } else {
        std::cerr << "Failed to open log file: " << filePath << std::endl;
    }
}

std::string Log::specialCase() {
    if (level == "LINE")
        return "[==========================================================="
            "===================]\n";
    return "";
}

void Log::flush() {
    std::time_t time_t_now = std::time(nullptr);
    std::tm tm_now;
    std::ostringstream logMessage;
    std::vector<std::string> special = {"LINE"};

    if (!debug)
        return;
    localtime_r(&time_t_now, &tm_now);
    std::tm* tm_ptr = std::localtime(&time_t_now);
    if (tm_ptr != nullptr) {
        tm_now = *tm_ptr;
    } else {
        std::cerr << "Failed to get local time." << std::endl;
        return;
    }
        return;
    if (std::find(special.begin(), special.end(), level) == special.end())
        logMessage << "[" << level << "]\t(" <<std::put_time
            (&tm_now, "%H:%M:%S") << ") → " << buffer.str();
    else
        logMessage << specialCase();
    if (!filePath.empty()) {
        flushInFile(logMessage.str(), filePath);
    } else {
        std::cout << logMessage.str();
    }
    buffer.str("");
    buffer.clear();
}
