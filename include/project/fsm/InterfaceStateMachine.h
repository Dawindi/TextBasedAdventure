#ifndef INTERFACE_STATE_MACHINE_H
#define INTERFACE_STATE_MACHINE_H
#pragma once

#include <cstdint>
#include <memory>

using std::uint8_t;
using std::unique_ptr;

class InterfaceState;

class InterfaceStateMachine
{
  public:
  virtual ~InterfaceStateMachine() = default;

  virtual void run(unique_ptr<InterfaceState> Startstate) = 0;
  virtual std::uint8_t getPreviousStateType() const = 0;
  virtual const InterfaceState& getCurrentState() const = 0;

  private:
  virtual void entryPoint() = 0;
  virtual void exitPoint() = 0;
  virtual void
  transitionToNextState(unique_ptr<InterfaceState> currentState) = 0;
  virtual void setPreviousStateType(std::uint8_t& stateType) = 0;
};

#endif // INTERFACE_STATE_MACHINE_H
