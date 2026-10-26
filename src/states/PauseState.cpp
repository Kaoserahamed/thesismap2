#include "states/PauseState.h"
#include "core/GameStateMachine.h"

#include <raylib.h>

void PauseState::update(float /*dt*/) {
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_P)) {
        m_machine->pop();
    }
}

void PauseState::draw() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));
    DrawText("PauseState", 40, 40, 40, RAYWHITE);
    DrawText("ESC/ENTER/P: Resume", 40, 100, 20, RAYWHITE);
}
