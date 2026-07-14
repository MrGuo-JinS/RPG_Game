#pragma once

#include <string>
#include <iostream>
#include <cstdlib>

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Fatal,
    Off
};

class Logger {
private:
    LogLevel currentLogLevel;
public:
    Logger(LogLevel level = LogLevel::Info);

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    void setLogLevel(LogLevel level);
    LogLevel getLogLevel() const;

    static std::string LevelToString(LogLevel level);
    static std::string GetCurrentTime();

    template<typename... Args>
    void Log(LogLevel level, Args&&... args) {
        if (level < currentLogLevel) {
            return;
        }

        std::cout << "[" << GetCurrentTime() << "] [" << LevelToString(level) << "] ";
        (std::cout << ... << args) << std::endl;
    }

    template<typename... Args>void Trace(Args&&... args) {Log(LogLevel::Trace, std::forward<Args>(args)...);}
    template<typename... Args>void Debug(Args&&... args) {Log(LogLevel::Debug, std::forward<Args>(args)...);}
    template<typename... Args>void Info(Args&&... args) {Log(LogLevel::Info, std::forward<Args>(args)...);}
    template<typename... Args>void Warning(Args&&... args) {Log(LogLevel::Warning, std::forward<Args>(args)...);}
    template<typename... Args>void Error(Args&&... args) {Log(LogLevel::Error, std::forward<Args>(args)...);}
    template<typename... Args>void Fatal(Args&&... args) {
        Log(LogLevel::Fatal, std::forward<Args>(args)...);
        std::exit(EXIT_FAILURE);
    }
};