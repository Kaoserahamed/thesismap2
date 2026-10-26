#pragma once
#include <raylib.h>
#include <string>
#include <vector>

#include "core/GameStateMachine.h"
#include "core/Input.h"

namespace core {
// Owns the window, main loop, and state machine.
class Game {
public:
    Game();
    ~Game();
    void run();

    GameStateMachine& states() { return m_stateMachine; }
    Input& input() { return m_input; }

private:
    void initWindow();
    void update(float dt);
    void draw();

    GameStateMachine m_stateMachine;
    Input m_input;
    bool m_running = true;

    double m_accumulator = 0.0;
    const double m_fixedDt = 1.0 / 60.0;
};
}
