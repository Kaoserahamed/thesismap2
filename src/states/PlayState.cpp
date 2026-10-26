#include "states/PlayState.h"
#include "states/PauseState.h"
#include "states/JournalState.h"
#include "core/GameStateMachine.h"

#include <raylib.h>

void PlayState::update(float /*dt*/) {
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P)) {
        m_machine->push(std::make_unique<PauseState>());
    } else if (IsKeyPressed(KEY_J)) {
        m_machine->push(std::make_unique<JournalState>());
    }
}

void PlayState::draw() {
    ClearBackground(DARKGRAY);
    DrawText("PlayState", 40, 40, 40, RAYWHITE);
    DrawText("ESC/P: Pause  J: Journal", 40, 100, 20, RAYWHITE);
}
