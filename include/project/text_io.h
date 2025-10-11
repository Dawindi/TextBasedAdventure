#ifndef TEXT_IO_H
#define TEXT_IO_H
#pragma once

#include <cstdint>
#include <string>

using std::string;

namespace TextIO {
	struct InputToProcess {
		string rawInput;
		bool expectCommand;
	};
	enum class YesNo : std::uint8_t {
		Yes = 0U,
		No,
		Invalid
	};

	// Handling inputs
	string getInput(YesNo expectYesOrNo);
	bool processInput(const InputToProcess& input);
	//bool registerInteraction();

	// Handling outputs
	bool outputText(const string& text);
	//string findTextToOutput();
}

#endif // TEXT_IO_H