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
  : currentContext_(GameContext::StartUpOrError)
{
}

void GameStateMachine::transitionToNextState(
  unique_ptr<InterfaceState> currentState)
{
  bool nextContextIsValid = false;
  uint8_t nextContext = UINT8_MAX;

  if (currentState && currentState->getStateType() ==
                        static_cast<uint8_t>(GameStateType::ValidateGameState))
  {
    auto* validateGameState =
      dynamic_cast<ValidateGameState*>(currentState.get());
    nextContext =
      validateGameState->getNextContext(static_cast<uint8_t>(currentContext_));
    const array<GameContext, 3> validContexts{GameContext::StartUpOrError,
                                              GameContext::GameIsRunning,
                                              GameContext::SaveGame};

    if (nextContext !=
        static_cast<uint8_t>(currentContext_)) // fixed comparison
    {
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
    }
  }

  BaseStateMachine::transitionToNextState(std::move(currentState));

  if (nextContextIsValid)
  {
#ifdef _DEBUG
    cerr << "Updating game context to "
         << static_cast<unsigned int>(nextContext) << "\n";
#endif
    currentContext_ = static_cast<GameContext>(nextContext);
  }
}

void GameStateMachine::exitPoint()
{
#ifdef _DEBUG
  cerr << "Exiting GameStateMachine\n";
#endif
}
