#pragma once
#include <string>

namespace util {
// Logs info/warn/error messages to console and logs/game.log with timestamps.
class Log {
public:
    static void init(const std::string& path = "logs/game.log");
    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);
};
}
