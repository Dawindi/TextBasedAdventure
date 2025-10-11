#include "project/text_io.h"
#include <cctype>
#include <iostream>
#include <istream>
#include <list>
#include <optional>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::ws;
using std::list;
using std::optional;

namespace TextIO_Helpers {
	const string defaultResponse = "I don't understand that command. Please try again";
	const list<string> textCommands = {
		// Basic commands
		"help",
		"save",
		"load",
		"quit",

		// Movement commands
		"go to",
		"move to",
		"walk to",
		"run to",
		"enter",
		"leave",

		// Interaction commands
		"use",
		"take",
		"pick up",
		"drop",
		"look at",
		"examine",
		"talk to",
		"attack",
		"open",
		"close"
	};

	optional<bool> StringToYesNo(const string& input) {
		if (input == "yes" || input == "y" || input == "Yes" || input == "Y") {
			return true;
		}
		else if (input == "no" || input == "n" || input == "No" || input == "N") {
			return false;
		}
		return std::nullopt;
	}

	string StringToLowerCase(const string& input) {
		string lowerCaseString = input;
		for (char& c : lowerCaseString) {
			c = tolower(c);
		}
		return lowerCaseString;
	}

	string promptOpenInput()
	{
		string input;
		getline(cin >> ws, input);
		return input;
	}

	optional<bool> promptYesNoInput()
	{
		string input;
		getline(cin >> ws, input);
		return StringToYesNo(input);
	}

	bool stringIsValid(const string& input)
	{
		// Check if the input is empty
		if (input.empty()) {
			return false;
		}
		// Check if the input contains only whitespace
		for (const auto& c : input) {
			if (!isspace(c)) {
				break;
			}
			return false;
		}
		// Check if the input contains only printable characters
		for (const auto& c : input) {
			if (!isprint(c)) {
				return false;
			}
		}
		return true;
	}
}


using namespace TextIO_Helpers;
string TextIO::getInput(YesNo expectYesOrNo)
{
	if (expectYesOrNo == YesNo::Yes) {
		optional<bool> input = promptYesNoInput();
		while (!input.has_value()) {
			outputText("Please answer 'yes' or 'no'.");
			input = promptYesNoInput();
		}
		return *input ? "yes" : "no";
	}
	else if (expectYesOrNo == YesNo::No)
	{
		string input = promptOpenInput();
		while (!stringIsValid(input)) {
			outputText(defaultResponse);
			input = promptOpenInput();
		}
		return input;
	}
	else {
		outputText("Error: Invalid expectation for input.");
		return "";
	}
}

bool TextIO::processInput(const InputToProcess& input)
{
	// If input is empty, return false
	if (input.rawInput.empty()) {
		return false;
	}

	// If not expecting a command, accept any input
	if (!input.expectCommand) {
		return true;
	}

	// Convert input to lowercase for easier comparison
	string lowerCaseInput = StringToLowerCase(input.rawInput);

	// Check if the input matches any known commands
	for (const auto& command : textCommands) {
		if (lowerCaseInput.find(command) != string::npos) {
			return true;
		}
	}
	// Unable to process input
	return false;
}

bool TextIO::outputText(const string& text)
{
	// Check if the text is valid
	if (!stringIsValid(text)) {
		return false;
	}
	cout << text << endl;
	return true;
}
