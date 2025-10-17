#include <project/fsm/BaseStateMachine.h>

#include <iostream>
#include <memory>
#include <project/fsm/InterfaceState.h>
#include <utility>

using std::cerr;

BaseStateMachine::BaseStateMachine() : state_(nullptr) {}

void BaseStateMachine::run()
{
  entryPoint();
  exitPoint();
}

void BaseStateMachine::entryPoint()
{
#if defined(_DEBUG)
  {
    cerr << "Entering state machine\n";
  }
#endif
  while (state_)
  {
    state_->process();
    transitionToNextState();
  }
}

void BaseStateMachine::exitPoint()
{
#if defined(_DEBUG)
  {
    cerr << "Exiting state machine\n";
  }
#endif
}

void BaseStateMachine::transitionToNextState()
{
  if (state_)
  {
#if defined(_DEBUG)
    {
      cerr << "Transitioning from current state to next state\n";
    }
#endif

    std::unique_ptr<InterfaceState> nextState =
      std::move(state_->getNextState());
    state_.release();
    state_ = std::move(nextState);

#if defined(_DEBUG)
    {
      if (!state_)
      {
        cerr << "The next state is a nullptr\n";
      }
    }
#endif
  }
  else
  {
    cerr << "Transitioning to next called from nullptr state?";
  }
}
