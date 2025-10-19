#include "project/fsm/SendOutputToUserState.h"

#include "project/fsm/BaseState.h"
#include "project/fsm/GameStateMachine.h"
#include "project/fsm/InterfaceState.h"
#include "project/fsm/InterfaceStateMachine.h"
#include <iostream>
#include <utility>
#include <vector>

using std::cerr;
using std::move;
using std::uint8_t;
using std::unique_ptr;
using std::vector;

SendOutputToUserState::SendOutputToUserState()
  : nextState_(nullptr), stateMachine_(nullptr),
    validNextStates_({GameStateType::RequestInputFromUserState})
{
}

void SendOutputToUserState::enter(InterfaceStateMachine& stateMachine)
{
  stateMachine_ = &stateMachine;
#ifdef _DEBUG
  {
    cerr << "Entering SendOutputToUserState \n";
  }
  // If stateMachine_ is null, print an error message
  if (stateMachine_ == nullptr)
  {
    cerr << "Error: stateMachine_ is null in SendOutputToUserState::enter\n";
  }
  // Otherwise, print the address of stateMachine_ and the inherited type
  else
  {
    cerr << "stateMachine_ address: " << stateMachine_ << "\n";
    cerr << "Inherited type: " << typeid(*stateMachine_).name() << "\n";
  }
#endif
}

unique_ptr<InterfaceState> SendOutputToUserState::getNextState()
{
  return std::move(nextState_);
}

uint8_t SendOutputToUserState::getStateType() const
{
  return static_cast<std::uint8_t>(GameStateType::SendOutputToUserState);
}

void SendOutputToUserState::doActivity()
{
  // Implementation for the main activity of the Initialize state
}

void SendOutputToUserState::setNextState() {}

void SendOutputToUserState::exit() { nextState_.reset(nullptr); }