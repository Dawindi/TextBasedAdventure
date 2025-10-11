#ifndef TEXT_IO_H
#define TEXT_IO_H
#pragma once

#include <cstdint>
#include <string>

using std::string;

namespace TextIO
{
enum class CommandType : std::uint8_t
{
  Invalid = 0U,
  Unknown,
  Yes,
  No,
  Open,
  InteractWithTarget,
  MultipleChoice,
  Help,
  Save,
  Load,
  Quit,
  GoTo,
  Use,
  Take,
  Drop,
  Examine,
  TalkTo,
  Attack,
  OpenObject,
  Close,
  Inventory,
  Equip,
  Unequip,
};

struct UserInput
{
  CommandType type = CommandType::Invalid;
  string command;
  string interable;
  string target;
};

// struct outputParams
//{
//   CommandType commandType;
//   string outputText;
// };

// Handling inputs
UserInput getInput();
// bool processInput(UserInput& userInput);

// Handling outputs
// CommandType outputText(outputParams& outputParams);
void outputText(string& text);
} // namespace TextIO

#endif // TEXT_IO_H