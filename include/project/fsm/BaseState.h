#ifndef BASE_STATE_H
#define BASE_STATE_H
#pragma once

#include "InterfaceState.h"

#include <array>
#include <string>
#include <vector>

using std::array;
using std::string;
using std::uint8_t;
using std::unique_ptr;
using std::vector;

class StateErrorHandler
{
  public:
  explicit StateErrorHandler(const string& msg) : errorMsg(msg) {}
  void printError();

  private:
  string errorMsg;
};

class InterfaceStateMachine;

class BaseState : public InterfaceState
{
  public:
  BaseState() = default;

  void process(InterfaceStateMachine& stateMachine) override final;
  unique_ptr<InterfaceState> getNextState() override;
  vector<uint8_t> getValidStateTypes() const override;
  uint8_t getStateType() const override;

  private:
  void enter(InterfaceStateMachine& stateMachine) override;
  void doActivity() override;
  void setNextState() override;
  void exit() override;
  bool
  nextStateIsValid(const uint8_t& nextState,
                   const vector<uint8_t>& validStateTypes) const override final;

  unique_ptr<InterfaceState> nextState_ = nullptr;
  const array<uint8_t, 0> validStateTypes_{}; // empty set by default
};

#endif // BASE_STATE_H
