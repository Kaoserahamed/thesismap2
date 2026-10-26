#pragma once
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace util {
// Loads a JSON file, logging the path and error on failure.
std::optional<nlohmann::json> loadJson(const std::string& path);
}
