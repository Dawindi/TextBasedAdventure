#include "project/fsm/BaseState.h"

#include <exception>
#include <iostream>
#include <project/fsm/InterfaceState.h>

using std::cerr;
using std::string;
using std::uint8_t;
using std::unique_ptr;
using std::vector;

void StateErrorHandler::printError()
{
  cerr << "State Error: " << errorMsg << "\n";
}

void BaseState::process()
{
  try
  {
    enter();
    doActivity();
    setNextState();
    const uint8_t nextStateType =
      nextState_ ? nextState_->getStateType() : UINT8_MAX;
    nextStateIsValid(nextStateType, getValidStateTypes());
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

const vector<uint8_t> BaseState::getValidStateTypes()
{
  return vector<uint8_t>();
}

const uint8_t BaseState::getStateType() const { return UINT8_MAX; }

void BaseState::enter()
{
  // Implementation for enter
}

void BaseState::doActivity()
{
  // Implementation for doActivity
}

void BaseState::setNextState() {}

const bool BaseState::nextStateIsValid(const uint8_t& nextStateType,
                                 const vector<uint8_t>& validStateTypes) const
{
  for (const auto& validState : validStateTypes)
  {
    if (nextStateType == validState)
    {
      return true;
    }
  }

#if defined(_DEBUG)
  {
    cerr << "Next state is invalid\n";
  }
#endif

  return false;
}

void BaseState::exit()
{
  // Implementation for exit
}
