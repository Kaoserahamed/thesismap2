#pragma once
#include <raylib.h>

#include <unordered_map>

namespace core {
// Named input actions so keys can be rebound later.
enum class Action {
    MoveForward,
    MoveBackward,
    MoveLeft,
    MoveRight,
    Sprint,
    Interact,
    OpenJournal,
    Pause
};

class Input {
public:
    Input();
    void bind(Action action, int key);
    bool isDown(Action action) const;
    bool isPressed(Action action) const;
    bool isReleased(Action action) const;

private:
    std::unordered_map<int, int> bindings_;
};
}
