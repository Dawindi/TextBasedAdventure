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
  void exit() override;
  void prepareNextState() override;

  // Next state getter
  unique_ptr<InterfaceState> getNextState() override final;

  // Valid state types getters and setters
  const vector<uint8_t>& getValidStateTypes() const override;
  void
  setValidStateTypes(const vector<uint8_t>& validStateTypes) override final;

  // State type getter
  uint8_t getStateType() const override;

  // State machine getter
  InterfaceStateMachine* getStateMachine() const;

  protected:
  void enter(InterfaceStateMachine& stateMachine) override;
  void setNextState(unique_ptr<InterfaceState> nextState) override final;

  private:
  void doActivity() override;
  bool
  nextStateIsValid(const uint8_t& nextState,
                   const vector<uint8_t>& validStateTypes) const override final;

  InterfaceStateMachine* stateMachine_;
  unique_ptr<InterfaceState> nextState_;
  vector<uint8_t> validStateTypes_;
};

#endif // BASE_STATE_H
