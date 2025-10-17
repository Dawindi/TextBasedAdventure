#include "project/fsm/InitializeState.h"

#include "project/fsm/GameStateMachine.h"
#include <iostream>
#include <utility>

using std::cerr;

InitializeState::InitializeState() : nextState_(nullptr) {}

void InitializeState::enter()
{
#if defined(_DEBUG)
  {
    cerr << "Entering InitializeState \n";
  }
#endif
}

std::unique_ptr<InterfaceState> InitializeState::getNextState()
{
  return std::move(nextState_);
}

std::uint8_t InitializeState::getStateType()
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

bool InitializeState::nextStateIsValid()
{
  for (const auto& validGameStateType : validNextStates_)
  {
    if (static_cast<std::uint8_t>(validGameStateType) ==
        nextState_->getStateType())
    {
      return true;
    }
  }
#if defined(_DEBUG)
  {
    cerr << "Next state is state "
         << static_cast<std::uint8_t>(nextState_->getStateType())
         << " and that state is invalid  \n";
  }
#endif
  return false;
}

void InitializeState::exit() { nextState_.reset(nullptr); }