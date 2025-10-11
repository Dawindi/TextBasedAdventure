#include "project/text_io.h"
#include <cctype>
#include <iostream>
#include <istream>
#include <optional>
#include <unordered_map>
#include <vector>

using std::cerr;
using std::cin;
using std::getline;
using std::optional;
using std::unordered_map;
using std::vector;
using std::ws;
using TextIO::CommandType;

namespace TextIO_Helpers
{
const string defaultResponse =
  "I don't understand that command. Please try something else or type help to "
  "see available commands";
const unordered_map<string, CommandType> textCommands = {
  // Basic commands
  {"help", CommandType::Help},
  {"save", CommandType::Save},
  {"load", CommandType::Load},
  {"quit", CommandType::Quit},

  // Movement commands
  {"go to", CommandType::GoTo},
  {"move to", CommandType::GoTo},
  {"walk to", CommandType::GoTo},
  {"run to", CommandType::GoTo},
  {"travel to", CommandType::GoTo},
  {"enter", CommandType::GoTo},
  {"leave", CommandType::GoTo},

  // Interaction commands
  {"use", CommandType::Use},
  {"take", CommandType::Take},
  {"pick up", CommandType::Take},
  {"drop", CommandType::Drop},
  {"look at", CommandType::Examine},
  {"examine", CommandType::Examine},
  {"talk to", CommandType::TalkTo},
  {"attack", CommandType::Attack},
  {"open", CommandType::Open},
  {"close", CommandType::Close},

  // Inventory commands
  {"inventory", CommandType::Inventory},
  {"check inventory", CommandType::Inventory},
  {"show inventory", CommandType::Inventory},
  {"equip", CommandType::Equip},
  {"unequip", CommandType::Unequip},

  // Yes/No commands
  {"yes", CommandType::Yes},
  {"y", CommandType::Yes},
  {"no", CommandType::No},
  {"n", CommandType::No},

  // Multiple choice commands
  {"1", CommandType::MultipleChoice},
  {"2", CommandType::MultipleChoice},
  {"3", CommandType::MultipleChoice},
  {"4", CommandType::MultipleChoice},
  {"5", CommandType::MultipleChoice},
  {"6", CommandType::MultipleChoice},
  {"7", CommandType::MultipleChoice},
  {"8", CommandType::MultipleChoice},
  {"9", CommandType::MultipleChoice},
  {"10", CommandType::MultipleChoice},
};

string StringToLowerCase(const string& input)
{
  string lowerCaseString = input;
  for (char& c : lowerCaseString)
  {
    c = tolower(static_cast<unsigned char>(c));
  }
  return lowerCaseString;
}

bool stringIsValid(const string& input)
{
  if (input.empty())
  {
    return false;
  }
  for (const auto& c : input)
  {
    if (!isspace(static_cast<unsigned char>(c)))
    {
      break;
    }
    return false;
  }
  for (const auto& c : input)
  {
    if (!isprint(static_cast<unsigned char>(c)))
    {
      return false;
    }
  }
  return true;
}

// Splits the input string into words separated by single or multiple space
// characters. Empty segments caused by consecutive spaces are ignored.
vector<string> SplitBySpaces(const string& input)
{
  vector<string> words;
  string current;
  for (char c : input)
  {
    if (c == ' ')
    {
      if (!current.empty())
      {
        words.push_back(current);
        current.clear();
      }
    }
    else
    {
      current.push_back(c);
    }
  }
  if (!current.empty())
  {
    words.push_back(current);
  }
  return words;
}

void checkCommand(TextIO::UserInput userInput)
{
  switch (userInput.type)
  {
    case CommandType::Invalid:
    case CommandType::Unknown:
      cerr << defaultResponse << "\n";
      break;
    case CommandType::Yes:
    case CommandType::No:
      if (userInput.command.empty())
      {
        cerr << "Please respond with yes or no.\n";
      }
      break;
    case CommandType::Open:
      break;
    case CommandType::InteractWithTarget:
      break;
    case CommandType::MultipleChoice:
      break;
    case CommandType::Help:
      break;
    case CommandType::Save:
      break;
    case CommandType::Load:
      break;
    case CommandType::Quit:
      break;
    case CommandType::GoTo:
      break;
    case CommandType::Use:
      break;
    case CommandType::Take:
      break;
    case CommandType::Drop:
      break;
    case CommandType::Examine:
      break;
    case CommandType::TalkTo:
      break;
    case CommandType::Attack:
      break;
    case CommandType::OpenObject:
      break;
    case CommandType::Close:
      break;
    case CommandType::Inventory:
      break;
    case CommandType::Equip:
      break;
    case CommandType::Unequip:
      break;
    default:
      cerr << "Error: Unhandled CommandType in checkCommand\n";
      break;
  }
}
} // namespace TextIO_Helpers

using namespace TextIO_Helpers;
TextIO::UserInput TextIO::getInput()
{
  TextIO::UserInput userInput = {
    .type = CommandType::Invalid, .command = "", .target = ""};
  string inputLine;
  getline(cin >> ws, inputLine);
  if (!stringIsValid(inputLine))
  {
    return userInput;
  }
  string lowerCaseInput = StringToLowerCase(inputLine);
  vector<string> words = SplitBySpaces(lowerCaseInput);
  if (words.empty())
  {
    return userInput;
  }

  for (const auto& [commandText, commandType] : textCommands)
  {
    if (string singleWordCommand = words[0];
        singleWordCommand.find(commandText) == 0)
    {
      userInput.type = commandType;
      userInput.command = words[0];
      userInput.interable = words.size() > 1 ? words[1] : "";
      userInput.target = words.size() > 2 ? words[2] : "";
    }
    else if (words.size() > 1)
    {

      if (string twoWordCommand = words[0] + " " + words[1];
          twoWordCommand.find(commandText) == 0)
      {
        userInput.type = commandType;
        userInput.command = twoWordCommand;
        userInput.interable = words.size() > 2 ? words[2] : "";
        userInput.target = words.size() > 3 ? words[3] : "";
      }
    }
  }
  return userInput;
}

void TextIO::outputText(string& text)
{
  if (!stringIsValid(text))
  {
    cerr << "Error: outputText called with invalid string" << "\n";
    return;
  }
  cerr << text << "\n";
  return;
}
