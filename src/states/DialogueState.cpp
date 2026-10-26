#include "states/DialogueState.h"
#include "core/GameStateMachine.h"

#include <raylib.h>

void DialogueState::update(float /*dt*/) {
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER)) {
        m_machine->pop();
    }
}

void DialogueState::draw() {
    ClearBackground(PURPLE);
    DrawText("DialogueState", 40, 40, 40, RAYWHITE);
    DrawText("ESC/ENTER: Close", 40, 100, 20, RAYWHITE);
}
