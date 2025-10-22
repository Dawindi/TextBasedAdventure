#ifndef INTERFACE_STATE_H
#define INTERFACE_STATE_H
#pragma once

#include <cstdint>
#include <memory>
#include <vector>

using std::uint8_t;
using std::unique_ptr;
using std::vector;

class InterfaceStateMachine;

class InterfaceState
{
  public:
  // Virtual destructor for proper cleanup of derived classes
  virtual ~InterfaceState() = default;

  // Main processing function that calls the other functions in order
  virtual void process(InterfaceStateMachine& stateMachine) = 0;
  // exit handles cleanup when exiting the state and replaces itself with the
  // next state
  virtual void exit() = 0;

  // Getters and setters
  virtual unique_ptr<InterfaceState> getNextState() = 0;
  virtual void setNextState(unique_ptr<InterfaceState> nextState) = 0;
  virtual const vector<uint8_t>& getValidStateTypes() const = 0;
  virtual void setValidStateTypes(const vector<uint8_t>& validStateTypes) = 0;
  virtual uint8_t getStateType() const = 0;

  private:
  // Enter handles initialization when entering the state
  virtual void enter(InterfaceStateMachine& stateMachine) = 0;
  // doActivity contains the main logic of the state
  virtual void doActivity() = 0;
  // PrepareNextState prepares the next state before exiting the current state
  virtual void prepareNextState() = 0;
  // nextStateIsValid checks if the determined next state is valid
  virtual bool
  nextStateIsValid(const uint8_t& nextState,
                   const vector<uint8_t>& validStateTypes) const = 0;
};

#endif // INTERFACE_STATE_H
