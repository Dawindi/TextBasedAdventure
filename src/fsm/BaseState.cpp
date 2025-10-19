#include "project/fsm/BaseState.h"

#include <exception>
#include <iostream>
#include <project/fsm/InterfaceState.h>
#include <stdexcept>

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
    setNextState();
    // Need to create a getNextState here to solve this
    const uint8_t nextStateType =
      nextState_ ? nextState_->getStateType() : UINT8_MAX;
    if (!nextStateIsValid(nextStateType, getValidStateTypes()))
    {
      cerr << "Error: Invalid state transition from "
           << static_cast<unsigned int>(getStateType()) << " to "
           << static_cast<unsigned int>(nextStateType) << "\n";
      throw std::runtime_error("Invalid state transition");
    }
    exit();
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

unique_ptr<InterfaceState> BaseState::getNextState() { return nullptr; }

vector<uint8_t> BaseState::getValidStateTypes() const
{
  return vector<uint8_t>{};
}

uint8_t BaseState::getStateType() const { return UINT8_MAX; }

void BaseState::enter(InterfaceStateMachine& stateMachine) {}

void BaseState::doActivity() {}

void BaseState::setNextState() {}

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
