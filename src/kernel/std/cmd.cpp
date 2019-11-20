#include "std/cmd.h"

#include <std/io.h>

namespace std
{
    void evalCommand()
    {
        // Save here the input
        const String USER_INPUT = input();

        // Disable user input
        disableCursor();

        // Separate user input to program output
        newLine();

        // Process command
        processCommand(USER_INPUT);

        // Add a new line
        newLine();

        // Print the header before user input
        displayShellInput();

        // Enable user input
        enableCursor();
    }

    void displayShellInput()
    {
        // Header
        cout << "> ";

        // Update caret properties
        beginUserInput();
    }

    void processCommand(const String &CMD)
    {
        if (CMD == "hw")
            print("Hello world !");
        else
            print("Unknown command");
    }
}
