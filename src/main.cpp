#include "project/text_io.h"
#include <iostream>
#include <istream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::ws;

using namespace TextIO;
auto main() -> int
{
	bool running = true;
	while (running)
	{
		outputText("Welcome to the Text-Based Adventure Game!");
		outputText("Are you ready to start your adventure?");
		bool playerIsReady = false;
		while (!playerIsReady)
		{
			if (getInput(YesNo::Yes) == "yes") {
				playerIsReady = true;
				outputText("Great! Let's begin your adventure.");
				break;
			}
			else {
				outputText("You are not ready? I promise I have done my best to make a fun adventure");
				outputText("Are you ready now?");
			}
		}
		running = false;
	}
}
