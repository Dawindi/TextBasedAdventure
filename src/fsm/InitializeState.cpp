#include "project/fsm/InitializeState.h"

#include "project/fsm/BaseState.h"
#include "project/fsm/GameStateMachine.h"
#include "project/fsm/InterfaceStateMachine.h"
#include "project/fsm/SendOutputToUserState.h"
#include <iostream>
#include <memory>
#include <vector>

using std::cerr;
using std::uint8_t;
using std::vector;

InitializeState::InitializeState()
  : BaseState(), validNextStates_({GameStateType::SendOutputToUserState})
{
}

void InitializeState::prepareNextState()
{
  setNextState(std::make_unique<SendOutputToUserState>());
}

uint8_t InitializeState::getStateType() const
{
  return static_cast<std::uint8_t>(GameStateType::InitializeState);
}

void InitializeState::enter(InterfaceStateMachine& stateMachine)
{
  BaseState::enter(stateMachine);

  vector<uint8_t> validTypes;
  for (const auto& state : validNextStates_)
  {
    validTypes.push_back(static_cast<uint8_t>(state));
  }

  setValidStateTypes(validTypes);
}

void InitializeState::doActivity()
{
  // Implementation for the main activity of the Initialize state
}