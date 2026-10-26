#include "core/EventBus.h"

namespace core {
EventBus::Token EventBus::subscribe(const std::string& id, EventCallback callback) {
    const Token t = nextToken_++;
    subscriptions_.push_back({t, id, std::move(callback)});
    return t;
}

void EventBus::unsubscribe(Token token) {
    for (size_t i = 0; i < subscriptions_.size();) {
        if (subscriptions_[i].token == token) {
            subscriptions_.erase(subscriptions_.begin() + static_cast<std::ptrdiff_t>(i));
        } else {
            ++i;
        }
    }
}

void EventBus::publish(const std::string& id, const EventPayload& payload) {
    for (const auto& s : subscriptions_) {
        if (s.id == id && s.callback) s.callback(payload);
    }
}
}
