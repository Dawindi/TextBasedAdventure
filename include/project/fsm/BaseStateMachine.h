#ifndef BASE_STATE_MACHINE_H
#define BASE_STATE_MACHINE_H
#pragma once

#include "InterfaceState.h"
#include "InterfaceStateMachine.h"

#include <cstdint>
#include <memory>

using std::uint8_t;
using std::unique_ptr;

class BaseStateMachine : public InterfaceStateMachine
{
  public:
  BaseStateMachine();
  virtual ~BaseStateMachine() = default;
  void run(unique_ptr<InterfaceState> Startstate) override final;
  uint8_t getPreviousStateType() const override final;
  const InterfaceState& getCurrentState() const override final;

  protected:
  void transitionToNextState(InterfaceState* currentState) override;
  void setPreviousStateType(uint8_t& stateType) override;

  private:
  void entryPoint() override final;
  void exitPoint() override;

  unique_ptr<InterfaceState> state_;
  uint8_t previousStateType_;
};

#endif // BASE_STATE_MACHINE_H
