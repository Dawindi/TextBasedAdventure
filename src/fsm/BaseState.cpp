#include "project/fsm/BaseState.h"

#include <exception>
#include <iostream>
#include <project/fsm/InterfaceState.h>

using std::cerr;

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
    nextStateIsValid();
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

std::unique_ptr<InterfaceState> BaseState::getNextState() { return nullptr; }

std::uint8_t BaseState::getStateType() { return UINT8_MAX; }

void BaseState::enter()
{
  // Implementation for enter
}

void BaseState::doActivity()
{
  // Implementation for doActivity
}

void BaseState::setNextState()
{
  // Implementation for setNextState
}

bool BaseState::nextStateIsValid() { return false; }

void BaseState::exit()
{
  // Implementation for exit
}
