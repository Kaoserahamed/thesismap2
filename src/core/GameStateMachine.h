#pragma once
#include <memory>
#include <vector>

namespace core {
class GameState;

// Manages a stack of game states with push/pop/replace.
class GameStateMachine {
public:
    void push(std::unique_ptr<GameState> state);
    void pop();
    void replace(std::unique_ptr<GameState> state);
    void update(float dt);
    void draw();
    GameState* current() const;

private:
    std::vector<std::unique_ptr<GameState>> m_states;
};
}
