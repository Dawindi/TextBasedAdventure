#include <project/fsm/BaseStateMachine.h>

#include <exception>
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
    try
    {
      state_->process();
      transitionToNextState();
    }
    catch (const std::exception& e)
    {
      cerr << "Context: State Machine \n"
           << "Standard Exception : " << e.what() << "\n ";
      state_.reset(nullptr);
      break;
    }
    catch (...)
    {
      cerr << "Context: State Machine \n"
           << "Unknown Exception\n";
      state_.reset(nullptr);
      break;
    }
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

    // Transition to the next state
    state_ = std::move(state_->getNextState());

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
