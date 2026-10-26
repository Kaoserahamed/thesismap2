#include "core/GameStateMachine.h"
#include "core/GameState.h"

namespace core {
void GameStateMachine::push(std::unique_ptr<GameState> state) {
    if (state) {
        state->setMachine(this);
        state->onEnter();
        m_states.push_back(std::move(state));
    }
}

void GameStateMachine::pop() {
    if (!m_states.empty()) {
        m_states.back()->onExit();
        m_states.pop_back();
    }
}

void GameStateMachine::replace(std::unique_ptr<GameState> state) {
    pop();
    push(std::move(state));
}

void GameStateMachine::update(float dt) {
    if (!m_states.empty()) m_states.back()->update(dt);
}

void GameStateMachine::draw() {
    if (!m_states.empty()) m_states.back()->draw();
}

GameState* GameStateMachine::current() const {
    if (m_states.empty()) return nullptr;
    return m_states.back().get();
}
}
