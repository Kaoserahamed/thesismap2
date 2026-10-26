#pragma once
#include "core/GameState.h"

// Placeholder DialogueState state.
class DialogueState : public core::GameState {
public:
    void update(float dt) override;
    void draw() override;
    std::string name() const override { return "DialogueState"; }
};
