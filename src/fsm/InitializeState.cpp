#include "project/fsm/InitializeState.h"

#include "project/fsm/GameStateMachine.h"
#include <iostream>
#include <project/fsm/BaseState.h>
#include <project/fsm/InterfaceState.h>
#include <utility>
#include <vector>

using std::cerr;
using std::move;
using std::uint8_t;
using std::unique_ptr;
using std::vector;

InitializeState::InitializeState() : nextState_(nullptr) {}

void InitializeState::enter()
{
#if defined(_DEBUG)
  {
    cerr << "Entering InitializeState \n";
  }
#endif
}

unique_ptr<InterfaceState> InitializeState::getNextState()
{
  return std::move(nextState_);
}

const uint8_t InitializeState::getStateType() const
{
  return static_cast<std::uint8_t>(GameStateType::InitializeState);
}

void InitializeState::doActivity()
{
  // Implementation for the main activity of the Initialize state
}

void InitializeState::setNextState()
{
  // Implementation for determining the next state from Initialize state
  // Currently, there is only one valid state to transition to
  // That is state 2: SendOutputToUserState
}

void InitializeState::exit() { nextState_.reset(nullptr); }