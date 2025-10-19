#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H
#pragma once

#include "BaseStateMachine.h"
#include "InterfaceState.h" // ensure complete type

#include <cstdint>
#include <memory>

using std::uint8_t;
using std::unique_ptr;

enum class GameStateType : uint8_t
{
  InvaslidState = 255,
  InitializeState = 0,
  SendOutputToUserState,
  RequestInputFromUserState,
  ProcessUserInputState,
  CheckForSavedGameState,
  NoSavedGameFoundState,
  SaveGameFoundState,
  CreateNewGameState,
  LoadSavedGameState,
  HandleErrorState,
  ValidateGameState,
  StartGameState,
  UpdateWorldAndEntitiesState,
  SaveGameState,
};

enum class GameContext : uint8_t
{
  InvalidContext = 255,
  StartUpOrError = 0,
  GameIsRunning,
  SaveGame,
};

class GameStateMachine : public BaseStateMachine
{
  public:
  GameStateMachine();
  virtual ~GameStateMachine() = default;

  private:
  void transitionToNextState(unique_ptr<InterfaceState> currentState) override;
  void exitPoint() override;

  GameContext currentContext_;
};

#endif // GAME_STATE_MACHINE_H
