#pragma once
#include "core/GameState.h"

// Placeholder main menu state.
class MainMenuState : public core::GameState {
public:
    void update(float dt) override;
    void draw() override;
    std::string name() const override { return "MainMenuState"; }
};
