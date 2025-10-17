#ifndef INITIALIZE_STATE_MACHINE_H
#define INITIALIZE_STATE_MACHINE_H
#pragma once

#include "project/fsm/BaseState.h"

#include "project/fsm/GameStateMachine.h"
#include <array>
#include <cstdint>
#include <memory>

class InterfaceState;

class InitializeState : public BaseState
{
  public:
  InitializeState();
  ~InitializeState() = default;

  std::unique_ptr<InterfaceState> getNextState();

  virtual std::uint8_t getStateType() override;

  private:
  // Enter handles initialization when entering the state
  void enter() override final;
  // doActivity contains the main logic of the state
  void doActivity() override final;
  // setNextState determines the next state based on current conditions
  void setNextState() override final;
  // nextStateIsValid checks if the determined next state is valid
  virtual bool nextStateIsValid() override;
  // exit handles cleanup when exiting the state and replaces itself with the
  void exit() override final;

  std::unique_ptr<InterfaceState> nextState_;
  const std::array<GameStateType, 1> validNextStates_{
    GameStateType::SendOutputToUserState};
};

#endif // INITIALIZE_STATE_MACHINE_H
