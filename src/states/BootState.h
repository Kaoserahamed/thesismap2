#pragma once
#include "core/GameState.h"

namespace core { class GameStateMachine; }

// Placeholder boot state.
class BootState : public core::GameState {
public:
    void update(float dt) override;
    void draw() override;
    std::string name() const override { return "BootState"; }
};
