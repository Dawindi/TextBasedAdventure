#ifndef INTERFACE_STATE_MACHINE_H
#define INTERFACE_STATE_MACHINE_H
#pragma once

class InterfaceStateMachine
{
  public:
  virtual ~InterfaceStateMachine() = default;

  virtual void run() = 0;

  private:
  virtual void entryPoint() = 0;
  virtual void exitPoint() = 0;
  virtual void transitionToNextState() = 0;
};

#endif // INTERFACE_STATE_MACHINE_H
