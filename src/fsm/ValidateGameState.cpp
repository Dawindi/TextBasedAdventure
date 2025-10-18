#include "project/fsm/ValidateGameState.h"

#include "project/fsm/GameStateMachine.h"
#include <iostream>
#include <project/fsm/InterfaceState.h>
#include <utility>

using std::cerr;

ValidateGameState::ValidateGameState() : nextState_(nullptr) {}

void ValidateGameState::enter()
{
#if defined(_DEBUG)
  {
    cerr << "Entering ValidateGameState \n";
  }
#endif
}

std::unique_ptr<InterfaceState> ValidateGameState::getNextState()
{
  return std::move(nextState_);
}

const std::uint8_t ValidateGameState::getStateType() const
{
  return static_cast<std::uint8_t>(GameStateType::ValidateGameState);
}

const uint8_t
ValidateGameState::getNextContext(const uint8_t& currentContext) const
{
  uint8_t nextContext = static_cast<uint8_t>(GameContext::InvalidContext);
  if (!nextState_)
  {
    return nextContext;
  }
  else if (nextState_->getStateType() ==
           static_cast<std::uint8_t>(GameStateType::HandleErrorState))
  {
    nextContext = static_cast<uint8_t>(GameContext::StartUpOrError);
  }
  else if (currentContext == static_cast<uint8_t>(GameContext::StartUpOrError))
  {
    nextContext = static_cast<uint8_t>(GameContext::GameIsRunning);
  }
  else if (currentContext == static_cast<uint8_t>(GameContext::GameIsRunning))
  {
    nextContext = static_cast<uint8_t>(GameContext::SaveGame);
  }
  else if (currentContext == static_cast<uint8_t>(GameContext::SaveGame))
  {
    nextContext = static_cast<uint8_t>(GameContext::GameIsRunning);
  }
  return nextContext;
}

void ValidateGameState::doActivity()
{
  // Implementation for the main activity of the Validate state
}

void ValidateGameState::setNextState()
{
  // Implementation for determining the next state from Validate state
  // Currently, there is only one valid state to transition to
  // That is state 2: SendOutputToUserState
}