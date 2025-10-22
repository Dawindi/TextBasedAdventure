#include <project/fsm/GameStateMachine.h>

#include "project/fsm/ValidateGameState.h"
#include <array>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
// #include <utility>

using std::array;
using std::cerr;
using std::make_unique;
using std::uint8_t;
using std::unique_ptr;

GameStateMachine::GameStateMachine()
  : BaseStateMachine(), currentContext_(GameContext::StartUpOrError)
{
}

void GameStateMachine::transitionToNextState(InterfaceState* currentState)
{
  if (!currentState)
  {
    throw std::invalid_argument("currentState is null");
  }

  if (currentState->getStateType() ==
      static_cast<uint8_t>(GameStateType::ValidateGameState))
  {
    updateContext(*currentState);
  }
  BaseStateMachine::transitionToNextState(currentState);
}

void GameStateMachine::exitPoint()
{
#ifdef _DEBUG
  cerr << "Exiting GameStateMachine\n";
#endif
}

void GameStateMachine::updateContext(const InterfaceState& currentState)
{
  bool nextContextIsValid = false;
  const auto* validateGameState =
    dynamic_cast<const ValidateGameState*>(&currentState);
  auto nextContext =
    validateGameState->getNextContext(static_cast<uint8_t>(currentContext_));

  if (nextContext == static_cast<uint8_t>(currentContext_))
  {
    return;
  }

  const array<GameContext, 3> validContexts{GameContext::StartUpOrError,
                                            GameContext::GameIsRunning,
                                            GameContext::SaveGame};

  for (const auto& validContext : validContexts)
  {
    if (nextContext == static_cast<uint8_t>(validContext))
    {
      nextContextIsValid = true;
      break;
    }
  }
  if (!nextContextIsValid)
  {
    cerr << "Error: Invalid context transition from "
         << static_cast<unsigned int>(static_cast<uint8_t>(currentContext_))
         << " to " << static_cast<unsigned int>(nextContext) << "\n";
    throw std::runtime_error("Invalid context transition");
  }

#ifdef _DEBUG
  cerr << "Context transition from "
       << static_cast<unsigned int>(static_cast<uint8_t>(currentContext_))
       << " to " << static_cast<unsigned int>(nextContext) << "\n";
#endif

  currentContext_ = static_cast<GameContext>(nextContext);
}
