#ifndef VALIDATE_STATE_MACHINE_H
#define VALIDATE_STATE_MACHINE_H
#pragma once

#include "project/fsm/BaseState.h"
#include "project/fsm/GameStateMachine.h"
#include <array>
#include <cstdint>
#include <memory>

using std::array;
using std::uint8_t;
using std::unique_ptr;

class InterfaceStateMachine;

class ValidateGameState : public BaseState
{
  public:
  ValidateGameState();

  void prepareNextState() override;
  uint8_t getStateType() const override;
  uint8_t getNextContext(const uint8_t& currentContext) const;

  private:
  void enter(InterfaceStateMachine& stateMachine) override;
  void doActivity() override;

  const array<GameStateType, 2> validNextStates_;
};

#endif // VALIDATE_STATE_MACHINE_H