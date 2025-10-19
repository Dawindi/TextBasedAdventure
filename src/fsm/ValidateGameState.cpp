#include "project/fsm/ValidateGameState.h"

#include "project/fsm/GameStateMachine.h"
#include "project/fsm/InterfaceState.h"
#include "project/fsm/InterfaceStateMachine.h"
#include <iostream>
#include <utility>

using std::cerr;
using std::uint8_t;
using std::unique_ptr;

ValidateGameState::ValidateGameState()
  : nextState_(nullptr), stateMachine_(nullptr)
{
}

void ValidateGameState::enter(InterfaceStateMachine& stateMachine)
{
  stateMachine_ = &stateMachine;
#ifdef _DEBUG
  cerr << "Entering ValidateGameState \n";
  // If stateMachine_ is null, print an error message
  if (stateMachine_ == nullptr)
  {
    cerr << "Error: stateMachine_ is null in SendOutputToUserState::enter\n";
  }
  // Otherwise, print the address of stateMachine_ and the inherited type
  else
  {
    cerr << "stateMachine_ address: " << stateMachine_ << "\n";
    cerr << "Inherited type: " << typeid(*stateMachine_).name() << "\n";
  }
#endif
}

unique_ptr<InterfaceState> ValidateGameState::getNextState()
{
  return std::move(nextState_);
}

uint8_t ValidateGameState::getStateType() const
{
  return static_cast<uint8_t>(GameStateType::ValidateGameState);
}

uint8_t ValidateGameState::getNextContext(const uint8_t& currentContext) const
{
  auto nextContext = static_cast<uint8_t>(GameContext::InvalidContext);
  if (!nextState_)
  {
    return nextContext;
  }
  if ((nextState_->getStateType() & static_cast<uint8_t>(GameStateType::HandleErrorState)) != 0U)
  {
    nextContext = static_cast<uint8_t>(GameContext::StartUpOrError);
    return nextContext;
  }
  if ((currentContext & static_cast<uint8_t>(GameContext::StartUpOrError)) != 0U)
  {
    nextContext = static_cast<uint8_t>(GameContext::GameIsRunning);
    return nextContext;
  }
  if ((currentContext & static_cast<uint8_t>(GameContext::GameIsRunning)) != 0U)
  {
    nextContext = static_cast<uint8_t>(GameContext::SaveGame);
    return nextContext;
  }
  if ((currentContext & static_cast<uint8_t>(GameContext::SaveGame)) != 0U)
  {
    nextContext = static_cast<uint8_t>(GameContext::GameIsRunning);
    return nextContext;
  }
  return nextContext;
}

void ValidateGameState::doActivity() {}

void ValidateGameState::setNextState() {}