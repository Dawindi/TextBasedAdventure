#include <project/fsm/GameStateMachine.h>

#include <array>
#include <iostream>
#include <memory>
#include <project/fsm/InitializeState.h>
#include <project/fsm/ValidateGameState.h>
#include <stdexcept>

using std::array;
using std::cerr;
using std::make_unique;
using std::uint8_t;
using std::unique_ptr;

GameStateMachine::GameStateMachine()
  : state_(make_unique<InitializeState>()),
    currentContext_(GameContext::StartUpOrError)
{
}

void GameStateMachine::transitionToNextState()
{
  bool nextContextIsValid = false;
  uint8_t nextContext = UINT8_MAX;
  bool stateIsNotNullptr = state_ != nullptr;
  bool stateIsOfTypeValidateGameState =
    state_->getStateType() ==
    static_cast<uint8_t>(GameStateType::ValidateGameState);
  if (stateIsNotNullptr && stateIsOfTypeValidateGameState)
  {
    auto validateGameState = dynamic_cast<ValidateGameState*>(state_.get());
    nextContext =
      validateGameState->getNextContext(static_cast<uint8_t>(currentContext_));
    const array<GameContext, 3> validContexts{GameContext::StartUpOrError,
                                              GameContext::GameIsRunning,
                                              GameContext::SaveGame};
    if (!nextContext == static_cast<uint8_t>(currentContext_))
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
             << static_cast<uint8_t>(currentContext_) << " to " << nextContext
             << "\n";
        throw std::runtime_error("Invalid context transition");
      }
    }
  }
  BaseStateMachine::transitionToNextState();
  if (nextContextIsValid)
  {

#if defined(_DEBUG)
    cerr << "Updating game context to " << static_cast<uint8_t>(nextContext)
         << "\n";
#endif

    currentContext_ = static_cast<GameContext>(nextContext);
  }
}

void GameStateMachine::exitPoint()
{
#if defined(_DEBUG)
  {
    cerr << "Exiting GameStateMachine\n";
  }
#endif

  state_.reset(nullptr);
}
