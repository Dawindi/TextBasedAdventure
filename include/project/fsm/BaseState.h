#ifndef BASE_STATE_H
#define BASE_STATE_H
#pragma once

#include "InterfaceState.h"

#include <cstdint>
#include <memory>
#include <string>

class StateErrorHandler
{
  public:
  StateErrorHandler(const std::string& msg) : errorMsg(msg) {}

  void printError();

  private:
  std::string errorMsg;
};

class BaseState : public InterfaceState
{
  public:
  // Virtual destructor for proper cleanup of derived classes
  virtual ~BaseState() = default;

  // Main processing function that calls the other functions in order
  virtual void process() override final;

  virtual std::unique_ptr<InterfaceState> getNextState();

  virtual std::uint8_t getStateType() override;

  private:
  // Enter handles initialization when entering the state
  virtual void enter() override;
  // doActivity contains the main logic of the state
  virtual void doActivity() override;
  // setNextState determines the next state based on current conditions
  virtual void setNextState() override;
  // nextStateIsValid checks if the determined next state is valid
  virtual bool nextStateIsValid() override;
  // exit handles cleanup when exiting the state and replaces itself with the
  virtual void exit() override;
};

#endif // BASE_STATE_H
