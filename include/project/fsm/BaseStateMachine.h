#ifndef BASE_STATE_MACHINE_H
#define BASE_STATE_MACHINE_H
#pragma once

#include "InterfaceStateMachine.h"

#include <memory>

class InterfaceState;

class BaseStateMachine : public InterfaceStateMachine
{
  public:
  BaseStateMachine();
  virtual void run() override final;

  private:
  virtual void entryPoint() override final;
  virtual void exitPoint() override;
  virtual void transitionToNextState() override final;

  std::unique_ptr<InterfaceState> state_;
};

#endif // BASE_STATE_MACHINE_H
