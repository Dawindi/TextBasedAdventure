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

class InterfaceState;

class ValidateGameState : public BaseState
{
  public:
  ValidateGameState();

  unique_ptr<InterfaceState> getNextState() override;

  virtual const uint8_t getStateType() const override;
  const uint8_t getNextContext(const uint8_t& currentContext) const;

  private:
  // Enter handles initialization when entering the state
  void enter() override;
  // doActivity contains the main logic of the state
  void doActivity() override;
  // setNextState determines the next state based on current conditions
  void setNextState() override;

  unique_ptr<InterfaceState> nextState_;
  const array<GameStateType, 2> validNextStates_{
    GameStateType::HandleErrorState, GameStateType::StartGameState};
  GameContext nextContext_ = GameContext::InvalidContext;
};

#endif // VALIDATE_STATE_MACHINE_H