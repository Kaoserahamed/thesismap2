#pragma once
#include "core/GameState.h"

// Placeholder PauseState state.
class PauseState : public core::GameState {
public:
    void update(float dt) override;
    void draw() override;
    std::string name() const override { return "PauseState"; }
};
