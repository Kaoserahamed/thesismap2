#pragma once
#include <cstddef>
#include <functional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace core {
using EventPayload = std::variant<int, float, bool, std::string>;
using EventCallback = std::function<void(const EventPayload&)>;

// Type-safe publish/subscribe using string event ids and a small variant payload.
class EventBus {
public:
    using Token = size_t;

    Token subscribe(const std::string& id, EventCallback callback);
    void unsubscribe(Token token);
    void publish(const std::string& id, const EventPayload& payload = EventPayload{});

private:
    struct Subscription {
        Token token = 0;
        std::string id;
        EventCallback callback;
    };
    std::vector<Subscription> subscriptions_;
    Token nextToken_ = 1;
};
}
