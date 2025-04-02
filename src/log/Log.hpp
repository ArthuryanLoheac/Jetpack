/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Log
*/

#pragma once

#include <sstream>
#include <string>

class Log {
 public:
    explicit Log(const std::string &level);
    ~Log();
    std::string &getFilePath();
    static Log &info();
    static Log &warn();
    static Log &error();
    static Log &line();
    template <typename T>
    Log &operator<<(const T &message);
    Log &operator<<(std::ostream &(*manip)(std::ostream &));
    static void setFilePath(const std::string &path);
    static void setDebug(bool value);
 private:
    void flush();
    void flushInFile(const std::string &logMessage,
        const std::string &filePath);
    std::string filePath;
    std::string specialCase();
    std::string level;
    std::ostringstream buffer;
    static bool debug;
};

template <typename T>
Log &Log::operator<<(const T &message) {
    if (!debug) return *this;
    buffer << message;
    return *this;
}
