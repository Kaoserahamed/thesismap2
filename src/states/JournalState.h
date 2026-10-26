#pragma once
#include "core/GameState.h"

// Placeholder JournalState state.
class JournalState : public core::GameState {
public:
    void update(float dt) override;
    void draw() override;
    std::string name() const override { return "JournalState"; }
};
