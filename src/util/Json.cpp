#include "util/Json.h"
#include "util/Log.h"

#include <fstream>

namespace util {
std::optional<nlohmann::json> loadJson(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) {
        Log::error("Failed to open JSON file: " + path);
        return std::nullopt;
    }
    try {
        nlohmann::json j;
        f >> j;
        return j;
    } catch (const std::exception& e) {
        Log::error("Failed to parse JSON " + path + ": " + e.what());
        return std::nullopt;
    }
}
}
