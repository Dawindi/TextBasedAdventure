#include "project/fsm/InitializeState.h"

#include "project/fsm/BaseState.h"
#include "project/fsm/GameStateMachine.h"
#include "project/fsm/InterfaceState.h"
#include "project/fsm/InterfaceStateMachine.h"
#include "project/fsm/SendOutputToUserState.h"
#include <iostream>
#include <utility>
#include <vector>

using std::cerr;
using std::make_unique;
using std::move;
using std::uint8_t;
using std::unique_ptr;
using std::vector;

InitializeState::InitializeState()
  : nextState_(nullptr), stateMachine_(nullptr),
    validNextStates_({GameStateType::SendOutputToUserState})
{
}

void InitializeState::enter(InterfaceStateMachine& stateMachine)
{
  stateMachine_ = &stateMachine;
#ifdef _DEBUG
  {
    cerr << "Entering InitializeState \n";
    // If stateMachine_ is null, print an error message
    if (stateMachine_ == nullptr)
    {
      cerr << "Error: stateMachine_ is null in InitializeState::enter\n";
    }
    // Otherwise, print the address of stateMachine_ and the inherited type
    else
    {
      cerr << "stateMachine_ address: " << stateMachine_ << "\n";
      cerr << "Inherited type: " << typeid(*stateMachine_).name() << "\n";
    }
  }
#endif
}

unique_ptr<InterfaceState> InitializeState::getNextState()
{
  return std::move(nextState_);
}

uint8_t InitializeState::getStateType() const
{
  return static_cast<std::uint8_t>(GameStateType::InitializeState);
}

void InitializeState::doActivity()
{
  // Implementation for the main activity of the Initialize state
}

void InitializeState::setNextState()
{
  nextState_ = make_unique<SendOutputToUserState>();
}

void InitializeState::exit() { nextState_.reset(nullptr); }