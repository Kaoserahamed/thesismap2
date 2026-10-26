#include "core/WorldState.h"

#include <nlohmann/json.hpp>

namespace core {
namespace {
nlohmann::json valueToJson(const Value& v) {
    return std::visit([](auto&& x) -> nlohmann::json {
        using T = std::decay_t<decltype(x)>;
        nlohmann::json o;
        if constexpr (std::is_same_v<T, int>) { o["type"] = "int"; o["value"] = x; }
        else if constexpr (std::is_same_v<T, float>) { o["type"] = "float"; o["value"] = x; }
        else if constexpr (std::is_same_v<T, bool>) { o["type"] = "bool"; o["value"] = x; }
        else if constexpr (std::is_same_v<T, std::string>) { o["type"] = "string"; o["value"] = x; }
        return o;
    }, v);
}

Value jsonToValue(const nlohmann::json& j) {
    const std::string type = j.value("type", "");
    if (type == "int") return j.value("value", 0);
    if (type == "float") return j.value("value", 0.0f);
    if (type == "bool") return j.value("value", false);
    if (type == "string") return j.value("value", std::string{});
    return Value{};
}
}

bool WorldState::hasPersistent(const std::string& key) const {
    return persistent.find(key) != persistent.end();
}
bool WorldState::hasVolatile(const std::string& key) const {
    return volatileFlags.find(key) != volatileFlags.end();
}
void WorldState::setPersistent(const std::string& key, const Value& value) { persistent[key] = value; }
void WorldState::setVolatile(const std::string& key, const Value& value) { volatileFlags[key] = value; }
void WorldState::removePersistent(const std::string& key) { persistent.erase(key); }
void WorldState::removeVolatile(const std::string& key) { volatileFlags.erase(key); }

nlohmann::json WorldState::toJson() const {
    nlohmann::json o;
    o["loopCount"] = loopCount;
    nlohmann::json p = nlohmann::json::object();
    for (const auto& kv : persistent) p[kv.first] = valueToJson(kv.second);
    o["persistent"] = p;
    nlohmann::json v = nlohmann::json::object();
    for (const auto& kv : volatileFlags) v[kv.first] = valueToJson(kv.second);
    o["volatile"] = v;
    return o;
}

WorldState WorldState::fromJson(const nlohmann::json& j) {
    WorldState ws;
    ws.loopCount = j.value("loopCount", 0);
    if (j.contains("persistent") && j["persistent"].is_object()) {
        for (auto it = j["persistent"].begin(); it != j["persistent"].end(); ++it) {
            ws.persistent[it.key()] = jsonToValue(it.value());
        }
    }
    if (j.contains("volatile") && j["volatile"].is_object()) {
        for (auto it = j["volatile"].begin(); it != j["volatile"].end(); ++it) {
            ws.volatileFlags[it.key()] = jsonToValue(it.value());
        }
    }
    return ws;
}
}
