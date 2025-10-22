#include "project/fsm/SendOutputToUserState.h"

#include "project/fsm/GameStateMachine.h"
#include "project/fsm/InterfaceStateMachine.h"
#include <iostream>

using std::cerr;
using std::uint8_t;
using std::vector;

SendOutputToUserState::SendOutputToUserState()
  : BaseState(), validNextStates_({GameStateType::RequestInputFromUserState})
{
}

void SendOutputToUserState::prepareNextState()
{
  // make unique pointer of type RequestUserInputState
}

uint8_t SendOutputToUserState::getStateType() const
{
  return static_cast<uint8_t>(GameStateType::SendOutputToUserState);
}

void SendOutputToUserState::enter(InterfaceStateMachine& stateMachine)
{
  BaseState::enter(stateMachine);

  vector<uint8_t> validTypes;
  for (const auto& state : validNextStates_)
  {
    validTypes.push_back(static_cast<uint8_t>(state));
  }

  setValidStateTypes(validTypes);
}

void SendOutputToUserState::doActivity()
{
}

void SendOutputToUserState::exit() {}