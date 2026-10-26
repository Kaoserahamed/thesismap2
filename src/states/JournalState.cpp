#include "states/JournalState.h"
#include "core/GameStateMachine.h"

#include <raylib.h>

void JournalState::update(float /*dt*/) {
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_TAB)) {
        m_machine->pop();
    }
}

void JournalState::draw() {
    ClearBackground(BROWN);
    DrawText("JournalState", 40, 40, 40, RAYWHITE);
    DrawText("ESC/TAB: Close", 40, 100, 20, RAYWHITE);
}
