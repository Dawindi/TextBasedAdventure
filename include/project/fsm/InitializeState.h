#ifndef INITIALIZE_STATE_H
#define INITIALIZE_STATE_H
#pragma once

#include "project/fsm/BaseState.h"
#include "project/fsm/GameStateMachine.h"
#include <array>
#include <cstdint>

using std::array;
using std::uint8_t;

class InterfaceStateMachine;

class InitializeState : public BaseState
{
  public:
  InitializeState();

  void prepareNextState() override;
  uint8_t getStateType() const override;

  private:
  void enter(InterfaceStateMachine& stateMachine) override;
  void doActivity() override;

  const array<GameStateType, 1> validNextStates_;
};

#endif // INITIALIZE_STATE__H
