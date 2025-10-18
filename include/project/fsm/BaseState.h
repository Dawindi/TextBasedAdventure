#ifndef BASE_STATE_H
#define BASE_STATE_H
#pragma once

#include "InterfaceState.h"

#include <array>
#include <string>

using std::array;
using std::string;
using std::uint8_t;
using std::unique_ptr;
using std::vector;

class StateErrorHandler
{
  public:
  StateErrorHandler(const string& msg) : errorMsg(msg) {}

  void printError();

  private:
  string errorMsg;
};

class BaseState : public InterfaceState
{
  public:
  BaseState() = default;

  // Main processing function that calls the other functions in order
  virtual void process() override final;

  virtual unique_ptr<InterfaceState> getNextState() override;
  virtual const vector<uint8_t> getValidStateTypes() override;
  virtual const uint8_t getStateType() const override;

  private:
  // Enter handles initialization when entering the state
  virtual void enter() override;
  // doActivity contains the main logic of the state
  virtual void doActivity() override;
  // setNextState determines the next state based on current conditions
  virtual void setNextState() override;
  // exit handles cleanup when exiting the state and replaces itself with the
  virtual void exit() override;
  // nextStateIsValid checks if the determined next state is valid
  virtual const bool
  nextStateIsValid(const uint8_t& nextState,
                   const vector<uint8_t>& validStateTypes) const override final;

  const unique_ptr<InterfaceState> nextState_ = nullptr;
  const array<uint8_t, 0> validStateTypes_ = {};
};

#endif // BASE_STATE_H
