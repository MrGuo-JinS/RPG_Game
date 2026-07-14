#include "utils/Logger.hpp"
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

Logger::Logger(LogLevel level) : currentLogLevel(level) {}

void Logger::setLogLevel(LogLevel level) {
    currentLogLevel = level;
}

LogLevel Logger::getLogLevel() const {
    return currentLogLevel;
}

std::string Logger::LevelToString(LogLevel level){
    switch (level) {
        case LogLevel::Trace: return "TRACE";
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info: return "INFO";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Error: return "ERROR";
        case LogLevel::Fatal: return "FATAL";
        default: return "UNKNOWN";
    }
}

std::string Logger::GetCurrentTime(){
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#if defined(_MSC_VER)
    localtime_s(&tm, &now_time);
#else
    std::tm* ptm = std::localtime(&now_time);
    if (ptm)
        tm = *ptm;
    else
        tm = std::tm{};
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}