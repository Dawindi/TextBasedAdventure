#include "project/fsm/BaseStateMachine.h"

#include "project/fsm/InterfaceState.h"
#include <exception>
#include <iostream>
#include <memory>
#include <utility>

using std::cerr;
using std::unique_ptr;

BaseStateMachine::BaseStateMachine()
  : state_(nullptr), previousStateType_(UINT8_MAX)
{
}

void BaseStateMachine::run(unique_ptr<InterfaceState> Startstate)
{
  state_ = std::move(Startstate);
  entryPoint();
  exitPoint();
}

std::uint8_t BaseStateMachine::getPreviousStateType() const
{
  return previousStateType_;
}

const InterfaceState& BaseStateMachine::getCurrentState() const
{
  return state_ ? *state_
                : throw std::runtime_error("Current state is nullptr");
}

void BaseStateMachine::entryPoint()
{
#ifdef _DEBUG
  {
    cerr << "Entering state machine\n";
  }
#endif
  while (state_)
  {
    try
    {
      state_->process(*this);
      transitionToNextState(state_.get());
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
#ifdef _DEBUG
  {
    cerr << "Exiting state machine\n";
  }
#endif
}

void BaseStateMachine::setPreviousStateType(std::uint8_t& stateType)
{
  previousStateType_ = stateType;
}

void BaseStateMachine::transitionToNextState(InterfaceState* currentState)
{
  if (currentState)
  {
#ifdef _DEBUG
    {
      cerr << "Transitioning from current state to next state\n";
    }
#endif

    // Get the next state
    unique_ptr<InterfaceState> nextState =
      std::move(currentState->getNextState());

    // Clean up current state
    currentState->exit();

    // Reset current state and move next state into place
    state_ = std::move(nextState);

#ifdef _DEBUG
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
