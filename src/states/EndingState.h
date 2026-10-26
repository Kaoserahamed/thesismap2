#pragma once
#include "core/GameState.h"

// Placeholder EndingState state.
class EndingState : public core::GameState {
public:
    void update(float dt) override;
    void draw() override;
    std::string name() const override { return "EndingState"; }
};
