#include "project/fsm/ValidateGameState.h"

#include "project/fsm/GameStateMachine.h"
#include "project/fsm/InterfaceState.h"
#include "project/fsm/InterfaceStateMachine.h"
#include <iostream>
#include <vector>

using std::cerr;
using std::uint8_t;
using std::vector;

ValidateGameState::ValidateGameState()
  : BaseState(), validNextStates_({GameStateType::HandleErrorState,
                                   GameStateType::StartGameState})
{
}

void ValidateGameState::prepareNextState()
{
  // make unique pointer of HandleErrorState or StartGameState depending on the
  // result of validation
}

uint8_t ValidateGameState::getStateType() const
{
  return static_cast<uint8_t>(GameStateType::ValidateGameState);
}

uint8_t ValidateGameState::getNextContext(const uint8_t& currentContext) const
{
  auto nextContext = static_cast<uint8_t>(GameContext::InvalidContext);
  const auto nextState = const_cast<ValidateGameState*>(this)->getNextState();
  if (!nextState)
  {
    return nextContext;
  }
  if ((nextState->getStateType() &
       static_cast<uint8_t>(GameStateType::HandleErrorState)) != 0U)
  {
    nextContext = static_cast<uint8_t>(GameContext::StartUpOrError);
    return nextContext;
  }
  if ((currentContext & static_cast<uint8_t>(GameContext::StartUpOrError)) !=
      0U)
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

void ValidateGameState::enter(InterfaceStateMachine& stateMachine)
{
  BaseState::enter(stateMachine);

  vector<uint8_t> validTypes;
  for (const auto& state : validNextStates_)
  {
    validTypes.push_back(static_cast<uint8_t>(state));
  }

  setValidStateTypes(validTypes);
}

void ValidateGameState::doActivity() {}