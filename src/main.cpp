#include "project/text_io.h"
#include <string>

using std::string;

namespace
{
// outputParams intro1{.commandType = CommandType::Unknown,
//                     .outputText = "Welcome to the Text-Based Adventure
//                     Game!"};
// outputParams intro2{.commandType = CommandType::No,
//                     .outputText = "Are you ready to start your adventure?"};
// outputParams intro2YesResponse{.commandType = CommandType::Unknown,
//                                .outputText =
//                                  "Great! Let's begin your adventure!"};
// outputParams intro2NoResponse{
//   .commandType = CommandType::No,
//   .outputText = "Are you sure? I promise you'll love it! Are you ready
//   now?"};
string intro1 = "Welcome to the Text-Based Adventure Game!";
string intro2 = "Great! Let's begin your adventure!";
string intro2YesResponse = "Great! Let's begin your adventure!";
string intro2NoResponse =
  "Are you sure? I promise you'll love it! Are you ready now?";
string defaultResponse =
  "I don't understand that command. Please try something else or type help to "
  "see available commands";
} // namespace

using namespace TextIO;
auto main() -> int
{
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
    outputText(intro2);
    running = false;
  }
}