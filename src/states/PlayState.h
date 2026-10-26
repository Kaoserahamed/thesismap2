#pragma once
#include "core/GameState.h"

// Placeholder PlayState state.
class PlayState : public core::GameState {
public:
    void update(float dt) override;
    void draw() override;
    std::string name() const override { return "PlayState"; }
};
