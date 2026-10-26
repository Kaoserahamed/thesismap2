#include "states/MainMenuState.h"
#include "states/PlayState.h"
#include "core/GameStateMachine.h"

#include <raylib.h>

void MainMenuState::update(float /*dt*/) {
    if (IsKeyPressed(KEY_ENTER)) {
        m_machine->replace(std::make_unique<PlayState>());
    }
}

void MainMenuState::draw() {
    ClearBackground(DARKGREEN);
    DrawText("MainMenuState", 40, 40, 40, RAYWHITE);
    DrawText("Press ENTER for Play", 40, 100, 20, RAYWHITE);
}
