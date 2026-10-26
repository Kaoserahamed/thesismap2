#pragma once
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>

namespace core {
using Value = std::variant<int, float, bool, std::string>;

// Shared persistent/volatile state plus loop counter. No game logic here.
class WorldState {
public:
    std::unordered_map<std::string, Value> persistent;
    std::unordered_map<std::string, Value> volatileFlags;
    int loopCount = 0;

    bool hasPersistent(const std::string& key) const;
    bool hasVolatile(const std::string& key) const;

    template <typename T>
    std::optional<T> getPersistent(const std::string& key) const {
        auto it = persistent.find(key);
        if (it == persistent.end()) return std::nullopt;
        if (const T* p = std::get_if<T>(&it->second)) return *p;
        return std::nullopt;
    }
    template <typename T>
    std::optional<T> getVolatile(const std::string& key) const {
        auto it = volatileFlags.find(key);
        if (it == volatileFlags.end()) return std::nullopt;
        if (const T* p = std::get_if<T>(&it->second)) return *p;
        return std::nullopt;
    }

    void setPersistent(const std::string& key, const Value& value);
    void setVolatile(const std::string& key, const Value& value);
    void removePersistent(const std::string& key);
    void removeVolatile(const std::string& key);

    nlohmann::json toJson() const;
    static WorldState fromJson(const nlohmann::json& j);
};
}
