#include "core/Input.h"

namespace core {
Input::Input() {
    bind(Action::MoveForward, KEY_W);
    bind(Action::MoveBackward, KEY_S);
    bind(Action::MoveLeft, KEY_A);
    bind(Action::MoveRight, KEY_D);
    bind(Action::Sprint, KEY_LEFT_SHIFT);
    bind(Action::Interact, KEY_E);
    bind(Action::OpenJournal, KEY_TAB);
    bind(Action::Pause, KEY_ESCAPE);
}

void Input::bind(Action action, int key) {
    bindings_[static_cast<int>(action)] = key;
}

bool Input::isDown(Action action) const {
    auto it = bindings_.find(static_cast<int>(action));
    if (it == bindings_.end()) return false;
    return IsKeyDown(it->second);
}

bool Input::isPressed(Action action) const {
    auto it = bindings_.find(static_cast<int>(action));
    if (it == bindings_.end()) return false;
    return IsKeyPressed(it->second);
}

bool Input::isReleased(Action action) const {
    auto it = bindings_.find(static_cast<int>(action));
    if (it == bindings_.end()) return false;
    return IsKeyReleased(it->second);
}
}
