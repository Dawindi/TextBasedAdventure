#include "project/fsm/GameStateMachine.h"
#include "project/text_io.h"
#include <cstdio>
#include <memory>
#include <string>

using std::string;

namespace
{

// Introductory texts and responses
string intro1 = "Welcome to the Text-Based Adventure Game!";
string intro2 = "Are you ready to start?";
string intro2YesResponse = "Great! Let's begin your adventure!";
string intro2NoResponse =
  "Are you sure? I promise you'll love it! Are you ready now?";
string defaultResponse =
  "I don't understand that command. Please try something else or type help to "
  "see available commands";
/////////////////////////////////////////////////////////////////
// End of introductory texts and responses

// Test room texts and responses
string testRoom1Intro =
  "You find yourself in a dimly lit room. There is a door to the north and "
  "a table in the center.";
string lookAtTable =
  "The table is old and covered in dust. On it, you see a rusty key and a "
  "mysterious box.";
string lookAtDoor =
  "The door is wooden and slightly ajar. It seems to lead to another room.";
/////////////////////////////////////////////////////////////////
// End of test room texts and responses
} // namespace

using namespace TextIO;
auto main() -> int
{
#if defined(DEBUG) || defined(_DEBUG)
  printf("Debug build\n");
#else
  // printf("Release mode\n");
#endif

  auto gameStateMachine = std::make_unique<GameStateMachine>();
  gameStateMachine->run();

  bool running = true;
  while (running)
  {
    outputText(intro1);
    bool playerReady = false;
    outputText(intro2);
    UserInput input = getInput();
    while (!playerReady)
    {
      if (input.type == CommandType::Yes)
      {
        playerReady = true;
        break;
      }
      else if (input.type == CommandType::No)
      {
        outputText(intro2NoResponse);
        input = getInput();
      }
      else
      {
        outputText(defaultResponse);
        input = getInput();
      }
    }
    outputText(intro2YesResponse);
    running = false;
  }
}