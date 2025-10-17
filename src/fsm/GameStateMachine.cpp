#include <project/fsm/GameStateMachine.h>

#include <iostream>
#include <memory>
#include <project/fsm/InitializeState.h>

using std::cerr;

GameStateMachine::GameStateMachine()
  : state_(std::make_unique<InitializeState>()),
    currentContext_(GameContext::StartUpOrError)
{
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
