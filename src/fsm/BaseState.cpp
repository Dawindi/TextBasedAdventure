#include "project/fsm/BaseState.h"

#include "project/fsm/InterfaceState.h"
#include "project/fsm/InterfaceStateMachine.h"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <utility>

using std::cerr;
using std::string;
using std::uint8_t;
using std::unique_ptr;
using std::vector;

void StateErrorHandler::printError()
{
  cerr << "State Error: " << errorMsg << "\n";
}

void BaseState::process(InterfaceStateMachine& stateMachine)
{
  try
  {
    enter(stateMachine);
    doActivity();
    prepareNextState();
    nextState_ = getNextState();
    const uint8_t nextStateType =
      nextState_ ? nextState_->getStateType() : UINT8_MAX;
    if (!nextStateIsValid(nextStateType, getValidStateTypes()))
    {
      cerr << "Error: Invalid state transition from "
           << static_cast<unsigned int>(getStateType()) << " to "
           << static_cast<unsigned int>(nextStateType) << "\n";
      throw std::runtime_error("Invalid state transition");
    }
  }
  catch (const std::exception& e)
  {
    cerr << "Context: State \n"
         << "Standard Exception : " << e.what() << "\n ";
  }
  catch (StateErrorHandler& seh)
  {
    seh.printError();
  }
  catch (...)
  {
    cerr << "Context: State \n"
         << "Unknown Exception\n";
  }
}

void BaseState::prepareNextState() {}

unique_ptr<InterfaceState> BaseState::getNextState()
{
  return std::move(nextState_);
}

void BaseState::setNextState(unique_ptr<InterfaceState> nextState)
{
  nextState_ = std::move(nextState);
}

const vector<uint8_t>& BaseState::getValidStateTypes() const
{
  return validStateTypes_;
}

void BaseState::setValidStateTypes(const vector<uint8_t>& validStateTypes)
{
  validStateTypes_ = validStateTypes;
}

uint8_t BaseState::getStateType() const { return UINT8_MAX; }

InterfaceStateMachine* BaseState::getStateMachine() const
{
#ifdef _DEBUG
  {
    if (stateMachine_ == nullptr)
    {
      cerr << "Error: stateMachine_ is null in BaseState::getStateMachine\n";
    }
  }
#endif

  return stateMachine_;
}

void BaseState::enter(InterfaceStateMachine& stateMachine)
{
  stateMachine_ = &stateMachine;

#ifdef _DEBUG
  {
    const string stateType = typeid(*this).name();
    cerr << "Entering state: " << stateType << "\n";
    // If stateMachine_ is null, print an error message
    if (stateMachine_ == nullptr)
    {
      cerr << "Error: stateMachine_ is null in InitializeState::enter\n";
    }
    // Otherwise, print the address of stateMachine_ and the inherited type
    else
    {
      cerr << "State Machine address: " << stateMachine_ << "\n";
      cerr << "State Machine class: " << typeid(*stateMachine_).name() << "\n";
    }
  }
#endif
}

void BaseState::doActivity() {}

bool BaseState::nextStateIsValid(const uint8_t& nextStateType,
                                 const vector<uint8_t>& validStateTypes) const
{
  for (const auto& validState : validStateTypes)
  {
    if (nextStateType == validState)
    {
      return true;
    }
  }
#ifdef _DEBUG
  cerr << "Next state is invalid\n";
#endif
  return false;
}

void BaseState::exit() {}
