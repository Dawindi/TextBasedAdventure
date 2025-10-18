#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H
#pragma once

#include "BaseStateMachine.h"
#include <cstdint>
#include <memory>

class InterfaceState;

enum class GameStateType : std::uint8_t
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

enum class GameContext : std::uint8_t
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

  private:
  //virtual void entryPoint() override;
  virtual void transitionToNextState() override;
  virtual void exitPoint() override;

  std::unique_ptr<InterfaceState> state_;
  GameContext currentContext_;
};

#endif // GAME_STATE_MACHINE_H
