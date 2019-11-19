#pragma once

// To handle system's commands

#include <std/types.h>
#include <std/String.h>

namespace std
{
    // Evaluates the current user input as a command
    void evalCommand();

    // Displays the header before user input
	void displayShellInput();

    // Processes a line of command
    void processCommand(const String &CMD);
}
