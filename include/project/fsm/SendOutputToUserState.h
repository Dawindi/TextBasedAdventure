#ifndef SEND_OUTPUT_TO_USER_STATE_H
#define SEND_OUTPUT_TO_USER_STATE_H
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

class SendOutputToUserState : public BaseState
{
  public:
  SendOutputToUserState();

  void prepareNextState() override;
  uint8_t getStateType() const override;

  private:
  void enter(InterfaceStateMachine& stateMachine) override;
  void doActivity() override;
  void exit() override;

  const array<GameStateType, 1> validNextStates_;
};

#endif // SEND_OUTPUT_TO_USER_STATE_H
