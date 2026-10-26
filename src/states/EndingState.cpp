#include "states/EndingState.h"
#include "core/GameStateMachine.h"

#include <raylib.h>

void EndingState::update(float /*dt*/) {
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER)) {
        if (m_machine) m_machine->pop();
    }
}

void EndingState::draw() {
    ClearBackground(MAROON);
    DrawText("EndingState", 40, 40, 40, RAYWHITE);
    DrawText("ESC/ENTER: Back", 40, 100, 20, RAYWHITE);
}
