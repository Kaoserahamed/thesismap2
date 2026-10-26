#include "states/BootState.h"
#include "states/MainMenuState.h"
#include "core/GameStateMachine.h"

#include <raylib.h>

void BootState::update(float /*dt*/) {
    if (IsKeyPressed(KEY_ENTER)) {
        m_machine->replace(std::make_unique<MainMenuState>());
    }
}

void BootState::draw() {
    ClearBackground(DARKBLUE);
    DrawText("BootState", 40, 40, 40, RAYWHITE);
    DrawText("Press ENTER for MainMenu", 40, 100, 20, RAYWHITE);
}
