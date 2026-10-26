#include "core/Game.h"

#include "core/DebugOverlay.h"
#include "util/Assets.h"
#include "states/BootState.h"
#include "util/Log.h"

#include <raylib.h>

namespace core {
Game::Game() {
    initWindow();
    util::Log::init();
    m_stateMachine.push(std::make_unique<BootState>());
}

Game::~Game() {
    util::Assets::unloadAll();
    CloseWindow();
}

void Game::initWindow() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "Last Train: 03:17");
    SetTargetFPS(0);
}

void Game::run() {
    while (!WindowShouldClose() && m_running) {
        if (IsKeyPressed(KEY_F1)) DebugOverlay::toggle();

        const float frameTime = GetFrameTime();
        m_accumulator += frameTime;
        while (m_accumulator >= m_fixedDt) {
            update(static_cast<float>(m_fixedDt));
            m_accumulator -= m_fixedDt;
        }
        draw();
    }
}

void Game::update(float dt) {
    m_stateMachine.update(dt);
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    m_stateMachine.draw();
    const auto* cur = m_stateMachine.current();
    DebugOverlay::draw(cur ? cur->name() : std::string{}, GetFrameTime());
    EndDrawing();
}
}
