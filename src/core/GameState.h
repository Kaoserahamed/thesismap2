#pragma once
#include <memory>
#include <string>

namespace core {
class GameStateMachine;

// Abstract game state.
class GameState {
public:
    virtual ~GameState() = default;
    virtual void onEnter() {}
    virtual void onExit() {}
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
    virtual std::string name() const { return "State"; }
    void setMachine(GameStateMachine* m) { m_machine = m; }
protected:
    GameStateMachine* m_machine = nullptr;
};
}
